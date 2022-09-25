#ifndef _DRIVER_SR04T_H
#define _DRIVER_SR04T_H
#include <Arduino.h>


int getDistance(uint8_t RX, uint8_t TX);
int getVolume(int distance1, int distance2);
uint8_t getOccupation(int volume);

#endif