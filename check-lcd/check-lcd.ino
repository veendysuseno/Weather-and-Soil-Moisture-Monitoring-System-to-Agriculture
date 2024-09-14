#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize with the I2C address 0x27, 16 columns and 2 rows

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
