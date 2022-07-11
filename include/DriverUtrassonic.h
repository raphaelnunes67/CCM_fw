#ifndef DRIVER_ULTRASSONIC
#define DRIVER_ULTRASSONIC

#define START_MEASUREMENT 0x55
#define NEW_MEASURE 0xFF
const int ULTRASSONIC_BAUD_RATE = 9600;

int GetDistance(int8_t RX_pin, int8_t TX_pin);

#endif