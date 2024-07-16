"""Class structure with communication class that will have methods for 
receiving and sending information to arduino as well as parsing sent information. Important methods:
checkSetup() - checks if arduino is set-up and ready to communicate
checkCoord() - checks if arduino is ready for coordinate
SendCoord() - sends coordinate pair to arduino to execute move
"""
import serial
import time

class arduino_communication:
    def __init__(self,port:str,baudrate:int,timeout:float) -> None:
        self.ser = serial.Serial(port,baudrate,timeout=timeout)
        self.send_bool = False
    def setup(self):
        while self.ser.in_waiting < 1:
            pass
        setup_byte = self.ser.read(1)
        setup_string = setup_byte.decode()
        if setup_string == "s":
            print("Succesful set-up, Arduino is ready to recieve commands")
        else:
            print("Set-up failed.")
    
    
    def check_ready(self)->bool:
        if self.ser.in_waiting > 0:
            ready_byte = self.ser.read(1)
            ready_string = ready_byte.decode()
            if ready_string == "r":
                return True
            else:
                return False
        pass
    def send_command(self,command:str):
        if self.send_bool == True:
            self.ser.write(b"command")
            pass


arduino = arduino_communication('/dev/cu.usbmodem101',115200,.1)
arduino.setup()

while True:
    if (arduino.check_ready() == True):
        print("sent command")
        arduino.send_command("S 500 500")