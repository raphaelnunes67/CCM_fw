#ifndef FILE_SYSTEM
#define FILE_SYSTEM

#include <Arduino.h>
#include "LittleFS.h"

class FileSystem {

  public:
    FileSystem();
    void checkSystemVersion(void);
    String loadSettings(void);
    void saveSettings(String settings);
    void removeSettings();
    String readHtml(void);

};


#endif