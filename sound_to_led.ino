// rotate potentiometer counter clockwise

struct params {
int soundSensorPin;
int LEDPin;
int Threshold_Value;
int sensorValue;
} first;

//unsigned long timeinit = millis();
void setParams(){
first.soundSensorPin = A1;
first.LEDPin = 5;
//first.Threshold_Value = 0;
}
void printT(){
  Serial.print("ThresholdValue");
Serial.println(first.Threshold_Value);
  Serial.print("sensorValue");
  Serial.println(first.sensorValue);
 }
 

int setSensorValue() {
  int cumulate = 0;
  int n =0;
  //for (int i =0; i < 10; i++){
    first.sensorValue = analogRead(first.soundSensorPin);
    
   // delay(2);
    //cumulate += first.sensorValue; // count the sum
    //n++;
//}
  //int avg = cumulate/n;
  //first.sensorValue = analogRead(first.soundSensorPin);

  return first.sensorValue;
}
int setThreshold() 
//set at 2 more than average over 1000 milli seconds
{
int cumulate = 0;
int n =0;
first.sensorValue = 0;
for (int i =0; i < 1000; i++){
  first.sensorValue = analogRead(first.soundSensorPin);
  cumulate += first.sensorValue; // count the sum
  n++;
}
int avg = cumulate/n;
return avg+400;
}



void pins_init()
{
  pinMode(first.LEDPin,OUTPUT);
  pinMode(first.soundSensorPin , INPUT);
}

void turnonLED()
{
  digitalWrite(first.LEDPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);  
}
void turnoffLED(){
  digitalWrite(first.LEDPin, LOW);    // turn the LED off by making the voltage LOW
  delay(500);  
 
}               
void setup(){
  Serial.begin(9600);
  setParams();
  pins_init();
  first.Threshold_Value = setThreshold();
}

void loop()
{
  first.sensorValue = setSensorValue();
  printT();

     
     if (first.sensorValue > first.Threshold_Value) {
      turnonLED();
     }
    
      
}
                                                                                                                                                                                                                                                                                                                                                                                                                      
