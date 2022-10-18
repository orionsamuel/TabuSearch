import os

def init(n):
    simulation(n)

def simulation(n):
    if(not os.path.exists("Output_Simulation")):
        os.system("mkdir Output_Simulation")
        os.system("mkdir Output_Simulation/agua")
        os.system("mkdir Output_Simulation/oleo")
        os.system("mkdir Output_Simulation/gas")
    else:
        os.system("rm -r -f Output_Simulation/*")
        os.system("mkdir Output_Simulation/agua")
        os.system("mkdir Output_Simulation/oleo")
        os.system("mkdir Output_Simulation/gas")


    os.system("rm -f output_simulation")
    os.system("cp ../summaryplot.py Output_Simulation/")
    for i in range(n):
        print("Executando a simulação: "+str(i))
        os.system("cp ../Output/3/"+str(i)+"-SPE9.DATA "
                  +"Output_Simulation/")
        os.system("cp ../Output/3/"+str(i)+"-PERMVALUES.DATA "
                  +"Output_Simulation/")
        os.system("cp ../Output/0/TOPSVALUES.DATA "
                  +"Output_Simulation/")
        os.system("mpirun -np 4 flow Output_Simulation/"+str(i)+
                  "-SPE9.DATA")
        os.system("python3 Output_Simulation/summaryplot.py WWPR:PRODU2 WWPR:PRODU3 WWPR:PRODU4 WWPR:PRODU5 WWPR:PRODU6 WWPR:PRODU7 " 
            +"WWPR:PRODU8 WWPR:PRODU9 WWPR:PRODU10 WWPR:PRODU11 WWPR:PRODU12 WWPR:PRODU12 WWPR:PRODU13 WWPR:PRODU14 WWPR:PRODU15 WWPR:PRODU16 WWPR:PRODU17 WWPR:PRODU18 "
            +"WWPR:PRODU19 WWPR:PRODU20 WWPR:PRODU21 WWPR:PRODU22 WWPR:PRODU23 WWPR:PRODU24 WWPR:PRODU25 WWPR:PRODU26 "
                  +"Output_Simulation/"+str(i)+"-SPE9.DATA")
        os.system("python3 Output_Simulation/summaryplot.py WOPR:PRODU2 WOPR:PRODU3 WOPR:PRODU4 WOPR:PRODU5 WOPR:PRODU6 WOPR:PRODU7 " 
            +"WOPR:PRODU8 WOPR:PRODU9 WOPR:PRODU10 WOPR:PRODU11 WOPR:PRODU12 WOPR:PRODU12 WOPR:PRODU13 WOPR:PRODU14 WOPR:PRODU15 WOPR:PRODU16 WOPR:PRODU17 WOPR:PRODU18 "
            +"WOPR:PRODU19 WOPR:PRODU20 WOPR:PRODU21 WOPR:PRODU22 WOPR:PRODU23 WOPR:PRODU24 WOPR:PRODU25 WOPR:PRODU26 "
                  +"Output_Simulation/"+str(i)+"-SPE9.DATA")
        os.system("python3 Output_Simulation/summaryplot.py WGPR:PRODU2 WGPR:PRODU3 WGPR:PRODU4 WGPR:PRODU5 WGPR:PRODU6 WGPR:PRODU7 " 
            +"WGPR:PRODU8 WGPR:PRODU9 WGPR:PRODU10 WGPR:PRODU11 WGPR:PRODU12 WGPR:PRODU12 WGPR:PRODU13 WGPR:PRODU14 WGPR:PRODU15 WGPR:PRODU16 WGPR:PRODU17 WGPR:PRODU18 "
            +"WGPR:PRODU19 WGPR:PRODU20 WGPR:PRODU21 WGPR:PRODU22 WGPR:PRODU23 WGPR:PRODU24 WGPR:PRODU25 WGPR:PRODU26 "
                  +"Output_Simulation/"+str(i)+"-SPE9.DATA")
        for j in range (25):
            os.system("mv WWPR:PRODU"+str(j+2)+".txt Output_Simulation/agua/"+str(i)+"-agua_"+str(j+1)+".txt")
        for j in range (25):
            os.system("mv WOPR:PRODU"+str(j+2)+".txt Output_Simulation/oleo/"+str(i)+"-oleo_"+str(j+1)+".txt")
        for j in range (25):
            os.system("mv WGPR:PRODU"+str(j+2)+".txt Output_Simulation/gas/"+str(i)+"-gas_"+str(j+1)+".txt")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.DBG")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.EGRID")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.INFOSTEP")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.INIT")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.PRT")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.SMSPEC")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.UNRST")
        os.system("rm Output_Simulation/"+str(i)+"-SPE9.UNSMRY")

    os.system("rm Output_Simulation/summaryplot.py ")


if __name__ == '__main__':
    init(3)




