#include<Arduino.h>
#include<Pinout.h>
#include<Definitions.h>
#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#include<DriverWifi.h>

void InitWifi(int mode, String ssid, String password) {
  
  WiFi.mode(WIFI_OFF);
  delay(10);
  switch (mode){
    case 0:
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED){
        LedController(WIFI_LED_MCP_PIN, ON);
        delay(200);
        LedController(WIFI_LED_MCP_PIN, OFF);
        delay(200);
      }
      break; 

    case 1:

      IPAddress apIP(192, 168, 1, 1);
      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid, password);
      LedController(WIFI_LED_MCP_PIN, ON);
      break;  
  }
}

void ReconnectWifi(){
  if (WiFi.status() != WL_CONNECTED){
    
    CommandMotor(OFF);
    CommandRelay(RELAY_1_MCP_PIN, OPEN);
    CommandRelay(RELAY_2_MCP_PIN, OPEN);
    
    String settings;
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, settings);
    String ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String password = doc["wifi"]["wifi_password"].as<String>();
    InitWifi(STATION, ssid, password);

  }
}