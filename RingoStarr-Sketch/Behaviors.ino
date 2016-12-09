// ************************************************************************************************************
// Behavior Code - The Ringo Starr Dance
// ************************************************************************************************************

#include "RingoHardware.h"
#include "Behaviors.h"
#include "FunStuff.h"

//byte vol; // volume used to calculate which dance to perform

void StopDancing(void){
  Motors(0,0);
  OffEyes();
}

void TheRingoStarrDance(void){
  for(int i=0; i<5; i++){
    int r = random(120);   
    int g = random(120);
    int b = random(120);
    int left = random(-200, 200);
    int right = random(-200, 200);
    OnEyes(r,g,b);
    Motors(left,right);
    delay(200);
    PlayAck();
  }
}


