/*
  ESP8266 firmware:
  Heavily influenced by 
  https://github.com/datasith/Ai_Tips_ESP8266/blob/master/esp8266_arduino_comm/esp8266_firmware/esp8266_firmware.ino
*/

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
char* ssid = "Southern iConnect";
char* password = "blackpink";

void setup() {
  WiFi.begin(ssid, password);
  Serial.begin(9600);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleIndex);
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleIndex() {
  DynamicJsonDocument doc(1024);
  doc["type"] = "request";
  serializeJson(doc, Serial);

  boolean messageReady = false;
  String message = "";

  while (messageReady == false) {
    if (Serial.available()) {
      message = Serial.readString();
      messageReady = true;
    }
  }

  DeserializationError error = deserializeJson(doc, message);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  distance = doc["distance"];
  gas = doc["gas"];
  String output = "distance: test";
  output += "CO level: test";

  // server.send(200, "application/json", output);  
}
