#include<Arduino.h>
#include<Definitions.h>
#include<RegisterDevice.h>
#include<ESP8266WebServer.h>
#include<FileSystem.h>
#include<Pinout.h>

ESP8266WebServer server(SERVER_PORT);

void HandleRegister(){
  FileSystem file_system;
  String html_page = file_system.ReadHtml();
  server.send(200, "text/html", html_page);
  
}

void HandleNotFound(){

}

void RegisterDevice() {
  
  LedController(WIFI_LED_MCP_PIN, OFF);
  LedController(MQTT_LED_MCP_PIN, OFF);

  server.on("/register", HandleRegister);
  server.onNotFound(HandleNotFound);
  server.begin();

  while(true){
    server.handleClient();
  }

}