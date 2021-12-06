#include <Wire.h> 
 
// Define Slave I2C Address. All slaves must be allocated a  
// unique number. 
 
#define SLAVE_ADDR 9 
 
// Define the pins used for SDA and SCL. This is important because  
// there is a problem with the TTGO and I2C will not work properly  
// unless you do. 
 
#define I2C_SDA 21
#define I2C_SCL 22

typedef struct {
  unsigned long rpm;
  float temp;
  float ph;
} Reading;
 
void setup() {
  Wire.begin (I2C_SDA, I2C_SCL);      // Configure the pins 
  Serial.begin(115200);                 // start serial for output
  Serial.println("Starting...");
}

void loop() { 
  Wire.requestFrom(SLAVE_ADDR, sizeof(Reading));


  byte data[sizeof(Reading)] = {0};
 
  for (int i = 0; i < sizeof(Reading) && Wire.available(); i++) {
    byte d = Wire.read();
    data[i] = d;
  }

  Reading reading = *(Reading*)data;

  Serial.println("Data:");
  Serial.println(reading.rpm);
  Serial.println(reading.temp);
  Serial.println(reading.ph);

 
  delay(500); 
}
