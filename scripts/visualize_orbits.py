#!/Users/jsnguyen/anaconda/bin/python

import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Ellipse
import matplotlib as mpl

au_to_km=1.496e+8;

def make_orbits(name,a,e,angle):
    n=len(a)
    print (a)
    orbits = []
    for i in range(n):
        b = np.sqrt(1-e[i]**2)*a[i]
        foci_dist = np.sqrt(a[i]**2 - b**2)
        foci_x = foci_dist*np.cos(angle[i])
        foci_y = foci_dist*np.sin(angle[i])
        print (angle[i])
        c = 'C'+str(i%10)
        orbits.append(mpl.patches.Ellipse(xy=[foci_x,foci_y], width=a[i]*2, height=b*2,color=c, angle=np.rad2deg(angle[i]), fill=False,label=name[i]))
    return orbits

radius = 2.1*au_to_km
fig, ax = plt.subplots(1,2,figsize=(10, 5))

filename='./data/initial_orbit.txt'
name=[]
a=[]
e=[]
angle=[]
pos_x=[]
pos_y=[]
with open(filename) as f:
    for line in f:
        line = line.split()
        name.append(line[0])
        a.append(float(line[1]))
        e.append(float(line[2]))
        angle.append(float(line[5]))
        pos = line[3][1:-1].split(',')
        pos_x.append(float(pos[0]))
        pos_y.append(float(pos[1]))


orbits = make_orbits(name,a,e,angle)
for i,el in enumerate(orbits):
    ax[0].add_patch(el)
    ax[0].scatter(pos_x[i],pos_y[i])
ax[0].set_aspect('equal')
ax[0].scatter(0,0, label='Host Star', color='black',marker='*')
ax[0].set_title('Initial Orbits')
ax[0].set_xlabel('Distance (AU)')
ax[0].set_xlim(-radius,radius)
ax[0].set_ylim(-radius,radius)

filename='./data/final_orbit.txt'
name=[]
a=[]
e=[]
angle=[]
pos_x=[]
pos_y=[]
with open(filename) as f:
    for line in f:
        line = line.split()
        name.append(line[0])
        a.append(float(line[1]))
        e.append(float(line[2]))
        angle.append(float(line[5]))
        pos = line[3][1:-1].split(',')
        pos_x.append(float(pos[0]))
        pos_y.append(float(pos[1]))

orbits = make_orbits(name,a,e,angle)
for i,el in enumerate(orbits):
    ax[1].add_patch(el)
    ax[1].scatter(pos_x[i],pos_y[i])

ax[1].set_aspect('equal')
ax[1].scatter(0,0, label='Host Star', color='black',marker='*')
ax[1].set_title('Final Orbits')
ax[1].set_xlabel('Distance (AU)')
ax[1].set_xlim(-radius,radius)
ax[1].set_ylim(-radius,radius)

plt.show()
