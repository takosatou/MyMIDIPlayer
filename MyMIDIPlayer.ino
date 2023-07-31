// MIDI Player
#include <M5Stack.h>
#include <SPI.h>
#include <usbhub.h>

#include <usbh_midi.h>
#include <efont.h>
#include <efontESP32.h>
#include <efontEnableJaMini.h>

#include "src/MD_MIDIFile/MD_MIDIFile.h"
#include "Songs.h"
#include "melody.h"
#include "debug.h"

USB usb;
USBH_MIDI midi(&usb);
MD_MIDIFile smf;
Songs songs;
int scroll_top = 0;
int cur_artist = 0;  // 0: Setting, 1..: artists
int cur_song = 0;    // -1: back, 0..: songs
enum { ARTIST, SONG } mode = ARTIST;
enum { S_INIT, S_IDLE, S_PLAYING } state = S_INIT;
enum { R_NONE, R_SINGLE, R_ALL } repeat = R_ALL;

bool piano_mode = true;
bool nsx39_mode = false;

const int SETTINGS = 0;
const char SETTINGS_TXT[] = "/settings.txt";

bool GS_mode = false;

void load_settings() {
  File f = SD.open(SETTINGS_TXT, FILE_READ);
  if (f.available()) {
    char c = f.read();
    piano_mode = c == '1';
    c = f.read();
    repeat = c == '2' ? R_ALL : c == '1' ? R_SINGLE : R_NONE;
    c = f.read();
    nsx39_mode = c == '1';
  }
  f.close();
}

void save_settings() {
  File f = SD.open(SETTINGS_TXT, FILE_WRITE);
  f.write(piano_mode ? '1' : '0');
  f.write(repeat == R_ALL ? '2' : repeat == R_SINGLE ? '1' : '0');
  f.write(nsx39_mode ? '1' : '0');
  f.close();
}

void send_midi(midi_event *pev) {
  if ((pev->data[0] >= 0x80) && (pev->data[0] <= 0xe0)) {
    if (GS_mode && pev->data[0] == 0xb0 && pev->data[1] == 7) {
      DEBUGX("\n", pev->data[2]);
      int v = (int)(pev->data[2] * 1.5);
      if (v > 127) v = 127;
      pev->data[2] = (uint8_t)v;
      DEBUGX(" -> ", pev->data[2]);
      DEBUGS(" Volume Up\n");
    }

    if (piano_mode && (pev->data[0] & 0xf0) == 0xc0) {
      // skip if the program is not melodious instrument
      if (MELODY[pev->data[1]] == 0) return;
      pev->data[1] = 0; // overwrite to Acoustic Piano
    }
    if (nsx39_mode && pev->channel == 0) {
      // remap ch1 to ch16 for NSX-39, because ch1 is reserved for MIKU voice
      pev->data[0] = (pev->data[0] & 0xf0) | 15;
    } else {
      pev->data[0] = (pev->data[0] & 0xf0) | pev->channel;
    }
  }
  if (!piano_mode || pev->channel != 9) { // skip Drum channel in Piano mode
    midi.SendData(pev->data, pev->size);
  }
  /*
  DEBUG("\n", millis());
  DEBUG("\tM T", pev->track);
  DEBUG(":  Ch ", pev->channel + 1);
  DEBUGS(" Data");
  for (uint8_t i = 0; i < pev->size; i++) {
    DEBUGX(" ", pev->data[i]);
  }
  */
  if (pev->data[0] == 0xb0 && pev->data[1] == 7) {
    DEBUGX(" ", pev->data[2]);
    DEBUGS(" Volume\n");
  }
}

void midi_volume(int vol);

void send_sysex(sysex_event *pev)
{
  DEBUG("\nS T", pev->track);
  DEBUGS(": Data");
  for (uint8_t i = 0; i < pev->size; i++)
    DEBUGX(" ", pev->data[i]);

  const uint8_t* data = pev->data;
  // GS master volume -> Volume Up!
  // F0 41 10 42 12 40 00 04 vol sum F7
  if (data[1] == 0x41 && data[2] == 0x10 && data[3] == 0x42 && data[4] == 0x12 &&
      data[5] == 0x40 && data[6] == 0x00 && data[7] == 0x04) {
    DEBUGX("\n", pev->data[8]);
    DEBUGS("GS Volume\n");
    midi_volume(127);
    GS_mode = true;
  }
}

uint8_t GM_SYSTEM_ON[] = {
  0xf0, 0x7e, 0x7f, 0x09, 0x01, 0xf7,
};

void midi_reset(void)
{
  midi.SendSysEx(GM_SYSTEM_ON, sizeof(GM_SYSTEM_ON));
  delay(500);

  midi_event ev;
  ev.size = 3;
  ev.data[0] = 0xb0;
  ev.data[1] = 121;
  ev.data[2] = 0;

  for (int c = 0; c < MIDI_MAX_TRACKS; c++) {
    ev.channel = c;
    send_midi(&ev);
  }

  GS_mode = false;
}

