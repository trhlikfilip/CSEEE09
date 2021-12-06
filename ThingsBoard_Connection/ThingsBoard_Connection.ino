#include <WiFi.h>  // WiFi control for ESP32
#include "esp_wpa2.h"
#include <ThingsBoard.h>  // ThingsBoard SDK

// WiFi control for ESP32
//wpa2 library for connections to Enterprise networks
#define EAP_IDENTITY "zcabcno@ucl.ac.uk"
#define EAP_PASSWORD "yA%9hpsEE#FMCG"

// See https://thingsboard.io/docs/getting-started-guides/helloworld/
#define TOKEN               "B6HPmgTJcFhlNa1zdLC7"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"

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
  connectWifi();
}


void loop() {
  
  delay(1000);
  
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
  
  /* float r = (float)random(1000)/1000.0; */
  float t = (float)random(6000)/1000.0 + 20.0;
  float ph = (float)random(4000)/1000.0 + 5;
  float stir = (float)random(1000)/10.0 + 400.0;
  messageCounter++;
  
  Serial.print("Sending data...[");
  Serial.print(messageCounter);
  Serial.print("]: ");
  /* Serial.println(r); */
  Serial.println(t);
  Serial.println(ph);
  Serial.println(stir);
  
  // Uploads new telemetry to ThingsBoard using MQTT.
  // See https://thingsboard.io/docs/reference/mqtt-api/#telemetry-upload-api
  // for more details
  /* tb.sendTelemetryInt("count", messageCounter); */
  /* tb.sendTelemetryFloat("randomVal", r); */
  tb.sendTelemetryFloat("temperature", t);
  tb.sendTelemetryFloat("pH value", ph);
  tb.sendTelemetryFloat("stirring speed", stir);

  
  // Process messages
  tb.loop();
}
