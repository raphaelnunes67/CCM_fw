
/*
  ****************************************
              Driver_RWS.h
   Script para ESP8266MOD (Cisterna)
   Autor: Raphael Nunes
   E-mail: raphaelnunes67@gmail.com
  ****************************************
*/
// Motor controller
void CommandMotor(bool Command) {
  Motor_State = Command;
  digitalWrite(MOTOR_pin, Motor_State);
}
// END - Motor controller

// Gate controller
void CommandGate(bool Command) {
  Gate_State = Command;
  digitalWrite(GATE_pin, Gate_State);
}
// END - Gate controller

// Make a JSON Serialized
String GetJSONSerialized(String value0, String value1) {
  DynamicJsonDocument doc (512);
  String input = "{}";
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();
  obj[String("MotorStatus")] = String(Motor_State);
  obj[String("GateStatus")] = String(Gate_State);
  obj[String("WaterLevel")] = value1;
  obj[String("Current")] = value0;
  String output;
  serializeJson(doc, output);
  return output;
}
// END - Make a JSON Serialized

// Get Current Value(Sensor )
String GetCurrent() {
  long I;
  if (Motor_State == false) {
    I = 0;
    return String(I);
  }
  else if (Motor_State == true) {
    I = random(60, 110);
    float i = (I / 10.0);
    return String(i);
  }
}
// END - Get Current Value

// Get Water Level(Sensor SR04T)
String GetWaterLevel() {
  //  long Level;
  //  Level = random(5, 121);
  unsigned int o = 0, uS;
  for (int i = 0; i <7; i++){
  delay(50);
  uS = sonar.ping();
  filter.in(uS);
  o = filter.out();
  }
#ifdef DEBUG
  Serial.println(o);
#endif
  return String(o / US_ROUNDTRIP_CM);
}
// END - Get Water Level

// Aux function to readValues
String ReadValues() {
  Current = GetCurrent();
  WaterLevel = GetWaterLevel();

  return GetJSONSerialized(Current, WaterLevel);
}
// - END Aux function

char SaveTime_upgrade(char intORfw) {
  //ntpClient.update();
  ntpClient.begin();
  delay(2000);
  ntpClient.forceUpdate();
  String TIME = ntpClient.getFormattedDate();
  file = SPIFFS.open("/system_info.json", "r");
  String system_info = file.readString();
  file.close();
  DynamicJsonDocument doc (512);
  deserializeJson(doc, system_info);
  JsonObject obj = doc.as<JsonObject>();
  if (intORfw == 'i') {
    obj[("last_update_int")] = TIME;
  }
  else if (intORfw == 'f') {
    obj[("last_update_fw")] = TIME;
  }
  system_info = "";
  serializeJson(doc, system_info);
  file = SPIFFS.open("/system_info.json", "w");
  file.print(system_info);
  file.close();
}
String UpdateVC_link(String New_VC_link) {
  int pFrom = New_VC_link.indexOf("\"new_vc_link\":\"") + 1;
  int pTo = New_VC_link.indexOf("\"}");
  New_VC_link = New_VC_link.substring(pFrom);
  file = SPIFFS.open("/system_info.json", "r");
  String system_info = file.readString();
  file.close();
  DynamicJsonDocument doc (512);
  deserializeJson(doc, system_info);
  JsonObject obj = doc.as<JsonObject>();
  obj[("VC_link")] = New_VC_link;
  system_info = "";
  serializeJson(doc, system_info);
  file = SPIFFS.open("/system_info.json", "w");
  file.print(system_info);
  file.close();
}
