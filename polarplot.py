import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Compute areas and colors

data = np.loadtxt("Sand Table Code/thr files/reverse-HEP.txt")
tdata = np.transpose(data)
theta = tdata[0]
r = tdata[1]
color = np.linspace(0,1,len(r))




fig, (ax1, ax2) = plt.subplots(1, 2,subplot_kw={"projection":"polar"})
splot = ax1.scatter(theta, r,s=2,c=color,cmap="plasma")
ax1.set_yticks(np.array([]))
ax1.set_xticks([])

pplot = ax2.plot(theta,r,linewidth=.5)[0]
ax2.set_yticks(np.array([]))
ax2.set_xticks([])


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
    


ani = animation.FuncAnimation(fig=fig, func=update, frames=len(r), interval=1)

plt.show()
