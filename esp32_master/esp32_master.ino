#include <Wire.h> 
 
// Define Slave I2C Address. All slaves must be allocated a  
// unique number. 
 
#define SLAVE_ADDR 9 
 
// Define the pins used for SDA and SCL. This is important because  
// there is a problem with the TTGO and I2C will not work properly  
// unless you do. 
 
#define I2C_SDA 21
#define I2C_SCL 22
 
void setup() {
  Wire.begin (I2C_SDA, I2C_SCL);      // Configure the pins 
  Serial.begin(115200);                 // start serial for output
  Serial.println("Starting...");
}

void loop() { 
  Wire.requestFrom(SLAVE_ADDR, 12);

  unsigned long spin_value;
  float temp_value;
  float ph_value;

  byte data[12] = {0};
 
  for (int i = 0; i < 12 && Wire.available(); i++) {
    byte d = Wire.read();
    data[i] = d;
  }

  spin_value = *(unsigned long*)data;
  temp_value = *(float*)(data + 4);
  ph_value = *(float*)(data + 8);

  Serial.println("Data:");
  Serial.println(spin_value);
  Serial.println(temp_value);
  Serial.println(ph_value);

 
  delay(500); 
}
