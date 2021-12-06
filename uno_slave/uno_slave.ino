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
 
void setup() { 
  Wire.begin(SLAVE_ADDR);                // join i2c bus with address #8 
  Wire.onRequest(onRequest);
  Serial.begin(115200);
  Serial.println("Starting...");
} 

void loop() {
  delay(100);
}
 
void onRequest() { 
  unsigned long spin_value; // 4 bytes
  float temp_value; // 4 bytes
  float ph_value; // 4 bytes
  spin_value = 31;
  temp_value = 16;
  ph_value = 10.0;

  byte data[12] = {0};

  *(unsigned long*)data = spin_value;
  *(float*)(data + 4) = temp_value;
  *(float*)(data + 8) = ph_value;

  /* unsigned long sv; */
  /* float tv; */
  /* float pv; */

  /* sv = *(unsigned long*)data; */
  /* tv = *(float*)(data + 4); */
  /* pv = *(float*)(data + 8); */

  /* Serial.println("Data:"); */
  /* Serial.println(sv); */
  /* Serial.println(tv); */
  /* Serial.println(pv); */

  Wire.write(data, 12);
}
