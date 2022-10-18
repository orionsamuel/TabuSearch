#include "../include/functions.hpp"

void functions::Simulation(int idIteration, int iterator, int size, string file, bool sup){
    string path;

    if(sup){
        path = "../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator);
    }else{
        path = "../Output/"+to_string(idIteration);
    }

    system(Command("cp ../summaryplot.py "+path+"/"));

    for(int i = 0; i < size; i++){
        if(sup){
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << iterator << " da superiorização " << endl;
        }else{
            cout << "Executando a simulação no indivíduo " << i << " da iteração " << idIteration << endl;
        }
        system(Command("flow "+path+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("python3 "+path+"/summaryplot.py WWPR:PRODU2 WWPR:PRODU3 WWPR:PRODU4 WWPR:PRODU5 WWPR:PRODU6 WWPR:PRODU7"+ 
            " WWPR:PRODU8 WWPR:PRODU9 WWPR:PRODU10 WWPR:PRODU11 WWPR:PRODU12 WWPR:PRODU12 WWPR:PRODU13 WWPR:PRODU14 WWPR:PRODU15 WWPR:PRODU16 WWPR:PRODU17 WWPR:PRODU18"+
            " WWPR:PRODU19 WWPR:PRODU20 WWPR:PRODU21 WWPR:PRODU22 WWPR:PRODU23 WWPR:PRODU24 WWPR:PRODU25 WWPR:PRODU26 "+path+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("python3 "+path+"/summaryplot.py WOPR:PRODU2 WOPR:PRODU3 WOPR:PRODU4 WOPR:PRODU5 WOPR:PRODU6 WOPR:PRODU7"+ 
            " WOPR:PRODU8 WOPR:PRODU9 WOPR:PRODU10 WOPR:PRODU11 WOPR:PRODU12 WOPR:PRODU12 WOPR:PRODU13 WOPR:PRODU14 WOPR:PRODU15 WOPR:PRODU16 WOPR:PRODU17 WOPR:PRODU18"+
            " WOPR:PRODU19 WOPR:PRODU20 WOPR:PRODU21 WOPR:PRODU22 WOPR:PRODU23 WOPR:PRODU24 WOPR:PRODU25 WOPR:PRODU26 "+path+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            system(Command("python3 "+path+"/summaryplot.py WGPR:PRODU2 WGPR:PRODU3 WGPR:PRODU4 WGPR:PRODU5 WGPR:PRODU6 WGPR:PRODU7"+ 
            " WGPR:PRODU8 WGPR:PRODU9 WGPR:PRODU10 WGPR:PRODU11 WGPR:PRODU12 WGPR:PRODU12 WGPR:PRODU13 WGPR:PRODU14 WGPR:PRODU15 WGPR:PRODU16 WGPR:PRODU17 WGPR:PRODU18"+
            " WGPR:PRODU19 WGPR:PRODU20 WGPR:PRODU21 WGPR:PRODU22 WGPR:PRODU23 WGPR:PRODU24 WGPR:PRODU25 WGPR:PRODU26 "+path+"/"+to_string(i)+"-"+file+".DATA >> out.txt"));
            for(int j = 2; j < 27; j++){
                system(Command("mv WWPR:PRODU"+to_string(j)+".txt "+path+"/agua/"+to_string(i)+"-agua_"+to_string(j-1)+".txt"));
            }
            for(int j = 2; j < 27; j++){
                system(Command("mv WOPR:PRODU"+to_string(j)+".txt "+path+"/oleo/"+to_string(i)+"-oleo_"+to_string(j-1)+".txt"));
            }
            for(int j = 2; j < 27; j++){
                system(Command("mv WGPR:PRODU"+to_string(j)+".txt "+path+"/gas/"+to_string(i)+"-gas_"+to_string(j-1)+".txt"));
            }
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".DBG"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".EGRID"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".INFOSTEP"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".PRT"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".SMSPEC"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".UNRST"));
            system(Command("rm "+path+"/"+to_string(i)+"-"+file+".UNSMRY"));
    }

    system(Command("rm  "+path+"/summaryplot.py"));
}

double functions::Rand_double(double min, double max){
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double>distr(min, max);

    double num = distr(eng);
    
    num = floor(num *100) / 100;

    return num;
}

double functions::Max(double num1, double num2){
    if(num1 > num2){
        return num1;
    }else{
        return num2;
    }
}

double functions::Min(double num1, double num2){
    if(num1 < num2){
        return num1;
    }else{
        return num2;
    }
}

double functions::Normalize(double value, double min, double max){
    return (value - min) / (max - min);
}

const vector<string> functions::split(const string& s, const char& c){
    string buff{""};
	vector<string> v;
	
	for(auto n:s){
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}

	if(buff != "") v.push_back(buff);
	
	return v;
}

void functions::CreateOutputDir(){
    DIR* dp = opendir("../Output/");

    if(dp == NULL){
        system("mkdir ../Output/");
    }else{
        system("rm -r -f ../Output/*");
    }
}

string functions::ReadFileInput(string file){
    string line, content;

    for(int i = 1; i < 26; i++){
        ifstream fileStream(file+"_"+to_string(i)+".txt", ios::in);
        while(!fileStream.eof()){
            getline(fileStream, line);
            content += line;
            content += " ";
        }
        fileStream.close();
    }

    return content;
}

vector<result> functions::ConvertStringInputToDoubleResult(string water, string oil, string gas){
    vector<string> waterSplit{split(water, ' ')};
    vector<string> oilSplit{split(oil, ' ')};
    vector<string> gasSplit{split(gas, ' ')};

    vector<result> results;
    
    for(int i = 0; i < waterSplit.size(); i++){
        result partialResult;
        partialResult.water = stod(waterSplit[i]);
        partialResult.oil = stod(oilSplit[i]);
        partialResult.gas = stod(gasSplit[i]);
        results.push_back(partialResult);
    }

    return results;

}

const char* functions::Command(string inputCommand){
    const char* command = (char*) inputCommand.c_str();
    return command;
}

void functions::CreateResultDir(int idIteration){
    string command = "../Output/"+to_string(idIteration);
    const char* file = (char*) command.c_str();
    DIR* dp = opendir(file);

    if(dp == NULL){;
        system(Command("mkdir ../Output/"+to_string(idIteration)));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/oleo"));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/agua"));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/gas"));
    }else{
        const char* rm = Command("rm -f ../Output/"+to_string(idIteration)+"/*");
        system(rm);
    }

}

