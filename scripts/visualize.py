#!/Users/jsnguyen/anaconda/bin/python

import matplotlib.pyplot as plt

filename='./data/path.txt'

au_to_km=1.496e+8

class protoplanetary_object:
    def __init__(self):
        self.id=0
        self.x=[]
        self.y=[]
        self.z=[]

with open(filename) as f:
    N_BODIES=next(f)
    bodies=[protoplanetary_object() for _ in range(int(N_BODIES))]
    for line in f:
        for i,el in enumerate(line.split()):
            bodies[i].id=int(el.split(':')[0])
            el=el.split(':')[1][1:-1].split(',')
            bodies[bodies[i].id].x.append(float(el[0]))
            bodies[bodies[i].id].y.append(float(el[1]))
            bodies[bodies[i].id].z.append(float(el[2]))

bodies=bodies[1:] #remove sun
plt.figure(figsize=(5,5))
bounds=2.1*au_to_km
plt.xlim(-bounds,bounds)
plt.ylim(-bounds,bounds)
for el in bodies:
    plt.plot(el.x,el.y,marker='',linestyle='--')
    plt.scatter(el.x[-1],el.y[-1])

plt.scatter(0,0, label='Host Star', color='black',marker='*')
#plt.plot(bodies[0].x,bodies[1].y,marker='',linestyle='--')
plt.savefig('vis_ex.png',bbox_inches='tight')
plt.show()
