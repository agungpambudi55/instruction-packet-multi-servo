/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

// INSTRUCTION PACKET SERVO AS TRANSMITTER
// HH M1L M1H M2L M2H M3L M3H M4L M4H M5L M5H SML SMH
// HH (Header) => FL = Left / FR = Right
// M1, M2, M3, M4, M5 (Index Servo) => L = Low / H = High
// SM (Speed Motor) => 0 - 255 | SML(Low) / SMH(High)

#ifndef instruction_packet_transmitter_h
#define instruction_packet_transmitter_h

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class InstructionPacketTransmitterClass{
  public:
    void begin(HardwareSerial &HWserial, long baud);  //### Calling serial start function
    void end(HardwareSerial &HWserial);               //### Calling serial end function
    //### Set goal position
    void setGoalPos(char hh, int m1, int m2, int m3, int m4, int m5, int sm);
    void setGoalPos(char hh, int index, int m, int sm);
  private:
    Stream *_serial;                                  //### Hardware serial RX/TX
};
#endif
