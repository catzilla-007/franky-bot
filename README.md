# Franky Bot

Arduino library that collects sensor information and connects to Robin inspector using ESP8266-01. Robin inspector connects to Franky bot via HTTP REST.

This acts as the main library for integrating sensors for hydrophonics.

## Getting sensor information via HTTP `GET`

### Request

```
GET http://arduino.host
```

### Response

```json
{
  "type": "sensors",
  "water-temperature": 24,
  "tds": 557,
  "temperature": 32,
  "humidity": 70,
  "pH": 5.8
}
```

Response values may vary depending on how many sensors are enabled/attached to the Arduino.
