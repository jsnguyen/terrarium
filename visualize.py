import matplotlib.pyplot as plt

filename='path.txt'

with open(filename) as f:
    x=[]
    y=[]
    z=[]
    for line in f:
            line=line.strip()
            line = line[1:-1]
            temp = (line.split(','))
            if temp != ['']:
                x.append(temp[0])
                y.append(temp[1])
                z.append(temp[2])

print (x,y)
plt.figure(figsize=(5,5))
bounds=2e8
plt.xlim(-bounds,bounds)
plt.ylim(-bounds,bounds)
plt.plot(x,y,marker='',linestyle='--')
plt.show()
