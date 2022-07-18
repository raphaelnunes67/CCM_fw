#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <Arduino.h>

class FileSystem {

  public:
    FileSystem();
    void checkSystemVersion(void);
    String LoadSettings(void);
    void SaveSettings(String settings);
    String ReadHtml(void);

};


#endif