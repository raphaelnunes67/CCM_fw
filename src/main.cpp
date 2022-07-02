#include <Arduino.h>
#include <Pinout.h>
#include <FileSystem.h>
#include <ArduinoJson.h>
#include <DriverWifi.h>
#include <DriverMqtt.h>

String settings;
FileSystem file_system;
DynamicJsonDocument doc(1024);

void setup()
{
  PinoutBegin();

  settings = file_system.LoadSettings();

  if (settings == "ERROR")
  {
    InitWifi("access_point", "ConfigureCCM", "ConfigureCCM");
  }

  deserializeJson(doc, settings);

  InitWifi("station", doc["wifi"]["wifi_ssid"], doc["wifi"]["wifi_password"]);
  InitMqtt(doc["mqtt"]);
}

void loop()
{

  // mcp.digitalWrite(WIFI_LED_pin, HIGH);
}