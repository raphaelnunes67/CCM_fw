#include<Arduino.h>
#include<Definitions.h>
#include<RegisterDevice.h>
#include<ESP8266WebServer.h>
#include<FileSystem.h>
#include<Pinout.h>
#include<ArduinoJson.h>

#define DEBUG

ESP8266WebServer server(SERVER_PORT);

void HandleRegister(){

  FileSystem file_system;
  String html_page = file_system.readHtml();
  if (server.hasArg("ssid") && server.hasArg("password") && server.hasArg("br_address")
      && server.hasArg("br_port") && server.hasArg("br_user") && server.hasArg("br_password")
      && server.hasArg("publish") && server.hasArg("subscribe") && server.hasArg("client_name") 
      && server.hasArg("fota_link")) { 

    String settings;
    StaticJsonDocument<384> doc;
    JsonObject wifi = doc.createNestedObject("wifi");
    wifi["wifi_ssid"] = server.arg("ssid");
    wifi["wifi_password"] = server.arg("password");

    JsonObject mqtt = doc.createNestedObject("mqtt");
    mqtt["br_address"] = server.arg("br_address");
    mqtt["br_port"] = server.arg("br_port");
    mqtt["br_user"] = server.arg("br_user");
    mqtt["br_password"] = server.arg("br_password");
    mqtt["publish"] = server.arg("subscribe");
    mqtt["subscribe"] = server.arg("pusblish");
    doc["fota_link"] = server.arg("fota_link");

    serializeJson(doc, settings);
    file_system.saveSettings(settings);
    delay(2000);
    ESP.restart();
    
  }
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
  
  ledController(WIFI_LED_MCP_PIN, OFF);
  ledController(MQTT_LED_MCP_PIN, OFF);

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