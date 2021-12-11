float highlevel ;
float lowlevel;
unsigned long RPM;
int Userinput = 1000;
float Val = 70;
float RPMaverage = 0;
float RPMtotal = 0;
int times=0;

void setup() {
pinMode(6, INPUT);
pinMode(5,OUTPUT);
Serial.begin(9600);

}

void loop() {
unsigned long duration;
highlevel = pulseIn(6, HIGH);
lowlevel = pulseIn(6, LOW);
duration = highlevel+lowlevel;
RPM=30000000/duration;
if( duration == 0 ) {RPM = 0;}
Serial.print("the RPM is\n");
Serial.print("\t");
Serial.print(String(RPM) + "\n");

unsigned long ll=Userinput-20;
unsigned long  ul=Userinput+20;

if(RPM<ll) {
    Val = Val+0.1;
    if(Val>255){ Val = 255;}
    analogWrite(5,Val);
    Serial.print("The value of PWM 1 is ");
    Serial.println(Val);
    Serial.print("The value of RPM is ");
    Serial.println(RPM);
    delay(100);
    //times = times+1;
    
   }
  else if(RPM>=ll&&RPM<=ul){
    // turn the pin on:
    Val = Val;
    analogWrite(5,Val);
   Serial.print("The value of PWM 2 is ");
    Serial.println(Val);
   Serial.print("The value of RPM is ");
    Serial.println(RPM);
    delay(100);
    //times = times+1;
        }
   else if(RPM>ul){
    Val = Val-0.1;
    if(Val<0){ Val = 0;}
    analogWrite(5,Val);
    Serial.print("The value of PWM 3 is ");
    Serial.println(Val);
    Serial.print("The value of RPM is ");
    Serial.println(RPM);
    delay(100);
    //times = times+1;
    }

   /*if(times<=10){
   RPMtotal = RPMtotal + RPM;
   RPMaverage = RPMtotal/times;
   }
   else (times>10);{
    RPMaverage = 0;
    RPMtotal = 0;
    times = 0;
   RPMtotal = RPMtotal + RPM;
   RPMaverage = RPMtotal/times;
   Serial.print("The value of RPMtotal is ");
   Serial.println(RPMtotal);
   }*/
   }
