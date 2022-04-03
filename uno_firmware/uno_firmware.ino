
#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  DynamicJsonDocument doc(1024);

  doc["type"] = "sensors";

  doc["temperature"] = "40";

  doc["humidity"] = "70%";

  serializeJson(doc, Serial);

  delay(2000);
}
