#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <Pinout.h>

Adafruit_MCP23X17 mcp;

void PinoutBegin(){
  mcp.begin_I2C();
  //mcp.pinMode(WIFI_LED_pin, OUTPUT); mcp.digitalWrite(WIFI_LED_pin, HIGH);
  pinMode(WIFI_LED_pin, OUTPUT); digitalWrite(WIFI_LED_pin, HIGH);
}

void LedController(int led_pin, bool state){
  mcp.digitalWrite(led_pin, state);
}

void LedOnBoardController(int led_pin, bool state){
  mcp.digitalWrite(led_pin, state);
}

void RelayController(int pin, bool state){

}

void MotorController(int pin, bool state){

}