#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <random>
#include <iomanip>
#include <vector>
#include <fstream>
#include <cmath>
#include "utils.hpp"

using namespace std;

class functions{
    public:

    void Simulation(int idIteration, int iterator, int size, string file, bool sup);
    double Rand_double(double min, double max);
    double Max(double num1, double num2);
    double Min(double num1, double num2);
    double Normalize(double value, double min, double max);
    const vector<string> split(const string& s, const char& c);
    void CreateOutputDir();
    string ReadFileInput(string file);
    vector<result> ConvertStringInputToDoubleResult(string water, string oil, string gas);
    const char* Command(string inputCommand);
    void CreateResultDir(int idIteration);
    void CreateSupDir(int idIteration, int iterator);
    void WriteSimulationFile(int idIteration, int interator, bool sup, string inputFile, string file, string permeabilityFile, individual sCandidate);
    void WriteErrorFile(int idIteration, int iterator, bool sup, individual sCandidate);
    double activationFunction(string waterResult, string oilResult, string gasResult, vector<result> results, int idIteration);

};