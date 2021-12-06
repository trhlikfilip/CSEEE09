#include<math.h>
const int transistorPin = 9;
int brightness=0;
int ThermistorPin= A0; //define thermistor
int Vo;
float R1=10000;
float logR2, R2, T;
float c1= 1.009249522e-03, c2=2.378405444e-04,c3=2.019202697e-07;
float target_value = 30.0;

void setup (){
  Serial.begin (9600) ;
  pinMode (transistorPin, OUTPUT) ;
  pinMode (ThermistorPin, INPUT) ;
}
void loop (){

  Vo=analogRead(ThermistorPin) ;
  R2=R1* (1023.0/(float)Vo-1.0) ;
  logR2=log(R2);
  T=(1.0/(c1+c2*logR2+c3*logR2*logR2*logR2) ) ;
  T=T-273.15;
  Serial.print("Temperature=");
  Serial.print(T);
  Serial.print("C ");
  delay (1000) ;
  if (T<target_value-0.5){
    digitalWrite(transistorPin,HIGH);
    //delay(100);
    Serial.println("Status:ON");
    digitalWrite(11,HIGH);
  }
  else if(T>=target_value+0.5){
    digitalWrite(transistorPin,LOW);
    //delay(100);
    Serial.println("Status:OFF");
    digitalWrite(11,LOW);
  } 
}
