#include <WiFi.h>
#include <Wire.h>
#include "esp_wpa2.h"
#include <ThingsBoard.h>
#include "keys.h"
#include "reading.h"
 
#define SLAVE_ADDR 9 
 
#define I2C_SDA 21
#define I2C_SCL 22

const char* ssid = "eduroam";
WiFiClient espClient;
int status = WL_IDLE_STATUS;
ThingsBoard tb(espClient);
static uint16_t messageCounter = 0; // count values sent

// Initialize ThingsBoard client
// the Wifi radio's status
void connectWifi() {
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);
  WiFi.disconnect(true); //disconnect from wifi to set new wifi connection
  WiFi.mode(WIFI_STA);
  //init wifi mode
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  WiFi.begin(ssid);
  //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println("");
  Serial.println(F("WiFi is connected!"));
  Serial.println(F("IP address set: "));
  Serial.println(WiFi.localIP()); //print LAN IP
}

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  connectWifi();
  Serial.println("Starting...");
}

void loop() { 
  delay(1000);
  Wire.requestFrom(SLAVE_ADDR, sizeof(Reading));

  // Initialize byte array for raw data to be read
  byte data[sizeof(Reading)] = {0};
 
  // Read I2C bytes into byte array
  for (int i = 0; i < sizeof(Reading) && Wire.available(); i++) {
    byte d = Wire.read();
    data[i] = d;
  }

  // Create Reading pointer to byte array
  Reading* reading = (Reading*)data;

  // Reconnect to WiFi, if needed
  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
    return;
  }
  
  // Reconnect to ThingsBoard, if needed
  if (!tb.connected()) {
    
    // Connect to the ThingsBoard 
    Serial.print("Connecting to: "); 
    Serial.print(THINGSBOARD_SERVER); 
    Serial.print(" with token "); 
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    } 
  }
  
  messageCounter++;
  
  Serial.print("Sending data...[");
  Serial.print(messageCounter);
  Serial.print("]: ");
  /* Serial.println(r); */
  Serial.println(reading->temp);
  Serial.println(reading->ph);
  Serial.println(reading->rpm);
  
  // Uploads new telemetry to ThingsBoard using MQTT.
  // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api
  // for more details
  /* tb.sendTelemetryInt("count", messageCounter); */
  /* tb.sendTelemetryFloat("randomVal", r); */
  tb.sendTelemetryFloat("temperature", reading->temp);
  tb.sendTelemetryFloat("pH value", reading->ph);
  tb.sendTelemetryFloat("stirring speed", reading->rpm);

  
  // Process messages
  tb.loop();
}
