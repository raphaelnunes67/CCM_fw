#include<Arduino.h>
#include<Definitions.h>
#include<RegisterDevice.h>
#include<ESP8266WebServer.h>
#include<FileSystem.h>
#include<Pinout.h>

#define DEBUG

ESP8266WebServer server(SERVER_PORT);


void HandleRegister(){
  FileSystem file_system;
  String html_page = file_system.ReadHtml();
  server.send(200, "text/html", html_page);
  
}

void HandleNotFound(){

  #ifdef DEBUG
    Serial.println("redirection...");
  #endif
  server.sendHeader("Location", "/",true); 
  server.send(302, "text/plane","");
}

void RegisterDevice() {
  
  LedController(WIFI_LED_MCP_PIN, OFF);
  LedController(MQTT_LED_MCP_PIN, OFF);

  server.on("/", HandleRegister);
  server.onNotFound(HandleNotFound);
  server.begin();
  #ifdef DEBUG
    Serial.println("Server initialized!");
  #endif

  while(true){
    server.handleClient();
  }

}