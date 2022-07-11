#include <Arduino.h>
#include <Definitions.h>
#include <Pinout.h>
#include <FileSystem.h>
#include <ArduinoJson.h>
#include <DriverWifi.h>
#include <DriverMqtt.h>

void setup(){

  String settings;
  FileSystem file_system;
  //Serial.begin(115200);
  PinoutBegin();

  settings = file_system.LoadSettings();

  if (settings == "ERROR"){

    const String ap_ssid = "device_" + String(ESP.getChipId(), HEX);
    const String ap_password = "device_" + String(ESP.getChipId(), HEX);
    InitWifi(ACCESS_POINT, ap_ssid, ap_password);
    
  }
  else{

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, settings);

    String ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String password = doc["wifi"]["wifi_password"].as<String>();
  
    InitWifi(STATION, ssid, password);

    //InitMqtt(doc["mqtt"]);

  }
}

void loop(){
  // mcp.digitalWrite(WIFI_LED_pin, HIGH);
  ReconnectWifi();
  //ReconnectMqtt();
}