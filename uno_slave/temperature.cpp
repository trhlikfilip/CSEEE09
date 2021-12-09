#include "temperature.h"
#include<math.h>

#include<PID_v1.h>

//Define constants for Temperature calculation

const int transistorPin = 9;

int ThermistorPin= A0; //define thermistor

int Vo;

float R1=10000;

float logR2, R2, T;

float c1= 1.009249522e-03, c2=2.378405444e-04,c3=2.019202697e-07;

float target_value = 30.0;

 

//Define constants for PID control

double SetPoint;

double Input;

double Output;

double Kp=0,Ki=5,Kd=0;

 

//create PID instance

PID myPID(&Input,&Output,&SetPoint,Kp,Ki,Kd,DIRECT);

 

 

void temperatureSetup (){

 

  Serial.begin(9600) ;

  pinMode (transistorPin, OUTPUT) ;

  pinMode (ThermistorPin, INPUT) ;

 

  //Setting parameters for PID

  SetPoint=target_value-5;

  myPID.SetMode(AUTOMATIC);

  myPID.SetTunings(Kp,Ki,Kd);

 

}

float temperatureLoop (){

 

//Temperature Detection

  Vo=analogRead(ThermistorPin) ;

  R2=R1* (1023.0/(float)Vo-1.0) ;

  logR2=log(R2);

  T=(1.0/(c1+c2*logR2+c3*logR2*logR2*logR2) ) ;

  T=T-273.15;

  Serial.print("Temperature=");

  Serial.print(T);

  Serial.print("C ");

  //delay (1000) ;

 

  Input=T;

  myPID.Compute();

 

//Controller

  if (T<target_value-0.5){

    analogWrite(transistorPin,Output);

    //delay(100);

    Serial.println(Output);

  }

  else if(T>=target_value+0.5){

    analogWrite(transistorPin,Output);

    //delay(100);

    Serial.println(Output);

  }

  return T;

  

}
