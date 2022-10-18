import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

error = []

inputFile = open("../Output/3/error.txt")
for line in inputFile:
    error.append(float(line))

population = []
    
for j in range(3):
    population.append(j+1)

plt.figure(figsize=(10, 4), dpi=300)
plt.title("Genetic Progress")
plt.ylabel("Best-So-Far Misfit Value")
plt.xlabel("Iterations")
#plt.yscale('log')
#plt.xscale('log')

plt.plot(population, error, color='red', label ='Error')
plt.legend(loc = 'upper right')
plt.savefig("Genetic Progress.png")
