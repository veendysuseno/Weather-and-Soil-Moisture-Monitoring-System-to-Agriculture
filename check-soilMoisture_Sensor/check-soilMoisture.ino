int sensorPin = A0; // Pin where the soil moisture sensor is connected
int nilai; // Variable to store sensor reading

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  nilai = analogRead(sensorPin); // Read the value from the soil moisture sensor
  Serial.print("Kelembaban Tanah: ");
  Serial.println(nilai); // Print the sensor value to the Serial Monitor

  // Determine soil condition based on sensor reading
  if (nilai > 700) { // Soil is dry
    Serial.println("Tanah Kering, Tolong Siram Air");
  } else if (nilai <= 700 && nilai > 350) { // Soil is normal
    Serial.println("Kelembaban normal Gan");
  } else { // Soil is wet
    Serial.println("Tanah Basah / Lembab Gan");
  }

  delay(500); // Wait for 500 milliseconds before the next reading
}
