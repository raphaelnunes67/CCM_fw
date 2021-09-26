/*
  ****************************************
             Sleep_Functions.h
   Script para ESP8266MOD (Cisterna)
   Autor: Raphael Nunes
   E-mail: raphaelnunes67@gmail.com
  ****************************************
*/
// Sleep Function
void ESP_Sleep() {
  if (Motor_State == false) {
#ifdef DEBUG
    Serial.println("Indo dormir em 3s...");
#endif
    client.publish("TEST/SMCC", "GS");
    delay(3000);
    ESP.deepSleep(time_sleep_s * 1e6, WAKE_RF_DEFAULT); // Sleep 300s
  }
}
// END - Sleep Function


