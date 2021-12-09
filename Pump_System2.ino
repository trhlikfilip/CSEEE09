#include "Arduino.h"

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
float avaregeVal[10];
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
  Serial.print("pH Value:");
  if(pointer>9){
    pointer = 0;
  }
  if(counter<10){
    avaregeVal[pointer] = TruePH;
    counter++;
    pointer++;
  }
  else{
    aPH = average(avaregeVal,10);
    Serial.println(aPH);
    pointer++;
    }
  // 6/12/21 Values
  // Acid (4) = 552
  // Pure (7) = 515
  // Alkaline (10) = 480
  //TruepH = (1803-3[pH]) / 37

  // if the sensor reading is greater than the threshold:
  if (pHReading < maxPH) {
    AciPumpS = !AciPumpS;
    analogWrite(AciPump,10);
    Serial.println("Activating Acid Pump");
  }
  else if (pHReading > minPH) {
    AlkPumpS = !AlkPumpS;
    digitalWrite(AlkPump, LOW);
    Serial.println("Activating Alkaline Pump");
  }
  delay(300);
  AciPumpS = LOW;
  AlkPumpS = LOW;
  delay(100);
}
