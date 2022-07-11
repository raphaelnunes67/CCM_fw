#include <Arduino.h>
#include<Definitions.h>
#include <ESP8266WebServer.h>
#include <FileSystem.h>
#include <Pinout.h>


void HandleRegister(){
  
}


void HandleNotFound(){

}

void DeviceRegister() {
  
  ESP8266WebServer server(80);
  
  LedController(WIFI_LED_MCP_PIN, OFF);
  LedController(MQTT_LED_MCP_PIN, OFF);

  server.on("/", HandleRegister);
  server.onNotFound(HandleNotFound);
  server.begin();

}