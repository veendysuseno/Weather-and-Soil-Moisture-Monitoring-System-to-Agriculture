# ESP8266 Weather and Soil Moisture Monitoring

## Overview

This project uses an ESP8266 microcontroller to collect temperature, humidity, and soil moisture data. The data is sent to ThingSpeak, an IoT analytics platform, for remote monitoring. The setup involves a DHT11 sensor for temperature and humidity and an analog soil moisture sensor.

## Components

- **ESP8266**: Microcontroller for WiFi and data handling
- **DHT11**: Sensor for temperature and humidity
- **Analog Soil Moisture Sensor**: Measures soil moisture
- **ThingSpeak**: IoT platform for data visualization

## Requirements

- Arduino IDE or compatible development environment
- ESP8266 board package installed
- DHT sensor library (`DHT.h`)
- ESP8266 WiFi library (`ESP8266WiFi.h`)

## Wiring

- **DHT11 Sensor**:

  - Data Pin to `D5`
  - VCC to `3.3V`
  - GND to `GND`

- **Soil Moisture Sensor**:

  - Analog Output to `A0`
  - VCC to `3.3V` or `5V` (depending on sensor specification)
  - GND to `GND`

- **Power Control for Soil Moisture Sensor**:
  - Control Pin to `D6`

## Code Description

- **Setup**:

  - Initializes serial communication, sets up the DHT11 sensor, and connects to WiFi.
  - Prints connection status to the Serial Monitor.

- **Loop**:

  - Reads humidity and temperature from the DHT11 sensor.
  - Reads soil moisture from the analog sensor.
  - Sends the collected data to ThingSpeak every 20 seconds.
  - Prints sensor readings and status messages to the Serial Monitor.

- **`readSensor()`**:
  - Turns on the power to the soil moisture sensor.
  - Reads the analog value and turns off the power.
  - Returns the inverted sensor value (higher value indicates more moisture).

## Configuration

- **ThingSpeak Setup**:

  - Create an account on [ThingSpeak](https://thingspeak.com/).
  - Create a new channel with at least three fields.
  - Copy the `Write API Key` and use it to replace the `apiKey` variable in the code.

- **WiFi Setup**:
  - Replace `ssid` and `password` with your WiFi network credentials.

## Uploading Code

1. Open the Arduino IDE.
2. Connect the ESP8266 to your computer.
3. Select the correct board and port from the Tools menu.
4. Paste the code into the IDE and upload it to the ESP8266.

## Troubleshooting

- **Failed to connect to ThingSpeak**:

  - Ensure that your API key is correct.
  - Check WiFi credentials and connection.
  - Verify the ThingSpeak server status.

- **Failed to read from DHT sensor**:
  - Check the wiring and connections to the DHT11 sensor.
  - Make sure the sensor is properly initialized.
