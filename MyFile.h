#ifndef MY_FILE_H
#define MY_FILE_H

#include <M5Stack.h>
#include <Arduino.h>

const int O_READ = 0;

class MyFile {
  uint64_t pos_;
  uint8_t* buf_;
public:
  MyFile(): pos_(0), buf_(0) {}

  ~MyFile() {
    if (buf_) { free(buf_); }
  }

  bool open(const char* fname, int mode) {
    String s(fname);
    File f = SD.open('/' + s, FILE_READ);
    if (!f.available()) {
      Serial.print("Cannot open '");
      Serial.print(fname);
      Serial.print("'\n");
      return false;
    }
    size_t sz = f.size();
    buf_ = (uint8_t*)malloc(sz);
    if (buf_ == 0) {
      Serial.print("Out of memory for ");
      Serial.print(fname);
      Serial.print("'\n");
      return false;
    }
    f.read(buf_, sz);
    f.close();
    pos_ = 0;
    return true;
  }

  void close() {
    if (buf_) { free(buf_); }
    buf_ = 0;
  }

  int fgets(char* buf, int size) {
    int i;
    for (i = 0; i < size - 1; i++) {
      buf[i] = buf_[pos_ + i];
    }
    pos_ += i;
    return i;
  }

  int read() {
    return (int)(unsigned int)buf_[pos_++];
  }

  uint64_t curPosition() {
    return pos_;
  }

  bool seekSet(uint64_t pos) {
    pos_ = pos;
    return true;
  }

  bool seekCur(int64_t offset) {
    pos_ += offset;
    return true;
  }
};


#endif /* MY_FILE_H */
