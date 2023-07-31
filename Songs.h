#ifndef SONGS_H
#define SONGS_H

struct Song {
  const char* artist;
  const char* title;
  const char* filename;
};

struct Artist {
  const char* artist;
  int start; // index of the first song of the artist
  int end;   // index of the last song of the artist 
};

class Songs {
  Song* songs_;
  int n_songs_;
  Artist* artists_;
  int n_artists_;
  int all_size_;
  char* all_;
  bool load_index_(const char* index);
  bool assign_songs_();
  bool assign_artists_();
public:
  Songs(): songs_(0), n_songs_(0), artists_(0), n_artists_(0) {}

  bool load(const char* index) {
    return load_index_(index) && assign_songs_() && assign_artists_();
  }

  int get_n_artists() { return n_artists_; }

  const char* get_artist(int an) {
    return artists_[an].artist;
  }

  int get_n_songs(int an) {
    Artist* a = &artists_[an];
    return a->end - a->start + 1;
  }

  const Song& get_song(int an, int sn) {
    return songs_[artists_[an].start + sn];
  }
};

#endif /* SONGS_H */
