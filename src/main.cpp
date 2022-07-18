#include<Arduino.h>
#include<Definitions.h>
#include<Pinout.h>
#include<FileSystem.h>
#include<ArduinoJson.h>
#include<RegisterDevice.h>
#include<DriverWifi.h>
#include<DriverMqtt.h>

#define DEBUG

void setup(){

  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.println();
  #endif

  delay(2000);
  PinoutBegin();
  String settings;
  FileSystem file_system;

  file_system.checkSystemVersion();
  settings = file_system.LoadSettings();

  if (settings == "ERROR"){
    #ifdef DEBUG
      Serial.println(F("settings file do not exists..."));
    #endif
    const String ap_ssid = "device_" + String(ESP.getChipId(), HEX);
    const String ap_password = "device_" + String(ESP.getChipId(), HEX);
    InitWifi(ACCESS_POINT, ap_ssid, ap_password);
    RegisterDevice();
    
  }
  else{

    StaticJsonDocument<512> doc;
    deserializeJson(doc, settings);
    String wifi_ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String wifi_password = doc["wifi"]["wifi_password"].as<String>();
  
    InitWifi(STATION, wifi_ssid, wifi_password);

    //InitMqtt(doc["mqtt"]);

  }
}

void loop(){
  // mcp.digitalWrite(WIFI_LED_pin, HIGH);
  ReconnectWifi();
  //ReconnectMqtt();
}