void midi_silence(void)
{
  midi_event ev;
  ev.size = 3;
  ev.data[0] = 0xb0;
  ev.data[1] = 120;
  ev.data[2] = 0;

  for (int c = 0; c < MIDI_MAX_TRACKS; c++) {
    ev.channel = c;
    send_midi(&ev);
  }
}

uint8_t MASTER_VOLUME[] = {
  0xf0, 0x7f, 0x7f, 0x04, 0x01, 0x00, 0x00, 0xf7,
};

void midi_volume(int vol)
{
  midi_event ev;
  ev.size = 3;
  ev.data[0] = 0xb0;
  ev.data[1] = 7;
  ev.data[2] = (uint8_t)vol;

  for (int c = 0; c < MIDI_MAX_TRACKS; c++) {
    ev.channel = c;
    send_midi(&ev);
  }

  MASTER_VOLUME[5] = (uint8_t)vol;
  MASTER_VOLUME[6] = (uint8_t)vol;
  midi.SendSysEx(MASTER_VOLUME, sizeof(MASTER_VOLUME));
}

void on_init_midi()
{
  midi_reset();
  midi_silence();
}

// Poll USB MIDI Controler
void MIDI_poll()
{
  uint8_t inBuf[3];
  midi.RecvData(inBuf);
}

const int N_LIST = 10;

void draw_list() {
  M5.Lcd.startWrite();
  M5.Lcd.fillScreen(0x0000);
  if (mode == ARTIST) {
    // draw artists
    if (cur_artist < scroll_top) {
      scroll_top = cur_artist;
    } else if (cur_artist >= scroll_top + N_LIST) {
      scroll_top = cur_artist - N_LIST + 1;
    }
    M5.Lcd.fillRect(0, (cur_artist - scroll_top) * 20, 320, 18, 0x7800);
    for (int i = 0; i < N_LIST; i++) {
      int n = i + scroll_top;
      if (n == cur_artist) {
	M5.Lcd.setTextColor(0xFFFF, 0x7800);
      } else {
	M5.Lcd.setTextColor(0xFFFF, 0x0000);
      }
      if (n >= songs.get_n_artists()) break;
      printEfont(songs.get_artist(n), 5, i * 20, 1);
    }
  } else {
    // draw songs
    if (cur_song < scroll_top) {
      scroll_top = cur_song;
    } else if (cur_song + 1 >= scroll_top + N_LIST) {
      scroll_top = cur_song - N_LIST + 1;
    }
    // draw artist name on the first row
    M5.Lcd.setTextColor(0xFF00, 0x0000);
    printEfont(songs.get_artist(cur_artist), 5, 0, 1);
    // draw songs from the second row
    M5.Lcd.fillRect(0, (cur_song - scroll_top) * 20 + 20, 320, 18, 0x7800);
    for (int i = 0; i < N_LIST; i++) {
      int n = i + scroll_top;
      if (n == cur_song) {
	M5.Lcd.setTextColor(0xFFFF, 0x7800);
      } else {
	M5.Lcd.setTextColor(0xFFFF, 0x0000);
      }
      if (n >= songs.get_n_songs(cur_artist)) break;
      if (n < 0) {
	printEfont("←もどる", 10, 20, 1);
      } else {
	printEfont(songs.get_song(cur_artist, n).title, 10, (i+1) * 20, 1);
      }
    }
    if (cur_artist == SETTINGS) {
      // draw settings
      printEfont(piano_mode ? "ON" : "OFF", 135, 2 * 20, 1);
      printEfont(repeat == R_SINGLE ? "1曲" : repeat == R_ALL ? "全曲" : "なし", 135, 3 * 20, 1);
      printEfont(nsx39_mode ? "ON" : "OFF", 135, 4 * 20, 1);
    }
  }

  // draw settings on the right-bottom corner
  M5.Lcd.setTextColor(0xFC9F, 0x0000);
  if (piano_mode) printEfont("P", 0, 220, 1);
  if (repeat == R_ALL) printEfont("A", 10, 220, 1);
  else if (repeat == R_SINGLE) printEfont("1", 10, 220, 1);
  if (nsx39_mode) printEfont("N", 20, 220, 1);

  // draw button labels
  M5.Lcd.setTextColor(0x0000, 0xFFFF);
  if (state == S_PLAYING) {
    printEfont(piano_mode ? "ピアノ" : " 原曲 ", 40, 220, 1);
    printEfont(" 停止 ", 135, 220, 1);
    printEfont(repeat == R_SINGLE ? "1曲リピート" :
	       repeat == R_ALL ? "全曲リピート" : "リピートなし", 210, 220, 1);
  } else {
    printEfont("  ↑  ", 40, 220, 1);
    printEfont(((mode == ARTIST && cur_artist == 0) ||
		(mode == SONG && cur_artist == SETTINGS) ||
		cur_song < 0) ?
	       " 選択 " : " 再生 ", 135, 220, 1);
    printEfont("  ↓  ", 230, 220, 1);
  }
  M5.Lcd.endWrite();
}

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.begin();
  M5.Speaker.begin();
  M5.Speaker.mute();
  SD.begin();
  // SDfonts.init(4);
  Serial.begin(9600);

  Serial.print("\nLoading index.csv\n");

  if (!songs.load("/index.csv")) {
    FATAL("Error: songs.load(). Halt.");
    while (1); //halt
  }

  Serial.print("Loading setting.txt\n");
  load_settings();

  Serial.print("Initializing USB\n");
  if (usb.Init() == -1) {
    FATAL("Error: usb.Init(). Halt.");
    while (1); //halt
  }
  delay(200);

  Serial.print("Initializing MIDI reader\n");
  midi.attachOnInit(on_init_midi);

  smf.begin();
  smf.setMidiHandler(send_midi);
  smf.setSysexHandler(send_sysex);

  Serial.print("Done setup()\n");

  draw_list();
}

