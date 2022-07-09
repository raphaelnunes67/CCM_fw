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
        LedOnBoardController(WIFI_LED_pin, HIGH);
        delay(200);
        LedOnBoardController(WIFI_LED_pin, LOW);
        delay(200);
      }
      break; 

    case 1:

      IPAddress apIP(192, 168, 1, 1);
      WiFi.mode(WIFI_AP);
      WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
      WiFi.softAP(ssid, password);
      LedOnBoardController(WIFI_LED_pin, HIGH);
      break;  
  }
}

void ReconnectWifi(){
  if (WiFi.status() != WL_CONNECTED){
    
    MotorController(MOTOR_PIN, HIGH);
    RelayController(RELAY_PIN, LOW);
    
    String settings;
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, settings);
    String ssid = doc["wifi"]["wifi_ssid"].as<String>();
    String password = doc["wifi"]["wifi_password"].as<String>();
    InitWifi(STATION, ssid, password);

  }
}