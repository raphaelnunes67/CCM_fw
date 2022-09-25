#include<Arduino.h>
#include<ArduinoJson.h>
#include<DriverMqtt.h>
#include<Pinout.h>

#include<Api.h>

#define DEBUG

WiFiClient EspClient;
PubSubClient client(EspClient);

bool connectMqtt(String mqtt_settings)
{

  bool connected;

  StaticJsonDocument<512> doc;
  deserializeJson(doc, mqtt_settings);
  String br_address = doc["br_address"].as<String>();
  int br_port = doc["br_port"].as<int>();
  String br_user = doc["br_user"].as<String>();
  String br_password = doc["br_password"].as<String>();
  String publish = doc["publish"].as<String>();
  String subscribe = doc["subscribe"].as<String>();

  String client_id = "device_" + String(ESP.getChipId(), HEX);

  char br_address_char[br_address.length() + 1];
  char br_user_char[br_user.length() + 1];
  char br_password_char[br_password.length() + 1];
  char subscribe_char[subscribe.length() + 1];
  char cliend_id_char[client_id.length()+ 1];

  br_address.toCharArray(br_address_char, br_address.length() + 1);

  br_user.toCharArray(br_user_char, br_user.length() + 1);
  br_password.toCharArray(br_password_char, br_password.length() + 1);
  subscribe.toCharArray(subscribe_char, subscribe.length() + 1);
  client_id.toCharArray(cliend_id_char, client_id.length() + 1);

  client.setServer(br_address_char, br_port);
  client.setCallback(callback);

  unsigned long current_time = millis();

  #ifdef DEBUG
    Serial.println("Tentando se conectar ao Broker... ");
  #endif

  connected = client.connect(cliend_id_char, br_user_char, br_password_char);
  while ((!connected) && (millis() - current_time < 10000)){
    connected = client.connect(cliend_id_char, br_user_char, br_password_char);
    ledController(WIFI_LED_MCP_PIN, ON);
    delay(200);
    ledController(WIFI_LED_MCP_PIN, OFF);
    delay(200);
  }

  if (connected == false){
    return connected;
  }

  #ifdef DEBUG
    Serial.println("Conectado!");
    Serial.print("IP Broker: ");
    Serial.print(br_address);
    Serial.print(". Porta: ");
    Serial.println(br_port);
    client.publish("test/ccm", "System ON!");
  #endif
  delay(500);
  client.subscribe(subscribe_char);

  #ifdef DEBUG
    Serial.println("Servico MQTT inicializado.");
    Serial.print("Inscrito em: [");
    Serial.print(subscribe);
    Serial.println("]");
    Serial.print("Publicando em: [");
    Serial.print(publish);
    Serial.println("]");
  #endif

  return connected;


}