# Main file to run when raspberry pi turns on 


import serial

# setup function to run and setup serial connection

def setup():
    """setup function that runs when script is first called"""
    # serial port 
    ser = serial.Serial('/dev/cu.usbmodem101',baudrate=115200,timeout=.1)
    
    return 0


def loop():
    '''loop that runs forever managing table'''
    while True:
        # do stuff forever
        return None
    

setup()
loop()



