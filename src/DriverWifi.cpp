#include <Arduino.h>
#include <Pinout.h>
#include <ESP8266WiFi.h>
#include <DriverWifi.h>

void InitWifi(String mode, String ssid, String password) {

  WiFi.mode(WIFI_OFF);
  delay(10);

  if (mode == "station"){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED){
      LedController(WIFI_LED_pin, LOW);
      delay(500);
      LedController(WIFI_LED_pin, HIGH);
      delay(500);
    }
    
  }
  else if (mode == "access_point"){
    IPAddress apIP(192, 168, 1, 1);
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password);
    LedController(WIFI_LED_pin, LOW);
  }
  else if(mode == "access_point_station"){


  }
  else{
    // error
  }

}