void functions::CreateSupDir(int idIteration, int iterator){
    string command = "../Output/"+to_string(idIteration)+"/superiorizacao/";
    const char* file = (char*) command.c_str();
    DIR* dp = opendir(file);

    if(dp == NULL){
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/superiorizacao/"));
    }

    command = "../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator);
    file = (char*) command.c_str();
    dp = opendir(file);

    if(dp == NULL){;
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/oleo"));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/agua"));
        system(Command("mkdir ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/gas"));
    }else{
        const char* rm = Command("rm -f ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/*");
        system(rm);
    }
}

void functions::WriteSimulationFile(int idIteration, int iterator, bool sup, string inputFile, string file, string permeabilityFile, individual sCandidate){
    ifstream input(inputFile, ios::in);
    ifstream inputPermeability("../Input/"+permeabilityFile, ios::in);
    ofstream outputPermeability, output;

    if(sup){
        outputPermeability.open("../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/0-"+permeabilityFile, ios::out);
        output.open("../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/0-"+file+".DATA", ios::out);
    }else{
        outputPermeability.open("../Output/"+to_string(idIteration)+"/"+to_string(iterator)+"-"+permeabilityFile, ios::out);
        output.open("../Output/"+to_string(idIteration)+"/"+to_string(iterator)+"-"+file+".DATA", ios::out);
    }

    string line;
    int count = 0;
    int index = 0;

    while(!input.eof()){
        getline(input, line);
        if(count == 131){
            if(sup){
                output << "    " << "0-"+permeabilityFile+" /" << endl;
            }else{
                output << "    " << to_string(iterator)+"-"+permeabilityFile+" /" << endl;
            }
        }else if((count > 112) && (count < 128)){
            if(count == 127){
                output << "    600*" << sCandidate.porosity[index]  << " /" << endl;
            index++;
            }else{
                output << "    600*" << sCandidate.porosity[index] << endl;
                index++;
            }
        }else{
            output << line << endl;
        }

        count++;
    }

    input.close();
    output.close();

    line = "";
    count = 0;

    while(!inputPermeability.eof()){
        getline(inputPermeability, line);
        if(count < 1226){
            outputPermeability << line  << endl;
        }

        count++;
    }

    for(int i = 0; i < TOTAL_CELLS; i++){
        if(i == (TOTAL_CELLS -1)){
            outputPermeability << sCandidate.permeability[i] << " /" << endl;
            outputPermeability << endl;
            outputPermeability <<  "COPY" << endl;
            outputPermeability <<  "	PERMX PERMY  /" << endl;
            outputPermeability <<  "	PERMX PERMZ  /" << endl;
            outputPermeability <<  "/" << endl;
            outputPermeability <<  "MULTIPLY" << endl;
            outputPermeability <<  "	PERMZ 0.01 /" << endl;
            outputPermeability <<  "/" << endl;
        }else{
            outputPermeability << sCandidate.permeability[i] << endl;
        }
    }

    inputPermeability.close();
    outputPermeability.close();
    
}

