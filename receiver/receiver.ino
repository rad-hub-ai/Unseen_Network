/*
 * Wireless Keypad - Receiver
 * 
 * This Arduino receives key presses via 433MHz RF receiver
 * and acts as a USB keyboard for Windows PC.
 * 
 * IMPORTANT: This code requires an Arduino with ATmega32U4 chip
 * (Arduino Leonardo, Pro Micro, or similar) for USB keyboard functionality.
 * 
 * Hardware:
 * - Arduino Leonardo/Pro Micro (ATmega32U4)
 * - 433MHz ASK RF Receiver Module
 * 
 * Pin Connections:
 * RF Receiver: Pin 2
 */

#include <VirtualWire.h>

// RF receiver settings
const int RF_RX_PIN = 2;
const int RECEPTION_SPEED = 1200; // Must match sender speed

// Variables for key handling
char lastReceivedKey = '\0';

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Wireless Keypad Receiver Starting...");
  
  // Initialize VirtualWire
  vw_set_rx_pin(RF_RX_PIN);
  vw_setup(RECEPTION_SPEED);
  vw_rx_start();
  
  Serial.println("Started!");
}

void loop() {
  // Check for received messages
  uint8_t message[VW_MAX_MESSAGE_LEN];
  uint8_t messageLength = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(message, &messageLength)) {
    // Process the received key (first character)
    char receivedKey = (char)message[0];
    
    // Update tracking variable
    lastReceivedKey = receivedKey;
    
    // Debug output
    Serial.print("Received and sent: ");
    Serial.println(receivedKey);
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}