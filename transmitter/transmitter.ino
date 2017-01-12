/*
  Created on Jan 2017
  Agung Pambudi <agung.pambudi5595@gmail.com>
*/

#include "instruction_packet_transmitter.h"

InstructionPacketTransmitterClass MultiServo;

void setup(){ 
  MultiServo.begin(Serial1, 115200);
}

void loop(){
  // Set goal position all servo
  MultiServo.setGoalPos('R', 50, 50, 50, 50, 50, 254);
  delay(1500);
  MultiServo.setGoalPos('R', 0, 0, 0, 0, 0, 254);
  delay(3000);
  MultiServo.setGoalPos('R', 150, 150, 150, 150, 150, 254);
  delay(1500);
  MultiServo.setGoalPos('R', 0, 0, 0, 0, 0, 50);
  delay(3000);
  MultiServo.setGoalPos('R', 50, 50, 50, 50, 50, 15);
  delay(1500);
  MultiServo.setGoalPos('L', 0, 0, 0, 0, 0, 15);
  delay(3000);

  // Set goal position one servo
  MultiServo.setGoalPos('R', 1, 50, 254);
  delay(1500);
  MultiServo.setGoalPos('R', 1, 0, 254);
  delay(1500);
}
