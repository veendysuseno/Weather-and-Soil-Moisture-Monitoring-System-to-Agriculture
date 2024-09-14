#include <DHT.h>
#include <ESP8266WiFi.h>

#define DHTPIN D5
#define DHTTYPE DHT11

String apiKey = "N0DIXZNP8ZHW0DJM";           // Write API Key ThingSpeak
const char* ssid = "VEENDY-SUSENO";           // WiFi SSID
const char* password = "Admin12345";          // WiFi password
const char* server = "api.thingspeak.com";    // ThingSpeak server

int sensorPin = A0; // Analog pin for soil moisture sensor
int powerPin = D6;  // Digital pin to control power to the soil moisture sensor
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW); // Ensure sensor power is off initially
  dht.begin();
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  delay(2000); // Delay between readings

  // Read humidity and temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Read soil moisture
  int soilMoisture = readSensor();

  // Connect to ThingSpeak
  if (client.connect(server, 80)) {
    String postStr = "api_key=" + apiKey;
    postStr += "&field1=";
    postStr += String(h);           // Humidity
    postStr += "&field2=";
    postStr += String(t);           // Temperature
    postStr += "&field3=";
    postStr += String(soilMoisture); // Soil Moisture

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celsius ");
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);
    Serial.println("Sending data to ThingSpeak");
  } else {
    Serial.println("Connection to ThingSpeak failed");
  }

  client.stop();
  Serial.println("Waiting 20 secs");
  delay(20000); // Wait 20 seconds between updates
}

int readSensor() {
  // Turn on power to sensor
  digitalWrite(powerPin, HIGH);
  delay(500); // Allow sensor to stabilize

  int nilaiSensor = analogRead(sensorPin); // Read analog value from sensor
  digitalWrite(powerPin, LOW); // Turn off power to sensor

  return 1023 - nilaiSensor;  // Return the inverse of sensor value
}
