import serial
import time
arduino = serial.Serial('/dev/cu.usbmodem101',baudrate=115200,timeout=.1)  # open serial port

print(arduino.name)         # check which port was really used

time.sleep(2)#TODO: figure out why it takes so long for serial port to actualy start working 
# arduino.write(bytes("<y>", 'utf-8')) 
# time.sleep(1)
# arduino.write(bytes("<n>", 'utf-8'))

while True:
    userinput = input()
    arduino.write(bytes(f"<{userinput}>",'utf-8'))
    # arduino.write(bytes("<y>", 'utf-8')) 
    # time.sleep(1)
    # arduino.write(bytes("<n>", 'utf-8'))
    # # if (arduino.in_waiting > 0):
    # #     print(arduino.read(200))
    # time.sleep(1)




arduino.close()             # close port

