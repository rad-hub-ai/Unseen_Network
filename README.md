# Wireless Keypad to PC Typing via 433MHz RF and Arduino

This project enables you to wirelessly send key presses from a 3x4 keypad connected to an Arduino using a 433MHz RF module. The received key presses are then typed automatically on your computer, simulating a real keyboard input that works in any application (e.g., Telegram, Notepad, browser).

---

## Components

- 2x Arduino UNO (or compatible)
- 3x4 Matrix Keypad
- 433MHz ASK RF Transmitter and Receiver modules
- Connecting wires
- USB cable for Arduino and PC connection

---

## How it works

1. The sender Arduino reads key presses from the keypad.
2. It transmits the pressed key wirelessly via the 433MHz RF transmitter.
3. The receiver Arduino gets the data through the RF receiver and sends it via serial (USB) to the PC.
4. A Python script on the PC listens to the serial port, receives the key presses, and uses software keyboard simulation (`pyautogui`) to type the keys in real time wherever the text cursor is active.

---

## Wiring

### Sender Arduino (Transmitter)
- Keypad rows to pins: 2, 3, 4, 5
- Keypad columns to pins: 6, 7, 8
- RF Transmitter data pin to Arduino pin 10
- Power (VCC) and GND to Arduino 5V and GND

### Receiver Arduino
- RF Receiver data pin to Arduino pin 11
- Power (VCC) and GND to Arduino 5V and GND

---

## Arduino Code

- Use the provided **Sender** code on the transmitting Arduino.
- Use matching **Receiver** code on the receiving Arduino (make sure it sends data via serial at 9600 baud).

---

## Python Script

- Requires `pyserial` and `pyautogui` libraries:

```bash
pip install pyserial pyautogui
