/*
 * Wireless Keypad - Sender
 * 
 * This Arduino reads from a 4x4 matrix keypad and transmits
 * key presses via 433MHz RF transmitter to the receiver Arduino.
 * 
 * Hardware:
 * - Arduino UNO
 * - 4x4 Matrix Keypad
 * - 433MHz ASK RF Transmitter Module
 * 
 * Pin Connections:
 * Keypad: Rows 2,3,4,5 | Columns 6,7,8,9
 * RF Transmitter: Pin 10
 */

#include <Keypad.h>
#include <VirtualWire.h>

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 3;

// Define the keypad layout
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// Define row and column pins
byte rowPins[ROWS] = {5, 4, 3, 2}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; // Connect to the column pinouts of the keypad

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// RF transmission settings
const int RF_TX_PIN = 10;
const int TRANSMISSION_SPEED = 1200; // bits per second

// Variables for key handling
char lastKey = '\0';
unsigned long lastKeyTime = 0;
const unsigned long KEY_REPEAT_DELAY = 500; // milliseconds

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Wireless Keypad Sender Starting...");
  
  // Initialize VirtualWire
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(TRANSMISSION_SPEED);
  
  Serial.println("Started!");
}

void loop() {
  // Read keypad
  char key = customKeypad.getKey();
  
  // If a key is pressed
  if (key) {
    // Check if it's a new key or repeat
    if (key != lastKey || (millis() - lastKeyTime) > KEY_REPEAT_DELAY) {
      // Transmit the single character
      vw_send((uint8_t*)&key, 1);
      vw_wait_tx(); // Wait for transmission to complete
      
      // Update tracking variables
      lastKey = key;
      lastKeyTime = millis();
      
      // Debug output
      Serial.print("Transmitted: ");
      Serial.println(key);
    }
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
} 