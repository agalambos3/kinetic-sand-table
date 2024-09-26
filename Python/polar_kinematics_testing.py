import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import math


#load data from thr file
data = np.loadtxt("dithermaster_thr/dither_tri4.thr")
#reshape data and seperate into theta and r array
tdata = np.transpose(data)
theta = tdata[0]
r = tdata[1]




def get_delta_t(r_i:float,r_f:float,th_i:float,th_f:float,v_a:float):
    del_th = th_f-th_i
    c = math.sqrt((r_f**2)+(r_i**2)-(2*r_i*r_f*math.cos(del_th)))
    t = c/v_a
    return t


# desired arc speed (units unclear)
v_a = 1

# time step for plotting position of table
t_step = .005

#np array for r positions of table
r_table =np.empty(1)
# np array for th positions of table
th_table = np.empty(1)


for index in range(len(theta)-1): 
    #get r_i,r_f,th_i,th_f from (two lines) in .thr file
    th_i = theta[index]
    th_f = theta[index+1]
    r_i = r[index]
    r_f = r[index+1]
    # print(th_i," ",th_f," ",r_i," ",r_f,"\n")

    #find time command should happen given desired "arc speed" v_a
    del_t = get_delta_t(r_i,r_f,th_i,th_f,v_a)

    # print(del_t,"\n")
    # print(th_i," ",th_f," ",r_i," ",r_f," ",del_t,"\n")

    #compute v_r (radial velocity) and v_th (angular velocity)
    if(del_t>0):
        v_r = (r_f-r_i)/del_t
        v_th = (th_f-th_i)/del_t
    else:
        v_r = 0
        v_th = 0

    # print(v_r," ",v_th,"\n")

    # time steps for command
    t_command = np.arange(0,del_t,t_step)
    #list of r positions during command

    r_command = (v_r*t_command)+r_i
    #list of theta positions during command
    th_command = (v_th*t_command)+th_i
    
    r_table = np.append(r_table,r_command)
    th_table = np.append(th_table,th_command)

    # input()


#compute position at each time step 

#append to list of positions for plotting 

#repeat above steps for all in .thr

#plot with animation the list of positions at given time step to see if it looks like what I expect



#create figure with two polar plots side by side

color = np.linspace(0,1,len(r_table))


# fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
# ax.scatter(th_table, r_table,s=.5,c=color,cmap="plasma")
# ax.set_rmax(1)
# ax.set_yticks(np.array([]))
# ax.set_xticks([])


fig, ax1  = plt.subplots(subplot_kw={"projection":"polar"})

#polar scatter plot\
ax1.scatter(theta,r,s=.1,c="gray")
splot = ax1.scatter(th_table, r_table,s=.05,c=color,cmap="plasma")
ax1.set_yticks(np.array([]))
ax1.set_xticks([])
ax1.set_rmax(1)



# fig1, ax2  = plt.subplots(subplot_kw={"projection":"polar"})

# # polar line plot
# pplot = ax2.plot(theta,r,linewidth=.5)[0]
# ax2.set_yticks(np.array([]))
# ax2.set_xticks([])
# ax2.margins(x=0,y=0)


# updating plot for animation


def update(frame):
    initial_frame = 0
    speed_multiplier = 2
    x = th_table[:speed_multiplier*(frame+initial_frame)]
    y = r_table[:speed_multiplier*(frame+initial_frame)]
    data = np.stack([x,y]).T
    splot.set_offsets(data)

    # # for each frame, update the data stored on each artist.
    # x = theta[:frame]
    # y = r[:frame]
    # # update the scatter plot:
    # data = np.stack([x, y]).T
    # splot.set_offsets(data)
    # #update line plot
    # pplot.set_xdata(theta[:frame])
    # pplot.set_ydata(r[:frame])
    return (splot)
    
is_animated = False
if is_animated == True:
    framelength = 10.0 # length of each frame in animation in milliseconds
    ani = animation.FuncAnimation(fig=fig, func=update, frames=len(r_table), interval=framelength)

# plt.savefig(fname="sand_drawing",dpi=400)
print(".thr file is {} lines long".format(len(r)))
print("number of computed step is {}".format(len(r_table)))
plt.show()