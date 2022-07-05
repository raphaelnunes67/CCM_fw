#ifndef DRIVER_WIFI
#define DRIVER_WIFI

#include <Arduino.h>

void InitWifi(char mode, String ssid, String password);
void ReconnectWifi(void);

#endif