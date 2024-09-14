#include <LiquidCrystal_I2C.h>
#include <DHT.h>

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
