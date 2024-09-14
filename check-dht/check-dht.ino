#include <DHT.h>

#define DHTPIN 8       // Define the pin where the DHT sensor is connected
#define DHTTYPE DHT11  // Define the type of DHT sensor

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  dht.begin();           // Initialize the DHT sensor
}

void loop() {
  float kelembaban = dht.readHumidity();        // Read humidity from DHT sensor
  float suhu = dht.readTemperature();          // Read temperature from DHT sensor

  // Check if any reads failed and exit early (0% or NaN values indicate failure)
    if (isnan(kelembaban) || isnan(suhu)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

  // Print the humidity and temperature values to the Serial Monitor
    Serial.print("kelembaban: ");
    Serial.print(kelembaban);
    Serial.print(" % ");
    Serial.print("suhu: ");
    Serial.print(suhu);
    Serial.println(" C");

  delay(2000); // Wait for 2 seconds before the next read
}
