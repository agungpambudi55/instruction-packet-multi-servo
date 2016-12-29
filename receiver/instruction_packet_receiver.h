/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

// INSTRUCTION PACKET SERVO AS RECEIVER
// HH M1L M1H M2L M2H M3L M3H M4L M4H M5L M5H SML SMH
// HH (Header) => FL = Left / FR = Right
// M1, M2, M3, M4, M5 (Index Servo) => L = Low / H = High
// SM (Speed Motor) => 0 - 255 | SML(Low) / SMH(High)

#ifndef instruction_packet_receiver_h
#define instruction_packet_receiver_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include "servo_lib.h"

class InstructionPacketReceiverClass {
  public:    
    void begin(HardwareSerial &HWserial, long baud);                        //### Calling serial start function
    void end(HardwareSerial &HWserial);                                     //### Calling serial end function
    void configServo(char dir, int pinM1, int pinM2, int pinM3, int pinM4, int pinM5); //### CONFIG PIN
    void receiveData(void);                                                 //### RECEIVE DATA PACKET INSTRUCTION
    void processData(void);                                                 //### PROCESSING DATA
    void goalPos(int gp1, int gp2, int gp3, int gp4, int gp5, int ssm);     //### GOAL POSITION & VELOCITY
    void goalPosDefault(void);                                              //### GOAL POSITION DEFAULT
  
  private:
    Stream *_serial;                                                        //### Hardware serial RX/TX
    char dir;                                                               //### Direction, R = right, L = left
    unsigned int m1, m2, m3, m4, m5, sm;
    ServoLib servo1, servo2, servo3, servo4, servo5;
    int headerFind = 0, indexData = 0;
    unsigned char dataRX[12], dataRXSum = 12;
};
#endif
