import time
import serial

from sys import argv

script, filename = argv

txt = open(filename)

ser = serial.Serial('/dev/ttyACM1', 9600)

time.sleep(2)

ser.write(txt.read())
