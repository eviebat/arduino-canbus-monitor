/*****************************************************************************************
* This is implementation of CAN BUS ASCII protocol based on LAWICEL v1.3 serial protocol
*  of CAN232/CANUSB device (http://www.can232.com/docs/can232_v3.pdf)
*
* Made for Arduino with Seeduino/ElecFreaks CAN BUS Shield based on MCP2515
*
* Copyright (C) 2015 Anton Viktorov <latonita@yandex.ru>
*                                    https://github.com/latonita/arduino-canbus-monitor
*
* This library is free software. You may use/redistribute it under The MIT License terms. 
*
*****************************************************************************************/

#include <SPI.h>
#include "mcp_can.h"
#include "can-232.h"
#include "SoftwareSerial.h"

#define DEBUG_MODE

#define CAN_2515

#ifdef CAN_2515
  #include "mcp2515_can.h"
  const int SPI_CS_PIN = 9;
  const int CAN_INT_PIN = 2;
  mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

void setup() {
	  Serial.begin(LW232_DEFAULT_BAUD_RATE); // default COM baud rate is 115200. 

    Can232::init(CAN_500KBPS, MCP_8MHz); // set default rate you need here and clock frequency of CAN shield. Typically it is 16MHz, but on some MCP2515 + TJA1050 it is 8Mhz

    // optional custom packet filter to reduce number of messages comingh through to canhacker
     Can232::setFilter(myCustomAddressFilter); 
}

INT8U myCustomAddressFilter(INT32U addr) {
    INT8U ret = LW232_FILTER_SKIP; //LW232_FILTER_PROCESS or LW232_FILTER_SKIP
    switch(addr) {
        case 0x122: // tesla torque limits
            ret = LW232_FILTER_PROCESS;
            break;
        case 0x222: //tesla torque 
            ret = LW232_FILTER_PROCESS;
            break;
        default:
            ret = LW232_FILTER_SKIP;
            break;
    }
  return ret;
}

void loop() {
    Can232::loop();
}

void serialEvent() {
    Can232::serialEvent();
}

