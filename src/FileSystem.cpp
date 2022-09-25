#include <Arduino.h>
#include <FileSystem.h>

#define DEBUG

File file;

FileSystem::FileSystem(){
  #ifndef DEBUG
    LittleFS.begin();
  #endif

  #ifdef DEBUG
  if(!LittleFS.begin()){ 
    Serial.println("An Error has occurred while mounting LittleFS");
  }
  else{
    Serial.println("File system initialized!");
  }
  #endif
}

void FileSystem::checkSystemVersion(void){
  file = LittleFS.open("/system.json", "r");
  if (!file){
    file = LittleFS.open("/system.json", "w");
    file.print("{\"firmware_version\":\"1.0\"}");
    file.close();
  }
}

String FileSystem::loadSettings(void){

  file = LittleFS.open("/settings.json", "r");

  if (file){
    String settings = file.readString();
    file.close();
    #ifdef DEBUG
      Serial.println(settings);
    #endif
    return settings;
  }
  return "ERROR";
}

void FileSystem::saveSettings(String settings){
  file = LittleFS.open("/settings.json", "w");
  file.print(settings);
  file.close();
}

void FileSystem::removeSettings(){
  LittleFS.remove("/settings.json");
}

String FileSystem::readHtml(void){

  file = LittleFS.open("/index.html", "r");
  String html_page = file.readString();
  file.close();
  return html_page;
}

