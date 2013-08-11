# See https://github.com/sudar/Arduino-Makefile for info on using this makefile

BOARD_TAG    = uno
MONITOR_PORT = /dev/ttyACM1
USER_LIB_PATH = ./libraries
ARDUINO_LIBS = Wire Adafruit_LEDBackpack Adafruit_GFX

include ../Arduino-Makefile/arduino-mk/Arduino.mk

