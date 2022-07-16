#include<Arduino.h>
#include<SoftwareSerial.h>
#include<DriverUtrassonic.h>

#define DEBUG

int GetDistance(int8_t RX_pin, int8_t TX_pin){
  SoftwareSerial UltrassonicSerial(RX_pin, TX_pin);
  UltrassonicSerial.begin(ULTRASSONIC_BAUD_RATE);
  delay(10);
  UltrassonicSerial.write(START_MEASUREMENT);
  delay(50);

  if (UltrassonicSerial.available()){
    byte startByte, h_data, l_data, sum = 0;
    byte buf[3];
    int distance;

    startByte = (byte)UltrassonicSerial.read();
    if (startByte == NEW_MEASURE){
      UltrassonicSerial.readBytes(buf, 3);
      h_data = buf[0];
      l_data = buf[1];
      sum = buf[2];

      distance = (h_data<<8) + l_data;

      if(((startByte + h_data + l_data)&NEW_MEASURE) != sum){
        UltrassonicSerial.end();
        return -1;
      }   
      else{
        UltrassonicSerial.end();
        #ifdef DEBUG
          Serial.print("distance: ");
          Serial.println(distance);
        #endif
        return distance;
      }
    }
  }
  UltrassonicSerial.end();
  return -1;
}