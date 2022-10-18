import os
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
from sklearn.metrics import r2_score
from sklearn.metrics import mean_absolute_percentage_error

if(not os.path.exists("Matchs")):
    os.system("mkdir Matchs")
else:
    os.system("rm -f Matchs/*")

real_water = []
real_oil = []
real_gas = []
real_waterMean = []
real_oilMean = []
real_gasMean = []

for i in range (25):
    inputFile_RealWater = open("../Input/agua/agua_"+str(i+1)+".txt", "r")
    inputFile_RealOil = open("../Input/oleo/oleo_"+str(i+1)+".txt", "r")
    inputFile_RealGas = open("../Input/gas/gas_"+str(i+1)+".txt", "r")    


    for line in inputFile_RealWater:
        real_waterMean.append(float(line))

    real_water.append(np.mean(real_waterMean))

    inputFile_RealWater.close()

    for line in inputFile_RealOil:
        real_oilMean.append(float(line))

    real_oil.append(np.mean(real_oilMean))

    inputFile_RealOil.close()

    for line in inputFile_RealGas:
        real_gasMean.append(float(line))

    real_gas.append(np.mean(real_gasMean))

    inputFile_RealGas.close()

for i in range(10):

    water = []
    oil = []
    gas = []
    waterMean = []
    oilMean = []
    gasMean = []
    water2 = []
    oil2 = []
    gas2 = []
    real_water2 = []
    real_oil2 = []
    real_gas2 = []

    for j in range (25):
        inputFile_Water = open("Output_Simulation/agua/"+str(i)+"-agua_"+str(j+1)+".txt", "r")
        inputFile_Oil = open("Output_Simulation/oleo/"+str(i)+"-oleo_"+str(j+1)+".txt", "r")
        inputFile_Gas = open("Output_Simulation/gas/"+str(i)+"-gas_"+str(j+1)+".txt", "r")

        for line in inputFile_Water:
            waterMean.append(float(line))

        water.append(np.mean(waterMean))
            
        inputFile_Water.close()

        for line in inputFile_Oil:
            oilMean.append(float(line))

        oil.append(np.mean(oilMean))

        inputFile_Oil.close()

        for line in inputFile_Gas:
            gasMean.append(float(line))

        gas.append(np.mean(gasMean))

        inputFile_Gas.close()
    
    for j in range(25):
        if water[j] < 1e-3:
            water[j] = 0.0
        water2.append(water[j])
        if oil[j] < 1e-3:
           oil[j] = 0.0
        oil2.append(oil[j])
        if oil[j] < 1e-3:
            oil[j] = 0.0
        gas2.append(gas[j])
        real_water2.append(real_water[j])
        real_oil2.append(real_oil[j])
        real_gas2.append(real_gas[j])

    print(str(i)+" - MAPE Error Water: ", mean_absolute_percentage_error(real_water2, water2))
    print(str(i)+" - R² Error Water: ", r2_score(real_water2, water2))
    print(str(i)+" - MAPE Error Oil: ", mean_absolute_percentage_error(real_oil2, oil2))
    print(str(i)+" - R² Error Oil: ", r2_score(real_oil2, oil2))
    print(str(i)+" - MAPE Error Gas: ", mean_absolute_percentage_error(real_gas2, gas2))
    print(str(i)+" - R² Error Gas: ", r2_score(real_gas2, gas2))
    print("")

    output = open("Matchs/resultado_"+str(i)+".txt", "w")

    output.write("MAPE Error Water: "+str(mean_absolute_percentage_error(real_water2, water2))+"\n")
    output.write("R² Error Water: "+str(r2_score(real_water2, water2))+"\n")
    output.write("MAPE Error Oil: "+str(mean_absolute_percentage_error(real_oil2, oil2))+"\n")
    output.write("R² Error Oil: "+str(r2_score(real_oil2, oil2))+"\n")
    output.write("MAPE Error Gas: "+str(mean_absolute_percentage_error(real_gas2, gas2))+"\n")
    output.write("R² Error Gas: "+str(r2_score(real_gas2, gas2))+"\n")


    output.close()

    values = [[real_water2, water2],[real_oil2, oil2],[real_gas2, gas2]]

    if(max(real_water2) > max(water2)):
        maxWater = max(real_water2)
    else:
        maxWater = max(water2)

    if(max(real_oil2) > max(oil2)):
        maxOil = max(real_oil2)
    else:
        maxOil = max(oil2)

    if(max(real_gas2) > max(gas2)):
        maxGas = max(real_gas2)
    else:
        maxGas = max(gas2)
    
    count = 0
    for value in values:
        instances = []
        for j in range(len(real_water2)):
            instances.append((j+1)*40)
            j = j + 250

        if(count == 0):
            #plt.title("Water Flow")
            plt.subplots_adjust(left=0.13, right=0.78, bottom=0.1, top=0.95)
            plt.ylabel("Water Flow")
            plt.xlabel("Time (in days)")
            plt.ylim([0, int(maxWater)+5])
            #plt.yscale('log')
            plt.plot(instances, values[0][0], color='red', label ='Real')
            plt.plot(instances, values[0][1], color='purple', label ='Predicted', linestyle = '--')
            plt.legend(loc = 'upper left', bbox_to_anchor=(1, 1))
            plt.savefig("Matchs/Matching Water_"+str(i)+" - Linhas.png")
        elif(count == 1):
            #plt.title("Oil Flow")
            plt.subplots_adjust(left=0.13, right=0.78, bottom=0.1, top=0.95)
            plt.ylabel("Oil Flow")
            plt.xlabel("Time (in days)")
            plt.ylim([0, int(maxOil)+100])
            #plt.yscale('log')
            plt.plot(instances, values[1][0], color='red', label ='Real')
            plt.plot(instances, values[1][1], color='purple', label ='Predicted', linestyle = '--')
            plt.legend(loc = 'upper left', bbox_to_anchor=(1, 1))
            plt.savefig("Matchs/Matching Oil_"+str(i)+" - Linhas.png")
        else:
            #plt.title("Oil Flow")
            plt.subplots_adjust(left=0.13, right=0.78, bottom=0.1, top=0.95)
            plt.ylabel("Gas Flow")
            plt.xlabel("Time (in days)")
            plt.ylim([0, int(maxGas)+100])
            #plt.yscale('log')
            plt.plot(instances, values[2][0], color='red', label ='Real')
            plt.plot(instances, values[2][1], color='purple', label ='Predicted', linestyle = '--')
            plt.legend(loc = 'upper left', bbox_to_anchor=(1, 1))
            plt.savefig("Matchs/Matching Gas_"+str(i)+" - Linhas.png")
        
        plt.clf()

        count = count + 1
