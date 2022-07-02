#ifndef PINOUT
#define PINOUT

#define WIFI_LED_pin 2
#define MQTT_LED_pin 3
#define RELAY_PIN 4

void PinoutBegin(void);
void LedController(int led_pin, bool state);
void RelayController(int pin, bool state);

#endif