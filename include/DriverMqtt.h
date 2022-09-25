#ifndef DRIVER_MQTT
#define DRIVER_MQTT

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>


bool connectMqtt(String mqtt_settings);

#endif