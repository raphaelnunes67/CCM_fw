#ifndef DRIVER_WIFI
#define DRIVER_WIFI

#include <Arduino.h>

void InitWifi(int mode, String ssid, String password);
void ReconnectWifi(void);

#endif