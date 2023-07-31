# A Simple MIDI file player using M5Stack Core and USB module

Copyright (C) 2023 Takashi Satou
Released under the LGPL-2.1 License

Files in src/MD_MIDIFile/ are based on MajicDesigns/MD_MIDIFile <https://github.com/MajicDesigns/MD_MIDIFile>, that are released under the LGPL-2.1 License.

## Dependent Libraries
- USB Host Shield Library 2.0
- YuuichiAkagawa/USBH_MIDI <https://github.com/tanakamasayuki/efont>
- taakamasayuki/efont <https://github.com/tanakamasayuki/efont>

## Settings in SD card
### index.csv
You need to place `index.csv` file in the root directory of the SD card.

Example
```
Group,Title,Filename
[設定],ピアノモード,0
[設定],リピート,0
[設定],NSX-39モード,0
クラシック,ドビュッシー アラベスク1,arabe1.mid
クラシック,ドビュッシー 月の光,bergam3.mid
クラシック,ドビュッシー 亜麻色の髪の乙女,prelude8.mid
クラシック,ショパン ノクターン,chno0902.mid
バッハ,メヌエット,menuett.mid
バッハ,アリア,air.mid
バッハ,シャコンヌ,vp2-5cha.mid
...
,,
```

The first line is for the titles of columns: `Group,Title,Filename`.

The following three lines are for setting modes.
```
[設定],ピアノモード,0
[設定],リピート,0
[設定],NSX-39モード,0
```

Then you may write the group, title and filename of a song for each line.

The last line must be `,,` to indicate the end of file.

### *.mid files

MIDI files (`*.mid`) should be placed in the root directory as well as `index.csv`.

## Settings

- ピアノモード Piano mode --- All instruments are conveted to piano. This is for Digital Piano that can use only piano voices.
- リピート Repeat mode --- Select 全曲 all / 1曲 one song / なし no repeat.
- NSX-39 mode --- Remap 1ch to 16ch, because 1ch in NSX-39 is reserved for Hatsune Miku's voice.

## Selecting the group
Using the left and right buttons to select a group, then press the center button to enter the group.

## Playing the song
Using the left and right buttons to select a song, then press the center button to play the song.

During playback, you can press the buttons:
- Left button --- Toggle piano mode
- Center button --- Stop playing the song
- Right button --- change repeat mode
