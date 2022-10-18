#include <string>
#include <chrono>

using namespace std;

const string inputOil = "../Input/oleo/oleo";
const string inputWater = "../Input/agua/agua";
const string inputGas = "../Input/gas/gas";
const string simulationFile = "../Input/SPE9.DATA";
const string fileName = "SPE9";
const string permeabilityFile = "PERMVALUES.DATA";

#define N_ITERATIONS 10
#define STOP 0.009

#define MIN_LAMBDA 0.1
#define MAX_LAMBDA 1

#define MIN_POROSITY 0.01
#define MAX_POROSITY 0.2

#define MIN_PERMEABILITY_1 10.0
#define MAX_PERMEABILITY_1 50.0

#define MIN_PERMEABILITY_2 50.0
#define MAX_PERMEABILITY_2 500.0

#define MIN_PERMEABILITY_3 500.0
#define MAX_PERMEABILITY_3 2000.0

#define MIN_PERMEABILITY_4 2000.0
#define MAX_PERMEABILITY_4 4000.0

#define MIN_PERMEABILITY_5 4000.0
#define MAX_PERMEABILITY_5 8000.0

#define a 0.99

#define WATER_WEIGHT 0.5
#define OIL_WEIGHT 0.2
#define GAS_WEIGHT 0.3

#define TOTAL_CELLS 4200

#define N_POROSITY 15

#define N_METRICS 3

#define N_BLOCKS 4

#define HEIGHT 42
#define WIDTH 100

#define SIZE 60
#define TABU_SIZE 60
#define SUPERIOZATION_SIZE 8

struct individual{
    double porosity[N_POROSITY];
    double permeability[TOTAL_CELLS];
    double error_rank;
    double proximity;
};

struct result{
    double water;
    double oil;
    double gas;
};


