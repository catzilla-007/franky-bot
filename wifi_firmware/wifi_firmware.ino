#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
char* ssid = "Southern iConnect";
char* password = "blackpink";

DynamicJsonDocument data(1024);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  Serial.print("Connecting.");
 
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  data["type"] = "initial";

  server.on("/", handleIndex);
  
  server.begin();
}

void loop() {
  server.handleClient();
  getData();
}

void getData() {
  String message = "";
  bool ready = false;

  DynamicJsonDocument doc(1024);
  
  // Get data from UNO serial
  if (Serial.available()) {
    message = Serial.readString();
    ready = true;  
  }

  if (ready) {
    DeserializationError error = deserializeJson(doc, message);
  
    if (error) {
      Serial.print("Failed to read data from UNO: ");
      Serial.println(error.c_str());
      ready = false;
      return;
    }
  
    if (doc["type"] != "sensors") {
      Serial.println("Invalid information");
      return;
    }

    Serial.println("Saving data");
    data = doc;
  }
}

void handleIndex() {
  String message;
  serializeJson(data, message);

  server.send(200, "application/json", message);  
}
