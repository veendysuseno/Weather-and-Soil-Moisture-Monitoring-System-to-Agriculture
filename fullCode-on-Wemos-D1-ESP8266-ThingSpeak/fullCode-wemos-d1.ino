#include <DHT.h>
#include <ESP8266WiFi.h>

// Replace with your channel’s ThingSpeak API key, SSID, and password
String apiKey = "CTRPQ51EAAPADZLU";
const char* ssid = "VEENDY-SUSENO";             // WiFi SSID
const char* password = "Admin12345";            // WiFi password
const char* server = "api.thingspeak.com";      // ThingSpeak server

#define DHTPIN D6   // Update this if needed for WEMOS D1 R1
#define DHTTYPE DHT11

int sensorPin = A0; // Pin for soil moisture sensor
int powerPin = D7;  // Pin to control power to the soil moisture sensor

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Set up the soil moisture sensor power control pin
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);

  // Initialize the DHT sensor
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

  // Connect to ThingSpeak and send data
  if (client.connect(server, 80)) {
    String postStr = "api_key=" + apiKey;
    postStr += "&field1=" + String(h);            // Humidity
    postStr += "&field2=" + String(t);            // Temperature
    postStr += "&field3=" + String(soilMoisture); // Soil Moisture

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: " + String(server) + "\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: " + String(postStr.length()) + "\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celsius Humidity: ");
    Serial.print(h);
    Serial.print(" % Soil Moisture: ");
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
  // Turn on power to the soil moisture sensor
  digitalWrite(powerPin, HIGH);
  delay(500); // Allow sensor to stabilize

  int nilaiSensor = analogRead(sensorPin); // Read analog value from sensor
  digitalWrite(powerPin, LOW); // Turn off power to sensor

  // Return the inverse of sensor value (higher value indicates more moisture)
  return 1023 - nilaiSensor;
}
