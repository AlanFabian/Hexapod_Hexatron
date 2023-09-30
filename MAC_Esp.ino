
// Simple code to retreive the WiFi MAC address
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP32)
  #include "ESP32WiFi.h"
#else
  // Non supported board
  #error This board is not supported
#endif
void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(WiFi.macAddress());
}
void loop(){
}
