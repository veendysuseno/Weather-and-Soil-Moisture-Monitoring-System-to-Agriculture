# DHT Sensor Data Logger

This project reads humidity and temperature data from a DHT11 sensor and outputs the readings to the Serial Monitor. The data is collected every 2 seconds and displayed in a format suitable for monitoring environmental conditions.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **DHT11 Sensor** (or DHT22, if using a different model)
- **Connecting Wires**
- **Breadboard** (optional)

## Circuit Diagram

1. **DHT11 Sensor:**
   - **VCC** to 5V (or 3.3V depending on your board)
   - **GND** to GND
   - **Data** to Digital Pin 8 (or the pin you define as `DHTPIN` in your code)

## Software Requirements

- **Arduino IDE**
- **DHT Library** (you can install it via the Library Manager in the Arduino IDE)

## Code

```cpp
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
```

## Setup Instructions

1. Connect the Hardware:

   - Connect the VCC pin of the DHT11 sensor to the 5V pin on the Arduino.
   - Connect the GND pin of the DHT11 sensor to the GND pin on the Arduino.
   - Connect the Data pin of the DHT11 sensor to Digital Pin 8 (or the pin defined as DHTPIN in your code).

2. Install the DHT Library:

   - Open the Arduino IDE.
   - Go to Sketch -> Include Library -> Manage Libraries.
   - Search for "DHT" and install the library by Adafruit.

3. Upload the Code:

   - Open the Arduino IDE and paste the provided code.
   - Select the appropriate board and port.
   - Click on the upload button to transfer the code to your Arduino board.

4. Monitor the Data:
   - Open the Serial Monitor (Tools -> Serial Monitor).
   - Set the baud rate to 115200 to match the Serial.begin() setting in the code.
   - Observe the humidity and temperature readings displayed every 2 seconds.

## Troubleshooting

- No Data or Errors: Ensure that the sensor is connected correctly and that the library is properly installed. Check the serial monitor for any error messages.
- Incorrect Readings: Verify that you are using the correct pin for the sensor and that the sensor is not damaged.
