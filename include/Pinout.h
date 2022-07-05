#ifndef PINOUT
#define PINOUT

#define WIFI_LED_pin 2
#define MQTT_LED_pin 3
#define WEB_SERVER_LED_pin 5
#define RELAY_PIN 4
#define MOTOR_PIN 6

void PinoutBegin(void);
void LedController(int led_pin, bool state);
void LedOnBoardController(int led_pin, bool state);
void RelayController(int pin, bool state);
void MotorController(int pin, bool state);

#endif