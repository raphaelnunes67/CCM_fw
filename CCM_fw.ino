
/*
  ****************************************
                 SMCC_main.ino
   Script para ESP8266MOD (Cisterna)
   Autor: Raphael Nunes
   E-mail: raphaelnunes67@gmail.com
  ****************************************
*/
//# Define DEBUG
//Includes
//#include "Arduino.h"
#include "Libraries.h"
#include "GeneralDefinitions.h"
#include "Interruptions.h"
#include "Sleep_Functions.h"
#include "SimpleBlink.h"
#include "Driver_ConfigSMCC.h"
#include "Driver_RWS.h"
#include "Driver_WIFI.h"
#include "OTA_Upgrade.h"
#include "Driver_MQTT.h"

void setup() {
#ifdef DEBUG
  Serial.begin(115200); // Serial debug
#endif
  SPIFFS.begin();
  SetPins();  // Defines the pins and their initial values
#ifdef DEBUG
  ShowSystemVersion();
#endif  
  SetInterrupt(); //Defines interrupt routines (Factory reset)
  VerifyConfigJSON(); // Checks whether registration data is saved in the file system
  initWIFI(); //Starts WIFI 
  OTA_arduino_upgrade(); //Enables updating via Arduino IDE
  initMQTT();//Starts MQTT comunication
}

void loop() {
  ArduinoOTA.handle(); // Keeps OTA update via arduino IDE always available
  client.loop(); // MQTT loop (callbacks)
  if (Lock) {SendValues();} // Lock == true (When the pump is on, time monitoring is activated)
  reconnectWIFI(); //Always check the WI FI connection and with the MQTT server
  reconnectMQTT();
}
