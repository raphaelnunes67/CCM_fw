#include <Arduino.h>
#include "LittleFS.h"
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

String FileSystem::LoadSettings(void){

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

bool FileSystem::SaveSettings(String settings){
  return true;

}

String FileSystem::ReadHtml(void){

  file = LittleFS.open("/index.html", "r");
  String html_page = file.readString();
  file.close();
  return html_page;
}