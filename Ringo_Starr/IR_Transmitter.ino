/*******************************
 *  irTransmitter (Draft)
 *  by Jacob Brown
 *  2-20-2016
 *  Note: This hasn't been
 *  tested yet. Possibly
 *  dangerous.
 ******************************/

#include <IRLib.h>
#define START_LISTENING 0xa // temporary 4-byte "data"
#define STOP_DANCING 0xb // temporary 4-byte "data"

IRsend irSender;

boolean ringoEnabled = false; // toggle boolean

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.read() == 0 && !ringoEnabled){ // if serial monitor reads 0 and Ringo is not enabled, data is sent to tell it to listen
    for (int i = 0; i < 5; i++) {
      irSender.send(UNKNOWN, START_LISTENING, 4); // unknown protocol - Ringo receives 4-byte packets
      delay(40); // slight delay (may be useful - if not, remove)
  }
    ringoEnabled = true;
  }
  

  if (Serial.read() == 1 && ringoEnabled){ // if serial monitor reads 1 and Ringo is enabled (dancing, listening, or otherwise), data is sent
                                           // to tell it to stop dancing
    for (int i = 0; i < 5; i++){
      irSender.send(UNKNOWN, STOP_DANCING, 4); // unknown protocol - Ringo receives 4-byte packet
      delay(40); // slight delay (may be useful - if not, remove)
  }
    ringoEnabled = false;
  }

}
