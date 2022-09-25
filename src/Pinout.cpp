#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <Pinout.h>

#define DEBUG

Adafruit_MCP23X17 mcp;

void pinoutBegin(){

  pinMode(RX_0_ULTRASSONIC_PIN, INPUT);
  pinMode(TX_0_ULTRASSONIC_PIN, OUTPUT);
  pinMode(RX_1_ULTRASSONIC_PIN, INPUT);
  pinMode(TX_1_ULTRASSONIC_PIN, OUTPUT);
  pinMode(RST_MCP_PIN, OUTPUT);

  digitalWrite(RST_MCP_PIN, LOW);
  delay(10);
  digitalWrite(RST_MCP_PIN, HIGH);

  mcp.begin_I2C();
  
  mcp.pinMode(WIFI_LED_MCP_PIN, OUTPUT); mcp.digitalWrite(WIFI_LED_MCP_PIN, HIGH);
  mcp.pinMode(MQTT_LED_MCP_PIN, OUTPUT); mcp.digitalWrite(MQTT_LED_MCP_PIN, HIGH);
  mcp.pinMode(WEB_SERVER_LED_MCP_PIN, OUTPUT); mcp.digitalWrite(WEB_SERVER_LED_MCP_PIN, HIGH);
  mcp.pinMode(RELAY_1_MCP_PIN, OUTPUT); mcp.digitalWrite(RELAY_1_MCP_PIN, LOW);
  mcp.pinMode(RELAY_2_MCP_PIN, OUTPUT); mcp.digitalWrite(RELAY_2_MCP_PIN, LOW);
}

void LedController(int led_pin, bool state){
  mcp.digitalWrite(led_pin, !state);
}

void CommandRelay(int pin, bool state){
  mcp.digitalWrite(pin, state);
}

void CommandMotor(bool state){
  if (state){
    analogWrite(GEN_PIN, DUTY_CYCLE_VALUE);
    delayMicroseconds(50);
    for (int i=255; i>1; i--){
      analogWrite(MOTOR_PIN, i);
      delayMicroseconds(100);
    }
  }
  else{
    analogWrite(GEN_PIN, 0);
    analogWrite(MOTOR_PIN, 255);
  }

}