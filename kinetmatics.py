"""big picture steps for kinematics -
Do the following for thr file until end is reached:
1. calculate the change in rho and change in theta
2. if change in theta is large between two points interpret as erase track 
2a. clear track (TODO: figure out how to generate thr file for erase track)
3. if change in theta is small interpret as linear move
3a. calculate number of steps needed from central and outer motor for
theta move
3b. compute number of steps needed from central motor to for radial move
3c. based on 3a and 3b calculate the number of steps 
each motor needs to make for move
4. Return number of steps each motor needs to make
(these step counts will be sent to arduino over serial where they will be 
input into Multistepper.moveTo() so that both motor movements finish
simultaneously, TODO: think about what kind of move simultaneous finish means  
"""

"""because table will run many tracks repeatedly computationally,
 I could process tracks into numpy arrrays composed of the step count for motor 
 and save them to their own directory"""

#import necessary libraries
import numpy as np
import math

#configuration settings relevant to specific table set-up
#TODO move table settings into configuration file so it is accesible across files

#full steps per revolution for nema17
nema17_spr = 200
#microstep setting
microsteps = 32
#gear ratio of angular stepper to central gear
outer_gear_ratio = 8

#steps per revolution for radial stepper
radial_spr = nema17_spr*microsteps
#steps per revolution for angular stepper
angular_spr = nema17_spr*microsteps*outer_gear_ratio

#table radius in mm
table_radius = 400

#linear distance per step ie gear profile pitch 
dist_per_step = 2 

#number of steps from rho = 0 to rho =1
radial_spd = math.floor(table_radius/(dist_per_step/microsteps))

print(radial_spr,angular_spr,radial_spd)

def compute_all_steps(thr_file_path):
    """takes thr file as input as calculates steps for each motor for 
    for all the lines in the file. return a len(thr)x2 array of motor steps"""
    data = np.loadtxt(thr_file_path)
    tdata = np.transpose(data)
    theta = tdata[0]
    rho = tdata[1]

    #get difference list for each move
    theta_diff = np.diff(theta)
    rho_diff = np.diff(rho)

    #calculate steps for angular and radial stepper for angular move
    angular_steps = np.floor((theta_diff/360)*angular_spr)
    radial_steps = np.floor(((theta_diff/360)*radial_spr))
    #calculate  steps for radial stepper due to angular move
    radial_steps += rho_diff*radial_spd

    step_array = np.column_stack((angular_steps,radial_steps))
    step_array = np.rint(step_array)
    return step_array

   




    
        
    
    pass

print(compute_all_steps("Sand Table Code/thr files/reverse-HEP.txt")[1000:1100])
