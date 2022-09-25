#ifndef _API_H_
#define _API_H_
#include<Arduino.h>

enum validMessages{
  OPEN_SOLENOID,
  CLOSE_SOLENOID,
  TURN_ON_MOTOR,
  TURN_OFF_MOTOR,
  OPEN_RELAY_1,
  CLOSE_RELAY_1,
  OPEN_RELAY_2,
  CLOSE_RELAY_2,
  GET_WATER_LEVEL,
  GET_FULL_STATUS
};

void callback(char* topic, byte* payload, unsigned int length);

#endif