#include "Arduino.h"

const int AciPump = 10;
const int AlkPump = 11;
const int pHSensor = A0;
const int minPH = 1; 
const int maxPH = 2;
const int idealPH = 5;

float pHReading = 0;
int AciPumpS = 0;
int AlkPumpS = 0;
float TruePH = 0;
int counter = 0;
int pointer = 0;
float avaregeVal[30];
float aPH = 0;

void setup() {
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

void loop() {
  // read the sensor and store it in the variable sensorReading:
  pHReading = analogRead(pHSensor);
  TruePH = (1803 - 3 * pHReading) / 37;
  Serial.print("Raw pH =");
  Serial.print(pHReading );
  Serial.print("  pH Value:");
  
  //stabilizer
  if(pointer>29){
    pointer = 0;
  }
  if(counter<30){
    avaregeVal[pointer] = TruePH;
    counter++;
    pointer++;
  }
  else{
    avaregeVal[pointer] = TruePH;
    aPH = average(avaregeVal,30);
    //Serial.println(TruePH);
    Serial.print(aPH);
    pointer++;
    }
  //Map the speed of the pump
  int SpeedBase=map(TruePH,0,minPH,255,200);
  int SpeedAcid=map(TruePH,14,maxPH,255,200);
  // pump activation
  if (TruePH > maxPH) {
    analogWrite(AciPump,130);
    digitalWrite(AlkPump,LOW);
    Serial.println("  Activating Acid Pump");
  }
  else if (TruePH < minPH) {
    analogWrite(AlkPump,130);
    digitalWrite(AciPump,LOW);
    Serial.println("  Activating Alkaline Pump");
  }
  else{
    Serial.println("Normal");
  }
}
