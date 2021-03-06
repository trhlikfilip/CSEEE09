// Wire Slave Sender 
// by Nicholas Zambetti <http://www.zambetti.com> 
 
// Demonstrates use of the Wire library 
// Sends data as an I2C/TWI slave device 
// Refer to the "Wire Master Reader" example for use with this 
 
// Created 29 March 2006 
 
// This example code is in the public domain. 
 
// Define Slave I2C Address 
#define SLAVE_ADDR 9 
 
#include <Wire.h> 
#include "reading.h"
#include "temperature.h"
#include "ph.h"
#include "stir.h"

Reading reading = { .rpm = 31, .temp = 27.5, .ph = 8.9 };
 
void setup() { 
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #8 
  Wire.onRequest(onRequest);
  Serial.begin(115200);
  Serial.println("Starting...");
  temperatureSetup();
  stirSetup();
  phSetup();
}

void loop() {
  delay(100);
  reading.rpm = stirLoop();
  reading.ph = phLoop();
  reading.temp = temperatureLoop();
}
 
void onRequest() { 
  byte* data = (byte*)&reading;
  Wire.write(data, sizeof(Reading));
}
