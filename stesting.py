import serial
import time
arduino = serial.Serial('/dev/cu.usbmodem101',baudrate=115200,timeout=.1)  # open serial port
print(arduino.name)         # check which port was really used


arduino.write(bytes("3200\n", 'utf-8')) 
	    

arduino.close()             # close port

