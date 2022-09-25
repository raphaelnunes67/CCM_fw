#include<Arduino.h>
#include<Wire.h>
#include<Definitions.h>
#include<Pinout.h>
#include<FileSystem.h>
#include<ArduinoJson.h>
#include<RegisterDevice.h>
#include<DriverWifi.h>
#include<DriverMqtt.h>

#define DEBUG

void i2cBegin(){
    Wire.begin();
    Wire.setClock(STANDARD_MODE);
}

void setup(){

  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();
  #endif

  delay(2000);
  
  i2cBegin();
  pinoutBegin();
  String settings;
  FileSystem file_system;

  file_system.checkSystemVersion();
  settings = file_system.loadSettings();

  if (settings == "ERROR"){
    #ifdef DEBUG
      Serial.println(F("settings file do not exists..."));
    #endif
    const String ap_ssid = "device_" + String(ESP.getChipId(), HEX);
    const String ap_password = "device_" + String(ESP.getChipId(), HEX);
    initWifi(ACCESS_POINT, ap_ssid, ap_password);
    RegisterDevice();
    
  }
  else{

    StaticJsonDocument<512> doc;
    deserializeJson(doc, settings);
    String wifi_ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String wifi_password = doc["wifi"]["wifi_password"].as<String>();

    #ifdef DEBUG
      Serial.println(F("settings file exists..."));
    #endif
  
    if (!initWifi(STATION, wifi_ssid, wifi_password)){
      file_system.removeSettings();
      ESP.restart();
    }

    if (!connectMqtt(doc["mqtt"])){
      file_system.removeSettings();
      ESP.restart();
    } 
  }
}

void loop(){
  // mcp.digitalWrite(WIFI_LED_pin, HIGH);
  reconnectWifi();
  //ReconnectMqtt();
  if (ENABLE_POOLING){
    
  }
}