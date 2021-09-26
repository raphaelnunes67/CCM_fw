/*
  ****************************************
           GeneralDefinitions.h
   Script para ESP8266MOD (Cisterna)
   Autor: Raphael Nunes
   E-mail: raphaelnunes67@gmail.com
  ****************************************
*/
//Define pins
const int WIFI_LED_pin = 12; //Led Red
const int MQTT_LED_pin = 2; //Led Blue
const int INTERRUPT_pin = 0;
const int MOTOR_pin = 14;
const int GATE_pin = 5;
const int CURRENT_SENSOR_pin = 17; // A0
const int WL_ECHO_pin = 13;
const int WL_TRIG_pin = 15;
const int GEN_pin = 4;
//Wake_pin => 16
//Web Server and DNS server
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer server(80); // Web Sever on port 80
//Variables
String MotorONOFF, Gate, WaterLevel, Current;
String ssid, password, port, br_add, br_usr, br_pass, subs, pubs;
String message;
bool Motor_State = false, Gate_State = false, Lock = false, Set_Timer = false; // Motor OFF and Gate Closed
const int time_pub = 1000; // Delay of each MQTT publication (1s)
const int time_sleep_s = 300; // Sleep time in seconds
const int ap_time_ms = 180000; //Access point is open for 3 minutes
const int try_connect_ms = 120000; // Time to try a connection (MQTT and WIFI); (ms)
const int duty_cycle_value = 132; // PWM value to use voltage doubler
//File System
File file;
//MQTT PubSubClient config.
WiFiClient EspClient;
PubSubClient client(EspClient);
//Time config
WiFiUDP ntpUDP;
const int timeZone = -4;
NTPClient ntpClient(ntpUDP, "a.ntp.br", timeZone*3600, 60000);
//Water Level Sensor
const int MAX_DISTANCE = 120;
NewPing sonar (WL_TRIG_pin, WL_ECHO_pin, MAX_DISTANCE);
MedianFilter filter (31,0);


// Set pins IO and initial values
void SetPins() {
  pinMode(WIFI_LED_pin, OUTPUT); digitalWrite(WIFI_LED_pin, HIGH);
  pinMode(MQTT_LED_pin, OUTPUT); digitalWrite(MQTT_LED_pin, HIGH);
<<<<<<< HEAD
  pinMode(MOTOR_pin, OUTPUT); digitalWrite(MOTOR_pin, LOW);
  pinMode(GATE_pin, OUTPUT); digitalWrite(GATE_pin, HIGH);
=======
  pinMode(MOTOR_pin, OUTPUT); analogWrite(MOTOR_pin, 255);
  pinMode(GATE_pin, OUTPUT); digitalWrite(GATE_pin, LOW);
>>>>>>> 9ce17eb26c7b03ea257da107b4d34c4eaf87adfe
  //pinMode(WL_ECHO_pin, INPUT);
  //pinMode(WL_TRIG_pin, OUTPUT); digitalWrite(WL_TRIG_pin, LOW);
  pinMode(GEN_pin, OUTPUT); analogWrite(GEN_pin, duty_cycle_value); 
  pinMode(INTERRUPT_pin, INPUT_PULLUP);
#ifdef DEBUG
  Serial.println("\nPinos setados.");
#endif
}
// END - Set and define initial pin values

// Show int and fw version in serial
void ShowSystemVersion() {
  if (SPIFFS.exists("/system_info.json")) {
    file = SPIFFS.open("/system_info.json", "r");
    String output = file.readString();
    file.close();
    DynamicJsonDocument doc (512);
    deserializeJson(doc, output);
    JsonObject obj = doc.as<JsonObject>();
    String FW_version = obj[("fw_ver")].as<String>();
    String Interface_version = obj[("int_ver")].as<String>();
    Serial.print("Versão do Firmware: ");
    Serial.println(FW_version);
    Serial.print("Versão da interface de cadastro: ");
    Serial.println(Interface_version);
  }
}
//END - ShowSystemVersion
