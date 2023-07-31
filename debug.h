#ifndef DEBUG

#define DEBUG(s, x)  do { Serial.print(F(s)); Serial.print(x); } while(false)
#define DEBUGX(s, x) do { Serial.print(F(s)); Serial.print(F("0x")); Serial.print(x, HEX); } while(false)
#define DEBUGS(s)    do { Serial.print(F(s)); } while (false)
#define DEBUGSP(fmt, x)  do { char b[128]; sprintf(b, fmt, x);  Serial.print(b); } while(false)
#define FATAL(s) do { DEBUGS(s); M5.Lcd.print(F(s)); } while(false)
#define ERROR(s) do { DEBUGS(s); M5.Lcd.print(F(s)); } while(false)

#endif
