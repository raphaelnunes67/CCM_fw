#include<Api.h>
#include<Arduino.h>
#include<Pinout.h>
#include<ArduinoJson.h>

#define DEBUG

void callback(char* topic, byte* payload, unsigned int length){
  
  #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
  #endif

  payload[length] = '\0';
  String received_message = String((char*)payload);

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, received_message);

  if (error) {
    #ifdef DEBUG
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
    #endif
    return;
  }

  int command = doc["command"];
  const char* fota_link = doc["fota_link"];

  switch (command)
  {
  case OPEN_SOLENOID:{
    commandSolenoid(SOLENOID_MCP_PIN, OPEN);
    break;
  }
  case CLOSE_SOLENOID:{
    commandSolenoid(SOLENOID_MCP_PIN, CLOSE);
    break;
  }
  case TURN_ON_MOTOR:{
    commandMotor(ON);
    break;
  }
  case TURN_OFF_MOTOR:{
    commandMotor(OFF);
    break;
  }
  case OPEN_RELAY_1:{
    commandRelay(RELAY_1_MCP_PIN, OPEN);
    break;
  }
   case CLOSE_RELAY_1:{
    commandRelay(RELAY_1_MCP_PIN, CLOSE);
    break;
  }
  case OPEN_RELAY_2:{
    commandRelay(RELAY_2_MCP_PIN, OPEN);
    break;
  }
   case CLOSE_RELAY_2:{
    commandRelay(RELAY_2_MCP_PIN, CLOSE);
    break;
  }
  
  case GET_WATER_LEVEL:{
    break;
  }
  case GET_FULL_STATUS:{
    break;
  }
  
  default:
    break;
  }
  if(fota_link != "" ;
}