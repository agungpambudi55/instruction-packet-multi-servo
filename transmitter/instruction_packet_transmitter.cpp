/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "instruction_packet_transmitter.h"

unsigned char dataTX[12];
unsigned int dataTXSum = 12;

//################################################################################# Set up Serial for a specified Serial object #####
void InstructionPacketTransmitterClass::begin(HardwareSerial &HWserial, long baud){
  HWserial.begin(baud);  
  _serial = &HWserial;
}

//########################################################################################################## Stop communication #####
void InstructionPacketTransmitterClass::end(HardwareSerial &HWserial){ HWserial.end(); }

// ################################################################################################# SET MULTIPLE GOAL POSITION #####
void InstructionPacketTransmitterClass::setGoalPos(char hh, int m1, int m2, int m3, int m4, int m5, int sm) {
  dataTX[0] = m1 & 0x00ff;  // M1L
  dataTX[1] = m1 >> 8;      // M1H
  dataTX[2] = m2 & 0x00ff;  // M2L
  dataTX[3] = m2 >> 8;      // M2H
  dataTX[4] = m3 & 0x00ff;  // M3L
  dataTX[5] = m3 >> 8;      // M3H
  dataTX[6] = m4 & 0x00ff;  // M4L
  dataTX[7] = m4 >> 8;      // M4H
  dataTX[8] = m5 & 0x00ff;  // M5L
  dataTX[9] = m5 >> 8;      // M5H
  
  dataTX[10] = sm & 0x00ff; // SML
  dataTX[11] = sm >> 8;     // SMH

  if(hh == 'R'){ _serial->print("FR");}     //### Header of instruction packet for right
  else if(hh == 'L'){_serial->print("FL");} //### Header of instruction packet for left

  _serial->write((byte*)dataTX, dataTXSum);
}

//################################################################################################### SET SINGLE GOAL POSITION #####
void InstructionPacketTransmitterClass::setGoalPos(char hh, int index, int m, int sm) {
  int m1, m2, m3, m4, m5;
  dataTX[0] = dataTX[0] & 0x00ff; //### M1L
  dataTX[1] = dataTX[1] << 8;     //### M1H
  dataTX[2] = dataTX[2] & 0x00ff; //### M2L
  dataTX[3] = dataTX[3] << 8;     //### M2H
  dataTX[4] = dataTX[4] & 0x00ff; //### M3L
  dataTX[5] = dataTX[5] << 8;     //### M3H
  dataTX[6] = dataTX[6] & 0x00ff; //### M4L
  dataTX[7] = dataTX[7] << 8;     //### M4H
  dataTX[8] = dataTX[8] & 0x00ff; //### M5L
  dataTX[9] = dataTX[9] << 8;     //### M5H

  m1 = (index == 1)? m : (dataTX[0] | dataTX[1]);     //### VALUE FROM GOAL POSITION OF SERVO MOTOR 1
  m2 = (index == 2)? m : (dataTX[2] | dataTX[3]);     //### VALUE FROM GOAL POSITION OF SERVO MOTOR 2
  m3 = (index == 3)? m : (dataTX[4] | dataTX[5]);     //### VALUE FROM GOAL POSITION OF SERVO MOTOR 3
  m4 = (index == 4)? m : (dataTX[6] | dataTX[7]);     //### VALUE FROM GOAL POSITION OF SERVO MOTOR 4
  m5 = (index == 5)? m : (dataTX[8] | dataTX[9]);     //### VALUE FROM GOAL POSITION OF SERVO MOTOR 5

  setGoalPos(hh, m1, m2, m3, m4, m5, sm);
}
