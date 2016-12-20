/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "instruction_packet_receiver.h"

int i=0;
int pos[] = {0, 45, 90, 135, 180};
int vel[] = {75, 25, 150, 200, 254};

InstructionPacketReceiverClass MultiServo;

void setup(){
  Serial.begin(115200);
  MultiServo.begin(Serial1, 115200);
  MultiServo.configServo('L', 3, 5, 6, 10, 9);
  MultiServo.goalPosDefault();
}

void loop(){
  // Manual test without transmitter
  while(false){
    MultiServo.goalPos(pos[i], pos[i], pos[i], pos[i], pos[i], vel[i]);
    Serial.print(" pos => "); 
    Serial.print(pos[i]);
    Serial.print(" vel => "); 
    Serial.print(vel[i]);
    Serial.println();
    delay(2500);
    i++;
    if(i>4)i=0;
  }

  // Execution instuction packet from transmitter
  while(true){
    MultiServo.receiveData();
    MultiServo.processData();
  }
}
