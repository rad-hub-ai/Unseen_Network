import serial
import time
import pyautogui
ser = serial.Serial('COM10', 9600)
time.sleep(2)
print("Listening... (keypress will be typed globally)")
while True:
    if ser.in_waiting > 0:
        char = ser.read().decode('utf-8')
        pyautogui.write(char)
        print(f"Typed: {char}")