void functions::WriteErrorFile(int idIteration, int iterator, bool sup, individual sCandidate){
    ofstream errorFile;

    if(sup){
        errorFile.open("../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/error.txt", ios::app);
    }else{
        errorFile.open("../Output/"+to_string(idIteration)+"/error.txt", ios::app);
    }
    
    
    errorFile << sCandidate.error_rank << endl;

    errorFile.close();
}

double functions::activationFunction(string waterOutputResult, string oilOutputResult, string gasOutputResult, vector<result> results, int idIteration){
    double rank;

    string waterResult = ReadFileInput(waterOutputResult);
    string oilResult = ReadFileInput(oilOutputResult);
    string gasResult = ReadFileInput(gasOutputResult);

    vector<result> simulateResults;

    simulateResults = ConvertStringInputToDoubleResult(waterResult, oilResult, gasResult);

    double minRealWater = 100000, maxRealWater = 0, minRealOil = 100000, maxRealOil = 0, minRealGas = 100000, maxRealGas = 0;
    double minSimulateWater = 100000, maxSimulateWater = 0, minSimulateOil = 100000, maxSimulateOil = 0, minSimulateGas = 100000, maxSimulateGas = 0;

    for(int i = 0; i < results.size(); i++){
        minRealWater = Min(minRealWater, results[i].water);
        maxRealWater = Max(maxRealWater, results[i].water);

        minRealOil = Min(minRealOil, results[i].oil);
        maxRealOil = Max(maxRealOil, results[i].oil);

        minRealGas = Min(minRealGas, results[i].gas);
        maxRealGas = Max(maxRealGas, results[i].gas);
    }

    for(int i = 0; i < simulateResults.size(); i++){
        minSimulateWater = Min(minSimulateWater, simulateResults[i].water);
        maxSimulateWater = Max(maxSimulateWater, simulateResults[i].water);

        minSimulateOil = Min(minSimulateOil, simulateResults[i].oil);
        maxSimulateOil = Max(maxSimulateOil, simulateResults[i].oil);

        minSimulateGas = Min(minSimulateGas, simulateResults[i].gas);
        maxSimulateGas = Max(maxSimulateGas, simulateResults[i].gas);
    }

    for(int i = 0; i < N_METRICS; i++){
        if(i == 0){
            for(int j = 0; j < simulateResults.size(); j++){
                rank += pow(Normalize(results[j].water, minRealWater, maxRealWater) - Normalize(simulateResults[j].water, minSimulateWater, maxSimulateWater),2);
            }
            rank *= WATER_WEIGHT;
        }else if(i == 1){
            for(int j = 0; j < simulateResults.size(); j++){
                rank += pow(Normalize(results[j].oil, minRealOil, maxRealOil) - Normalize(simulateResults[j].oil, minSimulateOil, maxSimulateOil),2);
            }
            rank *= OIL_WEIGHT;
        }else if(i == 2){
            for(int j = 0; j < simulateResults.size(); j++){
                rank += pow(Normalize(results[j].gas, minRealGas, maxRealGas) - Normalize(simulateResults[j].gas, minSimulateGas, maxSimulateGas),2);
            }
            rank *= GAS_WEIGHT;
        }           
    }

    rank = sqrt((rank / (simulateResults.size() * N_METRICS)));

    return rank;
}
