# Soil Moisture Sensor Monitor

This project reads the soil moisture level from a sensor connected to an Arduino and displays the moisture level on the Serial Monitor. It also provides feedback on the soil condition based on predefined threshold values.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **Soil Moisture Sensor**
- **Connecting Wires**
- **Breadboard** (optional)

## Circuit Diagram

1. **Soil Moisture Sensor:**
   - **VCC** to 5V (or 3.3V depending on your board)
   - **GND** to GND
   - **Analog Output** to Analog Pin A0 (sensorPin)

## Software Requirements

- **Arduino IDE**

## Code

```cpp
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
```

## Setup Instructions

1. Connect the Hardware:

   - Connect the VCC pin of the soil moisture sensor to the 5V pin on the Arduino.
   - Connect the GND pin of the soil moisture sensor to the GND pin on the Arduino.
   - Connect the Analog Output pin of the soil moisture sensor to Analog Pin A0.

2. Upload the Code:

   - Open the Arduino IDE and paste the provided code into a new sketch.
   - Select the appropriate board and port.
   - Click on the upload button to transfer the code to your Arduino board.

3. Monitor the Data:
   - Open the Serial Monitor (Tools -> Serial Monitor).
   - Set the baud rate to 9600 to match the Serial.begin() setting in the code.
   - Observe the soil moisture readings and corresponding feedback messages.

## Troubleshooting

- No Data or Errors: Ensure the sensor is connected properly and that the Serial Monitor is set to the correct baud rate.
- Unexpected Readings: Verify that the sensor is functioning correctly and that the threshold values are appropriate for your soil conditions.
