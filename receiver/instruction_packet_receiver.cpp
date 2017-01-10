/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "instruction_packet_receiver.h"

//################################################################################## Setup serial for a specified serial object #####
void InstructionPacketReceiverClass::begin(HardwareSerial &HWserial, long baud){
  HWserial.begin(baud);  
  _serial = &HWserial;
}

//########################################################################################################## Stop communication #####
void InstructionPacketReceiverClass::end(HardwareSerial &HWserial){ HWserial.end(); }

//############################################################################################################ CONFIG SERVO PIN #####
void InstructionPacketReceiverClass::configServo(char dir, int pinM1, int pinM2, int pinM3, int pinM4, int pinM5){
  dir = dir;
  servo1.attach(pinM1);
  servo2.attach(pinM2);
  servo3.attach(pinM3);
  servo4.attach(pinM4);
  servo5.attach(pinM5);
}

//############################################################################################# RECEIVE DATA PACKET INSTRUCTION #####
void InstructionPacketReceiverClass::receiveData(void){
  while(_serial->available()){
    char inChar = (char)_serial->read();
    if(inChar == 'F'){ headerFind = 1;}
    else if(headerFind == 1 && (inChar == 'R' || inChar == 'L')){ 
      if(inChar != dir){ headerFind = 0; }
      else { headerFind = 2; }
    }else if(headerFind == 2){
      dataRX[indexData] = (int)inChar;
      indexData++;
      if(indexData >= dataRXSum){ headerFind = indexData = 0; }
    }else { headerFind = indexData = 0; }
  }
}

//############################################################################################################# PROCESSING DATA #####
void InstructionPacketReceiverClass::processData(void){
  dataRX[0] = dataRX[0] & 0x00ff;   //### M1L
  dataRX[1] = dataRX[1] << 8;       //### M1H
  dataRX[2] = dataRX[2] & 0x00ff;   //### M2L
  dataRX[3] = dataRX[3] << 8;       //### M2H
  dataRX[4] = dataRX[4] & 0x00ff;   //### M3L
  dataRX[5] = dataRX[5] << 8;       //### M3H
  dataRX[6] = dataRX[6] & 0x00ff;   //### M4L
  dataRX[7] = dataRX[7] << 8;       //### M4H
  dataRX[8] = dataRX[8] & 0x00ff;   //### M5L
  dataRX[9] = dataRX[9] << 8;       //### M5H

  dataRX[10] = dataRX[10] & 0x00ff; //### SML
  dataRX[11] = dataRX[11] << 8;     //### SMH

  m1 = dataRX[0] | dataRX[1];       //### VALUE FROM GOAL POSITION OF SERVO MOTOR 1
  m2 = dataRX[2] | dataRX[3];       //### VALUE FROM GOAL POSITION OF SERVO MOTOR 2
  m3 = dataRX[4] | dataRX[5];       //### VALUE FROM GOAL POSITION OF SERVO MOTOR 3
  m4 = dataRX[6] | dataRX[7];       //### VALUE FROM GOAL POSITION OF SERVO MOTOR 4
  m5 = dataRX[8] | dataRX[9];       //### VALUE FROM GOAL POSITION OF SERVO MOTOR 5

  sm = dataRX[10] | dataRX[11];     //### VALUE FROM SPEED SERVO MOTOR

  goalPos(m1, m2, m3, m4, m5, sm);
}

//##################################################################################################### GOAL POSITION & VELOCITY #####
//### gp = Goal Position,  ssm = Speed Servo Motor
void InstructionPacketReceiverClass::goalPos(int gp1, int gp2, int gp3, int gp4, int gp5, int ssm){  
  if(dir == 'L'){   //### Reverse position
    gp1 = abs(gp1-180);
    gp2 = abs(gp2-180);
    gp3 = abs(gp3-180);
    gp4 = abs(gp4-180);
    gp5 = abs(gp5-180);
  }
  
  servo1.write(gp1, ssm);
  servo2.write(gp2, ssm);
  servo3.write(gp3, ssm);
  servo4.write(gp4, ssm);
  servo5.write(gp5, ssm);
}

//####################################################################################################### GOAL POSITION DEFAULT #####
void InstructionPacketReceiverClass::goalPosDefault(void){
  goalPos(0, 0, 0, 0, 0, 254);  //### position open
  delay(2500);
}