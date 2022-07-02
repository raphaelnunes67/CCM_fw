#include <Arduino.h>
#include <LittleFS.h>
#include <FileSystem.h>

File file;

FileSystem::FileSystem(){
  LittleFS.begin();
}

String FileSystem::LoadSettings(void){


  if (LittleFS.exists("/settings.json")){
    file = LittleFS.open("/settings.json", "r");
    String settings = file.readString();
    file.close();
    return settings;
  }

  return "ERROR";

}

bool FileSystem::SaveSettings(String settings){
  return true;

}