#include "ph.h"
#include <Arduino.h>

const int AciPump = 10;
const int AlkPump = 11;
const int pHSensor = A0;
const int minPH = 1; // = 3
const int maxPH = 2;
const int idealPH = 5;

float pHReading = 0;
int AciPumpS = 0;
int AlkPumpS = 0;
float TruePH = 0;
int counter = 0;
int pointer = 0;
float averageVal[30];
float aPH = 0;

void phSetup() {
  pinMode(AciPump, OUTPUT);
  pinMode(AlkPump, OUTPUT);
  Serial.begin(9600);
}

float average(float * array, int len) {
  long sum = 0L ;
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ; 
}

float phLoop() {
  // read the sensor and store it in the variable sensorReading:
  pHReading = analogRead(pHSensor);
  TruePH = (1803 - 3 * pHReading) / 37;
  Serial.print("Raw pH =");
  Serial.print(pHReading );
  Serial.print("  pH Value:");
  if (pointer>29){
    pointer = 0;
  }
  if (counter<30){
    averageVal[pointer] = TruePH;
    counter++;
    pointer++;
  }
  else {
    averageVal[pointer] = TruePH;
    aPH = average(averageVal,30);
    //Serial.println(TruePH);
    Serial.print(aPH);
    pointer++;
  }
  // 6/12/21 Values
  // Acid (4) = 552
  // Pure (7) = 515
  // Alkaline (10) = 480
  //TruepH = (1803-3[pH]) / 37
  //Map the speed of the pump
  int SpeedBase=map(TruePH,0,minPH,255,200);
  int SpeedAcid=map(TruePH,14,maxPH,255,200);
  // if the sensor reading is greater than the threshold:
  if (TruePH > maxPH) {
    //AciPumpS = !AciPumpS;
    analogWrite(AciPump,130);
    digitalWrite(AlkPump,LOW);
    Serial.println("  Activating Acid Pump");
  }
  else if (TruePH < minPH) {
    //AlkPumpS = !AlkPumpS;
    analogWrite(AlkPump,130);
    digitalWrite(AciPump,LOW);
    Serial.println("  Activating Alkaline Pump");
  }
  else {
    Serial.println("Normal");
  }
  return TruePH;
  //delay(300);
  //AciPumpS = LOW;
  //AlkPumpS = LOW;
  //delay(100);
}
