# Wemos D1 R1 ESP8266 Weather and Soil Moisture Monitoring System

## Overview

- This project leverages an ESP8266 Wemos D1 R1 microcontroller to monitor environmental conditions using a DHT11 sensor for temperature and humidity, and a soil moisture sensor. The data collected from these sensors is sent to ThingSpeak, an IoT platform that provides real-time data visualization.

## Components Required

- ESP8266 (Wemos D1 R1): A microcontroller with built-in WiFi.
- DHT11 Sensor: Measures temperature and humidity.
- Soil Moisture Sensor: Measures soil moisture levels.
- ThingSpeak Account: An IoT platform for data storage and visualization.

## Prerequisites

Before starting, ensure you have:

- Arduino IDE installed. or Visual Studio Code
- ESP8266 board package installed in the Arduino IDE.
- Required libraries:
  - DHT sensor library.
  - ESP8266WiFi library.
- A ThingSpeak account with a channel set up.

## Setup Instructions

Hardware Connections

- DHT11 Sensor:
  - VCC → 3.3V (on Wemos D1 R1)
  - GND → GND
  - DATA → D6 (on Wemos D1 R1)
- Soil Moisture Sensor:
  - VCC → 3.3V or 5V (depends on your sensor)
  - GND → GND
  - Analog Output Pin → A0 (on Wemos D1 R1)
- Power Control for Soil Moisture Sensor:
  - Control Pin → D7 (on Wemos D1 R1)

## ThingSpeak Setup

1. Sign up at ThingSpeak.
2. Create a new channel with the following fields:
   - Field 1: Humidity
   - Field 2: Temperature
   - Field 3: Soil Moisture
3. Copy your Write API Key from the channel settings and update the code with this key.

## Software Setup

1. Install required libraries:

   - In Arduino IDE, go to Sketch > Include Library > Manage Libraries.
   - Install DHT sensor library and ESP8266WiFi library.

2. Copy the provided code into the Arduino IDE.

3. Update the following parameters in the code:

```cpp
String apiKey = "Your_ThingSpeak_API_Key";  // Replace with your ThingSpeak API Key
const char* ssid = "Your_SSID";             // Replace with your WiFi SSID
const char* password = "Your_PASSWORD";     // Replace with your WiFi Password
```

4. Select Wemos D1 R1 from Tools > Board.
5. Upload the code to the ESP8266.

## Code Explanation

- This program reads data from the DHT11 and soil moisture sensor and sends it to ThingSpeak every 20 seconds.

- Main Functions:
  - WiFi Connection: Connects to your WiFi network using the provided SSID and password.
  - Sensor Readings: Reads humidity, temperature, and soil moisture data.
  - Data Transmission: Sends sensor data to ThingSpeak using HTTP POST requests.

## Full Code

```cpp
#include <DHT.h>
#include <ESP8266WiFi.h>

String apiKey = "Your_ThingSpeak_API_Key";   // Replace with your ThingSpeak API Key
const char* ssid = "Your_SSID";              // WiFi SSID
const char* password = "Your_PASSWORD";      // WiFi password
const char* server = "api.thingspeak.com";   // ThingSpeak server

#define DHTPIN D6
#define DHTTYPE DHT11

int sensorPin = A0;  // Pin for soil moisture sensor
int powerPin = D7;   // Pin to control power to the soil moisture sensor

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  int soilMoisture = readSensor();
  if (client.connect(server, 80)) {
    String postStr = "api_key=" + apiKey;
    postStr += "&field1=" + String(h);
    postStr += "&field2=" + String(t);
    postStr += "&field3=" + String(soilMoisture);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: " + String(server) + "\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: " + String(postStr.length()) + "\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("Waiting 20 secs");
  delay(20000);
}

int readSensor() {
  digitalWrite(powerPin, HIGH);
  delay(500);
  int nilaiSensor = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);
  return 1023 - nilaiSensor;
}
```

## Troubleshooting

- WiFi Connection Fails: Ensure the correct SSID and password are entered.
- Failed to Connect to ThingSpeak: Double-check your ThingSpeak API key and channel setup.
- Sensor Read Failures: Verify wiring and sensor connections.
