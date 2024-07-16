# Main file to run when raspberry pi turns on 


import serial
import os 
import random

#directory for thr file

thrDirectory = "/Users/andras/Documents/Kinetic Sand Table/Sand Table Code/dithermaster_thr"
isSketchActive = False
# directory of active sketch
activeSketchDir = None
#file for active sketch
activeSketch = None






# setup function to run and setup serial connection

def setup():
    """setup function that runs when script is first called"""
    # serial port 
    ser = serial.Serial('/dev/cu.usbmodem101',baudrate=115200,timeout=.1)

    while(ser.is_open==False):
        # wait until serial port is open
        pass

    # read until arduino ready signal is sent
    ser.read_until(b'R')


def loop():
    '''loop that runs forever managing table'''
    while True:
        if(isSketchActive == True):
            #
            pass


        # if sketch is running
    
        # do stuff forever
        
        else:
            random.choice(os.listdir(thrDirectory))
            pass


    
activeSketchName = random.choice(os.listdir(thrDirectory))
activeSketch=open(thrDirectory+"/"+activeSketchName)
print(activeSketch.name)
for line in activeSketch:
    input()
    # print(line)
    thr,r= line.split(" ")
    thr = thr.strip()
    r = r.strip()
    command = "<P "+thr+" "+r+" >"
    print(command)

# setup()
# loop()


'''What needs to happen in main loop:
- check serial port for command request
- if command requested
    - if command qd (and matches requested command) send commmand 
    - else q command and send 
- else
    - q command 

Program also has to have:
- way to randomly select thr file
- home/do spiral before each file to end up at right start position 
- parse thr one line at a time to q commands



'''