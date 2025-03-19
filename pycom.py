#install pyserial                                                                                                
import serial

import time

serial1 = serial.Serial('/dev/ttyUSB0', 9600)

while True:
    x = input("1=on 0=off: ")
    if x == "0":
        serial1.write(b'0')
    elif x == "1":
        serial1.write(b'1')
