#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <Arduino.h>

class FileSystem {

  public:
    FileSystem();
    String LoadSettings(void);
    bool SaveSettings(String settings);
    String ReadHtml(void);

};


#endif