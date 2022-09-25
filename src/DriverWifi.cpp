#include<Arduino.h>
#include<Pinout.h>
#include<Definitions.h>
#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#include<DriverWifi.h>
#include<FileSystem.h>

#define DEBUG

bool initWifi(int mode, String ssid, String password) {
  
  WiFi.mode(WIFI_OFF);
  delay(10);
  bool result = true;
  
  switch (mode){
    case STATION:{
      const unsigned long current_time = millis();
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      while ((WiFi.status() != WL_CONNECTED) && (millis() - current_time < 10000)){
        ledController(WIFI_LED_MCP_PIN, ON);
        delay(200);
        ledController(WIFI_LED_MCP_PIN, OFF);
        delay(200);
      }
      if (WiFi.status() != WL_CONNECTED){
        result = false;
      }
      break; 
    }

    case ACCESS_POINT:{
      IPAddress apIP(192, 168, 1, 1);
      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid, password);
      ledController(WIFI_LED_MCP_PIN, ON);
      #ifdef DEBUG
        Serial.println("Access Point iniciado!");
        Serial.print("IP address: ");
        Serial.println(WiFi.softAPIP());
      #endif
      break;  
    }
  }
  return result;
}

void reconnectWifi(){
  if (WiFi.status() != WL_CONNECTED){
    
    commandMotor(OFF);
    commandRelay(RELAY_1_MCP_PIN, OPEN);
    commandRelay(RELAY_2_MCP_PIN, OPEN);
    
    String settings;
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, settings);
    String ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String password = doc["wifi"]["wifi_password"].as<String>();
    initWifi(STATION, ssid, password);

  }
}