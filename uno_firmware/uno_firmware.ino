
#include <ArduinoJson.h>

String message = "";
bool messageReady = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(Serial.available()) {
    message = Serial.readString();
    messageReady = true;
  }

  if(messageReady) {
    DynamicJsonDocument doc(1024); 

    DeserializationError error = deserializeJson(doc,message);
    if(error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }
    if(doc["type"] == "request") {
      doc["type"] = "response";
      doc["distance"] = "100";
      doc["gas"] = "100";
      serializeJson(doc,Serial);
    }
    messageReady = false;
  }
}
