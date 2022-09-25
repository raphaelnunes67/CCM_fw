#ifndef DRIVER_WIFI
#define DRIVER_WIFI

#include <Arduino.h>

enum {
  STATION,
  ACCESS_POINT
};

bool initWifi(int mode, String ssid, String password);
void reconnectWifi(void);

#endif