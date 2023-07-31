#include <M5Stack.h>
#include "Songs.h"
#include "debug.h"

bool Songs::load_index_(const char* index) {
  File f = SD.open(index, FILE_READ);
  if (!f.available()) {
    Serial.print("Cannot open '");
    Serial.print(index);
    Serial.print("'\n");
    return false;
  }
  all_size_ = f.size();
  all_ = (char*)malloc(all_size_);
  if (all_ == 0) {
    Serial.print("Out of memory for ");
    Serial.print(index);
    Serial.print("'\n");
    return false;
  }
  f.read((uint8_t*)all_, all_size_);
  f.close();

  return true;
}

bool Songs::assign_songs_() {
  // allocate songs
  n_songs_ = 0;
  int i;
  for (i = 0; i < all_size_; i++) {
    if (all_[i] == '\n') {
      n_songs_++;
    }
  }
  DEBUGSP("n_songs=%d\n", n_songs_);
  songs_ = (Song*)malloc(sizeof(struct Song) * n_songs_);
  if (songs_ == 0) {
    Serial.print("Out of memory for songs_\n");
    return false;
  }

  // skip the first row for label
  for (i = 0; i < all_size_; i++) {
    if (all_[i] == '\n') {
      i++;
      break;
    }
  }

  int sn = 0;
  // replace ',' to '\n'
  while (i < all_size_) {
    struct Song* csong = &songs_[sn];
    csong->artist = &all_[i];
    for (; i < all_size_; i++) {
      if (all_[i] == ',') {
	all_[i] = '\0';
	i++;
	break;
      }
    }
    csong->title = &all_[i];
    for (; i < all_size_; i++) {
      if (all_[i] == ',') {
	all_[i] = '\0';
	i++;
	break;
      }
    }
    csong->filename = &all_[i];
    for (; i < all_size_; i++) {
      if (all_[i] == '\r') {
	all_[i] = '\0';
      } else if (all_[i] == '\n') {
	all_[i] = '\0';
	i++;
	break;
      }
    }
    sn++;
    /*
    Serial.print(csong->artist);
    Serial.print(" ");
    Serial.print(csong->title);
    Serial.print(" ");
    Serial.print(csong->filename);
    Serial.print("\n");
    */
  }
  return true;
}

bool Songs::assign_artists_() {
  n_artists_ = 0;
  const char* ca = songs_[0].artist;
  int i;
  for (i = 1; i < n_songs_; i++) {
    if (*ca == '\0') break;

    /*
    DEBUGSP("%d ", i);
    Serial.print(ca);
    Serial.print(" ");
    Serial.print(songs_[i].artist);
    Serial.print("\n");
    */

    if (strcmp(ca, songs_[i].artist) != 0) {
      n_artists_++;
      ca = songs_[i].artist;
      /*
      Serial.print(ca);
      Serial.print("\n");
      */
    }
  }
  DEBUGSP("n_artists=%d\n", n_artists_);

  artists_ = (Artist*)malloc(sizeof(struct Artist) * (n_artists_ + 1));
  if (songs_ == 0) {
    Serial.print("Out of memory for artists_\n");
    return false;
  }

  n_artists_ = 0;
  artists_[0].artist = songs_[0].artist;
  artists_[0].start = 0;
  ca = songs_[0].artist;

  for (i = 1; i < n_songs_; i++) {
    if (*ca == '\0') {
      break;
    }
    if (strcmp(ca, songs_[i].artist) != 0) {
      artists_[n_artists_++].end = i - 1;
      ca = artists_[n_artists_].artist = songs_[i].artist;
      artists_[n_artists_].start = i;
    }
  }
  artists_[n_artists_].end = i - 1;
  return true;
}

