#include <vector>
//using namespace std;

int soundSensorPin = A0;
int LEDPin = 5;
int Threshold_Value = 0;
vector<int> cont;

void setup() {
  Serial.begin(9600);
  pins_init();
  Threshold_Value = setThreshold();
}

int setThreshold() {
  int cumulate = 0;
  int n = 0;
  for (int i =0; i < 1000; i++) {
    int sensorValue = analogRead(soundSensorPin);
    cumulate += sensorValue; // count the sum
    n++;
  }

  int avg = cumulate/n;
  return avg+5;
}

void loop() {
  delay(200);
  int sensorValue = analogRead(soundSensorPin);
  int Threshold_value = Threshold_value;
  
  //for (int i = 0; i < 50; i++) {
  // count how many items have been sumed
  //}
  
  Serial.println(Threshold_Value);
  Serial.print("sensorValue");
  Serial.println(sensorValue);
  delay(1);
  if (sensorValue > Threshold_value) {
    turnonLED();
    delay(200);
  }
  
  turnoffLED();
}

void pins_init() {
  pinMode(LEDPin,OUTPUT);
  pinMode(soundSensorPin , INPUT);
}

void turnonLED() {
  digitalWrite(LEDPin,HIGH);
}

void turnoffLED() {
  digitalWrite(LEDPin, LOW);
}


