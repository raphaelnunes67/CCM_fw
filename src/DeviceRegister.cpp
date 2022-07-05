#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <FileSystem.h>
#include <Pinout.h>


void HandleRegister(){
  
}


void HandleNotFound(){

}

void DeviceRegister() {
  ESP8266WebServer server(80);
  
  digitalWrite(WIFI_LED_pin, LOW);
  digitalWrite(MQTT_LED_pin, HIGH);

  server.on("/", HandleRegister);
  server.onNotFound(HandleNotFound);
  server.begin();

}