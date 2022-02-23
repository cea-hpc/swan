import matplotlib.pyplot as plt
import matplotlib.cbook as cbook

import numpy as np

def initPlot():
    # Initialize the figure and axes.
    fig, axs = plt.subplots(2)
    for ax in axs.flat:
        ax.set(xlabel='x(m)', ylabel='Surface elevation (m)')
        ax.label_outer()
    return axs
  
def plot(axs, amp, id, xArray):   
    with cbook.get_sample_data('/home/oudotmp/workspaces/swan/swan/src/swan/dumpHAmp' + amp + '.csv') as file:
        hArray = np.loadtxt(file, delimiter=',')
    
    num_rows, num_cols = hArray.shape
    finalTime=hArray[num_rows-1][0]
     
    # Set the title for the figure
    axs[id].set_title('Propagation of a Gaussian wave (Amp=' + str(float(amp)/10) + ') at t='+str(finalTime)+'s', fontsize=15)
    axs[id].plot(xArray, hArray[0][1:], color='blue', label='H(x) à t=0s')
    axs[id].plot(xArray, hArray[num_rows-1][1:], color='green', label='H(x) à t='+str(finalTime)+'s')
    # Add a legend, and position it on the upper right (with box)
    axs[id].legend(loc='upper right', frameon=True)

axs = initPlot()
with cbook.get_sample_data('/home/oudotmp/workspaces/swan/swan/src/swan/dumpX.csv') as file:
    xArray = np.loadtxt(file, delimiter=',')
plot(axs, '01', 0, xArray)
plot(axs, '20', 1, xArray)
plt.show()
