import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np


#load data from thr file
data = np.loadtxt("Sand Table Code/Dithermaster sisyphus master thr_paths/dither_tri4.thr")
#reshape data and seperate into theta and r array
tdata = np.transpose(data)
theta = tdata[0]
r = tdata[1]
color = np.linspace(0,1,len(r))



#create figure with two polar plots side by side
fig, (ax1, ax2) = plt.subplots(1, 2,subplot_kw={"projection":"polar"})

#polar scatter plot
splot = ax1.scatter(theta, r,s=2,c=color,cmap="plasma")
ax1.set_yticks(np.array([]))
ax1.set_xticks([])
ax1.margins(x=0,y=0)

#polar line plot
pplot = ax2.plot(theta,r,linewidth=.5)[0]
ax2.set_yticks(np.array([]))
ax2.set_xticks([])
ax2.margins(x=0,y=0)


plt.margins(x=0,y=0)


#updating plot for animation
def update(frame):
    # for each frame, update the data stored on each artist.
    x = theta[:frame]
    y = r[:frame]
    # update the scatter plot:
    data = np.stack([x, y]).T
    splot.set_offsets(data)
    #update line plot
    pplot.set_xdata(theta[:frame])
    pplot.set_ydata(r[:frame])
    return (splot,pplot)
    
is_animated = False
if is_animated == True:
    ani = animation.FuncAnimation(fig=fig, func=update, frames=len(r), interval=1)

plt.show()
