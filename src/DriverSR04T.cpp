#include<DriverSR04T.h>
#include<Arduino.h>
#include<SoftwareSerial.h>
#include<Definitions.h>

int getDistance(uint8_t RX, uint8_t TX){
  SoftwareSerial sr04tSerial(RX, TX);
  sr04tSerial.begin(SERIAL_SR04T_BAUD_RATE);
  sr04tSerial.write(0x55);
  delay(50);
  if (!sr04tSerial.available()){
    return -1;
  }

  int distance;
  byte startByte, h_data, l_data, sum = 0;
  byte buf[3];
  
  startByte = (byte)sr04tSerial.read();
  if(startByte == 0xFF){
    sr04tSerial.readBytes(buf, 3);
    h_data = buf[0];
    l_data = buf[1];
    sum = buf[2];
    distance = (h_data<<8) + l_data;
    if(((startByte + h_data + l_data)&0xFF) != sum){
      #ifdef DEBUG
        Serial.println("Invalid result from SR04T");
      #endif
      return -1;
    }
    else{
      #ifdef DEBUG
        Serial.print("Distance [mm]: "); 
        Serial.println(distance);
      #endif
      return distance;
    } 
  } 
  return -1;

}


int getVolume(int distance1, int distance2){

}

uint8_t getOccupation(int volume){
  
}