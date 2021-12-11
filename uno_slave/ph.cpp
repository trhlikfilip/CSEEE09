#include "ph.h"
#include <Arduino.h>

const int AciPump = 10;
const int AlkPump = 11;
const int pHSensor = A1;
const int minPH = 3; // = 3
const int maxPH = 7;
const int idealPH = 5;

float pHReading = 0;
int AciPumpS = 0;
int AlkPumpS = 0;
float TruePH = 0;
int counter = 0;
int pointer = 0;
float avaregeVal[30];
float aPH = 0;


void phSetup() {
  pinMode(AciPump, OUTPUT);
  pinMode(AlkPump, OUTPUT);
  Serial.begin(9600);
}


float average (float * array, int len)
{
  long sum = 0L ;
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ; 
}


float phLoop() {
  pHReading = analogRead(pHSensor);
  TruePH = (1803 - 3 * pHReading) / 37;

  if (pHReading < maxPH) {
    AciPumpS = !AciPumpS;
    analogWrite(AciPump,10);
  } else if (pHReading > minPH) {
    AlkPumpS = !AlkPumpS;
    digitalWrite(AlkPump, LOW);
  }
  AciPumpS = LOW;
  AlkPumpS = LOW;

  if (pointer>29) {
    pointer = 0;
  }
  if (counter<30) {
    avaregeVal[pointer] = TruePH;
    counter++;
    pointer++;
    return(TruePH);
  } else {
    avaregeVal[pointer] = TruePH;
    aPH = average(avaregeVal,30);
    pointer++;
    return (float) aPH;
  }
}
