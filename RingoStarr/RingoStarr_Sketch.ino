/*
Modified Ringo Robot Sketch
Original Author: Dustin Soodak
RingoStarr Project for CIS330 @ University of Oregon
Created: March 11th, 2016
Edited by: Jacob Brown, Max Dickinson, Kyle Holmberg, and Kristen Splonkowski
Sources: 
+ http//www.plumgeek.com for Ringo info.
+ http//www.arduino.cc to learn about Arduino.
*/

#include "Behaviors.h"
#include "RingoHardware.h"

byte msg;  // IR message buffer

void setup(){
  HardwareBegin();        //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();       //Play startup chirp and blink eyes
  SwitchMotorsToSerial(); //Call "SwitchMotorsToSerial()" before using Serial.print functions as motors & serial share a line
  RestartTimer();
  RxIRRestart(1);
  Serial.begin(9600);
}

byte current=0x0;

void loop(){ 
  if(IsIRDone()){ // if IR received
    RxIRStop(); //stop the receiving function
    current = IRBytes[0];
    TheRingoStarrDance();
    
    // USED TO DETERMINE HEX VALUE OF RECEIVED IR //
    /*
    if (current) {
      Serial.print("This is the current in the 'current' loop: ");
      Serial.println(current, HEX); //Used to find byte info on received IR
    }
    */
    
    RxIRRestart(1);
  }
  StopDancing();
  current = 0x0;
}
