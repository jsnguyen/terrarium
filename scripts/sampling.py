#!/Users/jsnguyen/anaconda/bin/python

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Ellipse
import matplotlib as mpl


PI=3.1459
eccentricity=0.5
semimajor_axis=1
x=[]
y=[]
for i in np.arange(0,2*PI,0.1):
    angle=i
    pos_mag=semimajor_axis*(1-(eccentricity*eccentricity)) / (1+(eccentricity*np.cos(angle)))
    semiminor_axis = np.sqrt(1-eccentricity*eccentricity)*semimajor_axis

    foci_dist = np.sqrt(semimajor_axis*semimajor_axis - semiminor_axis*semiminor_axis)

    x.append(pos_mag*np.cos(angle))
    y.append(pos_mag*np.sin(angle))

a=[0 for _ in x]
plt.quiver(0,0,x,y,width=0.01, units = 'xy', scale = 1)
plt.xlim(min(x)*1.1,max(x)*1.1)
plt.ylim(min(y)*1.1,max(y)*1.1)
#plt.plot(x,y)
plt.grid()
plt.show()
