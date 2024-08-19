// Include necessary libraries
#include "DHT.h"
#include <Wire.h>
#include <TM1650.h> // TM1650 display library

// Define pins
#define DHTPIN 4     // Digital pin connected to the DHT sensor

// Initialize the TM1650 display
TM1650 display(16, 17);  // Assuming CLK is 16 and DIO is 17

// Define sensor type
#define DHTTYPE DHT11   // DHT 11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Start the DHT sensor
  dht.begin();
  
  // Initialize the display
  display.setBrightness(BRIGHT_TYPICAL); // Set brightness (0-7), 3 bit
  display.displayOnOFF(1); // Turn on the display
}

void loop() {
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  float hum = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the temperature to the Serial Monitor (optional)
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Convert temperature to an integer representing the first decimal digit (e.g., 26.2 -> 262)
  int tempInt = (int)(temperature * 10);

  // Split the temperature into individual digits
  int digit1 = (tempInt / 100) % 10; // Tens place
  int digit2 = (tempInt / 10) % 10;  // Units place
  int digit3 = tempInt % 10;         // First decimal place

  // Display digits on TM1650
  if (digit1 > 0) { // Only display tens digit if it's non-zero
    display.displayBit(0, digit1); // Display tens digit
  } else {
    display.clearBit(0); // Clear tens digit if zero
  }
  display.displayBit(1, digit2); // Display units digit
  display.displayDot(1, true);   // Turn on decimal point after second digit
  display.displayBit(2, digit3); // Display first decimal digit
  display.clearBit(3);           // Clear the fourth digit
  
  // Wait a bit before the next loop
  delay(2000); // 2 seconds delay
}
