#include <Wire.h> 
#include "reading.h"
 
#define SLAVE_ADDR 9 
 
#define I2C_SDA 21
#define I2C_SCL 22

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(115200);
  Serial.println("Starting...");
}

void loop() { 
  Wire.requestFrom(SLAVE_ADDR, sizeof(Reading));

  // Initialize byte array for raw data to be read
  byte data[sizeof(Reading)] = {0};
 
  for (int i = 0; i < sizeof(Reading) && Wire.available(); i++) {
    byte d = Wire.read();
    data[i] = d;
  }

  // Convert byte array to struct
  Reading reading = *(Reading*)data;

  Serial.println("Data:");
  Serial.println(reading.rpm);
  Serial.println(reading.temp);
  Serial.println(reading.ph);

 
  delay(500); 
}
