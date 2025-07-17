// Include the Liquid Crystal Library
#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library with the numbers of the interface pins
// LiquidCrystal(rs, en, d4, d5, d6, d7)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define the analog pin for the temperature sensor
const int tempSensorPin = A0;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp Sensor");
  lcd.setCursor(0, 1); // Move cursor to the second line
  lcd.print("Init...");

  // Start serial communication for debugging (optional, but good practice)
  Serial.begin(9600);
  Serial.println("Temperature Sensor with LCD - Initialized");
}

void loop() {
  // Read the analog value from the temperature sensor
  int sensorValue = analogRead(tempSensorPin);

  // Convert the analog value to voltage
  // For LM35: 10 mV per degree Celsius. Arduino's 5V is 1024 analog units.
  // So, 1 unit = 5000mV / 1024 = ~4.88mV
  // Voltage = sensorValue * (5.0 / 1024.0)
  float voltage = sensorValue * (5.0 / 1024.0);

  // Convert the voltage to temperature in Celsius
  // For LM35: Temp in Celsius = Voltage * 100
  // For TMP36: Temp in Celsius = (Voltage - 0.5) * 100
  // Let's assume LM35 for this example, adjust if using TMP36
  float temperatureC = voltage * 100.0;

  // Convert Celsius to Fahrenheit
  float temperatureF = (temperatureC * 9/5) + 32;

  // Clear the LCD to update the display
  lcd.clear();

  // Display temperature on the first line
  lcd.setCursor(0, 0); // Column 0, Row 0
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Display temperature on the second line
  lcd.setCursor(0, 1); // Column 0, Row 1
  lcd.print("      "); // Spaces to clear any leftover characters if temperature changes
  lcd.print(temperatureF);
  lcd.print((char)223); // Degree symbol
  lcd.print("F");

  // Print to Serial Monitor for debugging
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.print(voltage);
  Serial.print("V\tTemperature: ");
  Serial.print(temperatureC);
  Serial.print((char)223);
  Serial.println("C");

  delay(2000); // Wait for 2 seconds before taking another reading
}