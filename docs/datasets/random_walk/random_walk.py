from random import seed
from random import random
from matplotlib import pyplot

f = open('random_walk_1m.csv', 'w')
seed(1)
random_walk = list()
random_walk.append(-1 if random() < 0.5 else 1)
for i in range(1, 1000000):
    movement = -1 if random() < 0.5 else 1
    value = random_walk[i - 1] + movement
    random_walk.append(value)
    f.write( f"{value}\n")
pyplot.plot(random_walk)
pyplot.show()
