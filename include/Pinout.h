#ifndef PINOUT
#define PINOUT

const int INTERRUPT_PIN = 0;
const int RST_MCP_PIN = 2;
const int GEN_PIN = 4;
const int RX_0_ULTRASSONIC_PIN = 5;
const int TX_0_ULTRASSONIC_PIN = 13;
const int MOTOR_PIN = 12;
const int RX_1_ULTRASSONIC_PIN = 14;
const int TX_1_ULTRASSONIC_PIN = 15;
const int ANALOG_PIN = 17;

const int WIFI_LED_MCP_PIN = 1;
const int MQTT_LED_MCP_PIN = 2;
const int WEB_SERVER_LED_MCP_PIN = 3;
const int SOLENOID_MCP_PIN = 4;
const int RELAY_1_MCP_PIN = 5;
const int RELAY_2_MCP_PIN = 5;

const int DUTY_CYCLE_VALUE = 132;

#define ON true
#define OFF false

#define OPEN false
#define CLOSE true

void pinoutBegin(void);
void ledController(int led_pin, bool state);
void commandRelay(int pin, bool state);
void commandSolenoid(int pin, bool state);
void commandMotor(bool state);

#endif