void play_song() {
  midi_reset();
  midi_silence();
  midi_volume(100);

  const Song& song = songs.get_song(cur_artist, cur_song);
  DEBUGS("Play ");
  DEBUGS(song.artist);
  DEBUGS(" ");
  DEBUGS(song.title);
  DEBUGS(" ");
  DEBUGS(song.filename);
  DEBUGS("\n");
  int err = smf.load(song.filename);

  if (err == MD_MIDIFile::E_OK) {
    state = S_PLAYING;
    draw_list();
  } else {
    DEBUG(" - SMF load Error ", err);
    state = S_INIT;
    draw_list();
  }
}

#define LONG_PRESS 1000

void loop() {
  M5.update();
  usb.Task();

  switch (state) {
  case S_INIT:
    // wait until MIDI is ready
    if (midi) {
      state = S_IDLE;
    } else {
      DEBUGS("!Midi\n");
    }
    break;

  case S_IDLE:
    if (M5.BtnA.wasPressed() || M5.BtnA.pressedFor(LONG_PRESS)) {
      if (mode == ARTIST) {
	if (cur_artist > 0) {
	  cur_artist--;
	} else {
	  cur_artist = songs.get_n_artists() - 1;
	}
	draw_list();
      }
      if (mode == SONG) {
	if (cur_song >= 0) {
	  cur_song--;
	} else {
	  cur_song = songs.get_n_songs(cur_artist) - 1;
	}
	draw_list();
      }
    } else if (M5.BtnC.wasPressed() || M5.BtnC.pressedFor(LONG_PRESS)) {
      if (mode == ARTIST) {
	if (cur_artist < songs.get_n_artists() - 1) {
	  cur_artist++;
	} else {
	  cur_artist = 0;
	}
	draw_list();
      }
      if (mode == SONG) {
	if (cur_song < songs.get_n_songs(cur_artist) - 1) {
	  cur_song++;
	} else {
	  cur_song = -1;
	}
	draw_list();
      }
    } else if (M5.BtnB.wasPressed()) {
      if (mode == ARTIST) {
	mode = SONG;
	scroll_top = cur_song = -1;
	draw_list();
      } else if (cur_song < 0) {
	mode = ARTIST;
	scroll_top = 0;
	draw_list();
      } else if (cur_artist == SETTINGS) {
	if (cur_song == 0) {
	  piano_mode = !piano_mode;
	} else if (cur_song == 1) {
	  if (repeat == R_NONE) repeat = R_SINGLE;
	  else if (repeat == R_SINGLE) repeat = R_ALL;
	  else repeat = R_NONE;
	} else if (cur_song == 2) {
	  nsx39_mode = !nsx39_mode;
	}
	save_settings();
	draw_list();
      } else {
	play_song();
      }
    }
    break;

  case S_PLAYING: // play the file
    if (smf.isEOF()) {
      smf.close();

      if (repeat == R_SINGLE) {
	play_song();
      } else if (repeat == R_ALL) {
	if (cur_song < songs.get_n_songs(cur_artist) - 1) {
	  cur_song++;
	} else {
	  cur_song = 0;
	}
	play_song();
      } else {
	state = S_IDLE;
	draw_list();
      }

    } else if (M5.BtnB.wasPressed()) {
      midi_reset();
      midi_silence();

      smf.close();
      state = S_IDLE;
      draw_list();
    } else if (M5.BtnA.wasPressed()) {
      piano_mode = !piano_mode;
      save_settings();
      draw_list();
      // replay
      smf.close();
      play_song();

    } else if (M5.BtnC.wasPressed()) {
      if (repeat == R_NONE) repeat = R_SINGLE;
      else if (repeat == R_SINGLE) repeat = R_ALL;
      else repeat = R_NONE;
      save_settings();
      draw_list();
    } else {
      smf.getNextEvent();
    }
    break;

  default:
    state = S_IDLE;
    break;
  }

  if (midi) {
    MIDI_poll();
  }
}
