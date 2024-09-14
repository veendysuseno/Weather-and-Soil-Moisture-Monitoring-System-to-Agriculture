# Soil Moisture and Temperature Control System

This project involves using an Arduino to monitor soil moisture and temperature, displaying the data on an LCD, and controlling relays to manage a light and a pump based on the readings.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **DHT11 Sensor** (for temperature and humidity)
- **Soil Moisture Sensor**
- **16x2 LCD with I2C Interface**
- **2 Relay Modules**
- **Connecting Wires**
- **Power Source**

## Software Requirements

- **Arduino IDE**
- **LiquidCrystal_I2C Library** (for controlling the LCD)
- **DHT Library** (for reading the DHT11 sensor)

## Circuit Diagram

1. **DHT11 Sensor:**

   - VCC to 5V
   - GND to GND
   - Data to Digital Pin 8 (DHTPIN)

2. **Soil Moisture Sensor:**

   - VCC to 5V
   - GND to GND
   - Analog Output to Analog Pin A0 (sensorPin)

3. **LCD (I2C):**

   - VCC to 5V
   - GND to GND
   - SDA to A4 (SDA)
   - SCL to A5 (SCL)

4. **Relay Modules:**

   - **Relay1 (Light):**
     - IN to Digital Pin 3 (RELAY1)
   - **Relay2 (Pump):**
     - IN to Digital Pin 5 (RELAY2)

5. **Power Pin for Soil Moisture Sensor:**
   - Power Pin to Digital Pin 6 (powerPin)

## Code

```cpp
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11
#define RELAY1 3 // Light
#define RELAY2 5 // Pump

int sensorPin = A0;
int powerPin = D6;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Can also be 0x3f
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  lcd.begin();
  dht.begin();
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
}

void loop() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);

  int soilMoisture = readSensor();

  lcd.setCursor(0, 0);
  lcd.print("K. Tanah: ");
  lcd.print(soilMoisture);

  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.print(t);
  lcd.print("C ");

  Serial.print("K. Tanah: ");
  Serial.println(soilMoisture);
  Serial.print("Suhu: ");
  Serial.println(t);

  if (t > 30) {
    digitalWrite(RELAY1, LOW); // Turn on light
  } else {
    digitalWrite(RELAY1, HIGH); // Turn off light
  }

  if (soilMoisture < 200) {
    digitalWrite(RELAY1, LOW); // Turn on light (when soil moisture is low)
    digitalWrite(RELAY2, LOW); // Turn on pump
  } else {
    digitalWrite(RELAY1, HIGH); // Turn off light
    digitalWrite(RELAY2, HIGH); // Turn off pump
  }

  delay(2000);
}

int readSensor() { // Read soil moisture sensor
  digitalWrite(powerPin, HIGH);
  delay(500);
  int nilaiSensor = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);
  return 1023 - nilaiSensor;
}
```

## Usage

1. Connect the hardware as described in the Circuit Diagram section.
2. Open the Arduino IDE and paste the provided code.
3. Select the appropriate board and port in the Arduino IDE.
4. Upload the code to your Arduino board.
5. Open the Serial Monitor to view the humidity, temperature, and soil moisture readings.

The system will automatically adjust the state of the relays based on the temperature and soil moisture levels. The LCD will display the soil moisture and temperature readings.

## Troubleshooting

- LCD Not Displaying Properly: Ensure that the I2C address (0x27 or 0x3f) matches your LCD module.
- Relay Not Responding: Verify that the relay connections are correct and that the relays are functional.

For further assistance, consult the Arduino Documentation or the respective libraries' documentation.
