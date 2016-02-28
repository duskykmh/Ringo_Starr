/* 
Ringo Robot
Ringo_Base_Sketch_Rev06
Version 6.1 12/2015

This is a basic sketch that can be used as a starting point
for various functionality of the Ringo robot.

Significant portions of this code written by
Dustin Soodak for Plum Geek LLC. Some portions
contributed by Kevin King.
Portions from other open source projects where noted.
This code is licensed under:
Creative Commons Attribution-ShareAlike 2.0 Generic (CC BY-SA 2.0)
https://creativecommons.org/licenses/by-sa/2.0/
Visit http://www.plumgeek.com for Ringo information.
Visit http://www.arduino.cc to learn about the Arduino.
*/

#include "RingoHardware.h"
#include "Behaviors.h"


//int i;    //declaire any global variables here

void setup(){
  HardwareBegin();        //initialize Ringo's brain to work with his circuitry
  PlayStartChirp();       //Play startup chirp and blink eyes
  SwitchMotorsToSerial(); //Call "SwitchMotorsToSerial()" before using Serial.print functions as motors & serial share a line
  RxIRRestart(4);         //wait for 4 byte IR remote command
  IsIRDone();
  GetIRButton();
  RestartTimer();
}
  
void loop(){
  restart:  //label to cause program to come back to here if "MENU" on remote is pressed in any example
  byte button;

  if(GetTime()>1000){   //blink rear pixel once a second to indicate Ringo is in "Menu" mode
      SetPixelRGB(0,0,0,100);   // turn on rear tail light to BLUE
      delay(10);                // brief delay
      OffPixels();              // turn off all pixels
      RestartTimer();           // zero timer
      } 
  
  if(IsIRDone()){                   //wait for an IR remote control command to be received
      button = GetIRButton();       // read which button was pressed, store in "button" variable

      if(button){                   // if "button" is not zero...
        switch (button){            // activate a behavior based on which button was pressed

         case 1:                    // Button 1, "Drive with remote control" behavior
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_DriveWithRemote();
         break;

         case 2:                    // Button 2, "Attack Bug" behavior
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_AttackBug();
         break;

         case 3:                    // Button 3, "The Ringo Dance" behavior
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_TheRingoDance();  // what it says NO EDGE DETECTION - DON'T LET RINGO JUMP OFF YOUR TABLE!
         break;

         case 4:                    // Button 4, "Spin Squeek" - Cover Ringo's eyes to activate 
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_SpinSqueek();
         break;

         case 5:                    // Button 5, "Color Wheel" - Ringo's eyes match the color wheel when rotated 
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_ColorWheel();     // virtual color wheel
         break;

         case 6:                    // Button 6, "Follow Light" - Ringo seeks light 
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_FollowLight();         
         break;

         case 7:                    // Button 7, "Drive Square" - Ringo drives in a square using navigation functions
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_DriveSquare();
         break;

         case 8:                    // Button 8, "Maintain Heading" - Rotate Ringo by hand and he'll return to start
                                    // Press User button and release to re-zero Ringo's heading
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_MaintainHeading();
         break;

         case 9:                    // Button 9, "Follow Line" - Ringo follows 1/2" (1cm) wide black line on white posterboard
         RxIRRestart(4);            // restart wait for 4 byte IR remote command
         Behavior_FollowLine();
         break;

         case 10:
         RxIRRestart(4);            // Button 0, "Explore Example" - Autonymous explore. Ringo avoids barriers and edges/lines on surface
         ExploreExample(160,60,500);//explore at speed 150 for 60 seconds and pause for 500ms afterwards for it to come to a halt
         break;
         
         default:                   // if no match, break out and wait for a new code
         PlayNonAck();              // quick "NonAck" chirp to know a known button was received, but not understood as a valid command
         RxIRRestart(4);            //wait for 4 byte IR remote command
         SwitchMotorsToSerial();
         Serial.print("button: ");Serial.println(button);  // send button number pressed to serial window
      
         break;
        }
      }
    }//end if(IsIRDone())
}




