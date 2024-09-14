# LCD I2C Test

This project demonstrates how to initialize and display text on a 16x2 LCD using the I2C interface. The code continuously displays two lines of text on the LCD to verify that the LCD is functioning correctly.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **16x2 LCD with I2C Interface**
- **Connecting Wires**
- **Breadboard** (optional)

## Circuit Diagram

1. **LCD (I2C):**
   - **VCC** to 5V (or 3.3V depending on your board)
   - **GND** to GND
   - **SDA** to A4 (SDA) on Arduino Uno (or corresponding SDA pin on other boards)
   - **SCL** to A5 (SCL) on Arduino Uno (or corresponding SCL pin on other boards)

## Software Requirements

- **Arduino IDE**
- **LiquidCrystal_I2C Library** (install via the Library Manager in the Arduino IDE)

## Code

```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize with I2C address 0x27, 16 columns, and 2 rows

void setup() {
  lcd.begin(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight (if your LCD has a backlight feature)
}

void loop() {
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("TEST LCD i2C"); // Print message on the first line
  lcd.setCursor(0, 1); // Set cursor to column 0, row 1
  lcd.print("CEK LCD NYALA"); // Print message on the second line

  delay(2000); // Wait for 2 seconds
}
```

Here’s a README.md file for your LCD testing code:

markdown

# LCD I2C Test

This project demonstrates how to initialize and display text on a 16x2 LCD using the I2C interface. The code continuously displays two lines of text on the LCD to verify that the LCD is functioning correctly.

## Hardware Requirements

- **Arduino Board** (e.g., Arduino Uno, Nano)
- **16x2 LCD with I2C Interface**
- **Connecting Wires**
- **Breadboard** (optional)

## Circuit Diagram

1. **LCD (I2C):**
   - **VCC** to 5V (or 3.3V depending on your board)
   - **GND** to GND
   - **SDA** to A4 (SDA) on Arduino Uno (or corresponding SDA pin on other boards)
   - **SCL** to A5 (SCL) on Arduino Uno (or corresponding SCL pin on other boards)

## Software Requirements

- **Arduino IDE**
- **LiquidCrystal_I2C Library** (install via the Library Manager in the Arduino IDE)

## Code

```cpp
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize with I2C address 0x27, 16 columns, and 2 rows

void setup() {
  lcd.begin(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight (if your LCD has a backlight feature)
}

void loop() {
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("TEST LCD i2C"); // Print message on the first line
  lcd.setCursor(0, 1); // Set cursor to column 0, row 1
  lcd.print("CEK LCD NYALA"); // Print message on the second line

  delay(2000); // Wait for 2 seconds
}
```

## Setup Instructions

1. Connect the Hardware:

   - Connect the VCC pin of the LCD to the 5V pin on the Arduino.
   - Connect the GND pin of the LCD to the GND pin on the Arduino.
   - Connect the SDA pin of the LCD to the SDA pin on the Arduino (A4 on the Arduino Uno).
   - Connect the SCL pin of the LCD to the SCL pin on the Arduino (A5 on the Arduino Uno).

2. Install the LiquidCrystal_I2C Library:

   - Open the Arduino IDE.
   - Go to Sketch -> Include Library -> Manage Libraries.
   - Search for "LiquidCrystal_I2C" and install the library by Frank de Brabander or similar.

3. Upload the Code:

   - Open the Arduino IDE and paste the provided code into a new sketch.
   - Select the appropriate board and port.
   - Click on the upload button to transfer the code to your Arduino board.

4. Observe the LCD:
   - Once the code is uploaded, the LCD should display "TEST LCD i2C" on the first line and "CEK LCD NYALA" on the second line.

## Troubleshooting

- LCD Not Displaying: Ensure the I2C address 0x27 matches your LCD module. If not, try 0x3F or use an I2C scanner sketch to find the correct address.
- No Backlight: Ensure the backlight feature is supported and properly connected if the text is not visible.
- Text Not Clear: Adjust the contrast if the text is faint or unclear.
