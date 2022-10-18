#include "tabu.hpp"

void tabu_search::FirstSimulation(){
    srand((unsigned)time(0));

    CreateResultDir(0);

    vector<double> randomPermeability;

    randomPermeability.resize(TOTAL_CELLS);

    for(int j = 0; j < N_POROSITY; j++){
        this->sBest.porosity[j] = Rand_double(MIN_POROSITY, MAX_POROSITY);
        for(int k = 0; k < TOTAL_CELLS; k++){
            if(k < 900){
                randomPermeability[k] = Rand_double(MIN_PERMEABILITY_1, MAX_PERMEABILITY_1);
            }else if(k >= 900 && k < 3300){
                randomPermeability[k] = Rand_double(MIN_PERMEABILITY_2, MAX_PERMEABILITY_2);
            }else if(k >= 3300 && k < 3600){
                randomPermeability[k] = Rand_double(MIN_PERMEABILITY_3, MAX_PERMEABILITY_3);
            }else if(k >= 3600 && k < 3900){
                randomPermeability[k] = Rand_double(MIN_PERMEABILITY_4, MAX_PERMEABILITY_4);
            }else if(k >= 3900 && k < 4200){
                randomPermeability[k] = Rand_double(MIN_PERMEABILITY_5, MAX_PERMEABILITY_5);
            }
        }
    }

    for(int j = 0; j < TOTAL_CELLS; j++){
        if(randomPermeability.size() == 0){
            this->sBest.permeability[j] = randomPermeability[0];
        }else{
            int index = rand() % randomPermeability.size();
            this->sBest.permeability[j] = randomPermeability[index];
            auto removeElement = randomPermeability.begin() + index;
            if(randomPermeability.end() != randomPermeability.end()){
                randomPermeability.erase(removeElement);
            }
        }
    }

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(0)+"/TOPSVALUES.DATA"));

    WriteSimulationFile(0, 0, false, simulationFile, fileName, permeabilityFile, this->sBest);
    
    for(int i = 0; i < 1; i++)
    Suavity(sBest);

    // Simulation(0, 0, 1, fileName, false);
    // sBest.error_rank = Fitness(0, 0, false, this->sBest);

    // WriteErrorFile(0, 0, false, this->sBest);

    // this->tabuList.push_back(sBest);

    // this->bestCandidate = sBest;

    // Superiorization(this->bestCandidate, 0);
}

void tabu_search::OthersSimulations(int idIteration){
    GetNeighbors(this->bestCandidate);

    CreateResultDir(idIteration);

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(idIteration)+"/TOPSVALUES.DATA"));

    for(int i = 0; i < SIZE; i++){
        WriteSimulationFile(idIteration, i, false, simulationFile, fileName, permeabilityFile, this->sNeighborhood[i]);
    }

    Simulation(idIteration, 0, SIZE, fileName, false);
    for(int i = 0; i < SIZE; i++){
        this->sNeighborhood[i].error_rank = Fitness(idIteration, i, false, this->sNeighborhood[i]);
    }

    for(int i = 0; i < SIZE; i++){
        WriteErrorFile(idIteration, 0, false, this->sNeighborhood[i]);
    }

    this->bestCandidate = sNeighborhood[0];

    for(int i = 0; i < SIZE; i++){
        // if(!Contains(sNeighborhood[i]) && sNeighborhood[i].error_rank < this->bestCandidate.error_rank){
        //     this->bestCandidate = sNeighborhood[i];
        // }
        if(sNeighborhood[i].error_rank < this->bestCandidate.error_rank){
            this->bestCandidate = sNeighborhood[i];
        }
    }

    Superiorization(this->bestCandidate, idIteration);

    if(this->bestCandidate.error_rank < this->sBest.error_rank){
        this->sBest = this->bestCandidate;
    }

    this->tabuList.push_back(this->bestCandidate);

    if(tabuList.size() > TABU_SIZE){
        tabuList.erase(tabuList.begin());
    }

}

double tabu_search::Fitness(int idIteration, int iterator, bool sup, individual sCandidate){
    string oilOutputResult, waterOutputResult, gasOutputResult;
    if(sup){
        oilOutputResult = "../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/oleo/0-oleo";
        waterOutputResult = "../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/agua/0-agua";
        gasOutputResult = "../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(iterator)+"/gas/0-gas";
    }else{
        oilOutputResult = "../Output/"+to_string(idIteration)+"/oleo/"+to_string(iterator)+"-oleo";
        waterOutputResult = "../Output/"+to_string(idIteration)+"/agua/"+to_string(iterator)+"-agua";
        gasOutputResult = "../Output/"+to_string(idIteration)+"/gas/"+to_string(iterator)+"-gas";
    }
    double error = activationFunction(waterOutputResult, oilOutputResult, gasOutputResult, realResults, idIteration);
    
    return error;
}

void tabu_search::Suavity(individual sCandidate){
    double sDeviation = 0, mean = 0, totalSuavity = 0;

    for(int i = 0; i < TOTAL_CELLS; i++){
        mean += sCandidate.permeability[i] / TOTAL_CELLS;
    }

    for(int i = 0; i < TOTAL_CELLS; i++){
        sDeviation += pow((sCandidate.permeability[i] - mean), 2) / TOTAL_CELLS;
    }

    sDeviation = sqrt(sDeviation);

    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            double suavity;

            if((i-1 < 0) || (j-1 < 0)){
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[i*WIDTH+(j+1)];
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[(i+1)*WIDTH+j];

                suavity /= N_BLOCKS / 2;
            }else if((i+1 >= HEIGHT) || (j+1 >= WIDTH)){
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[i*WIDTH+(j-1)];
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[(i-1)*WIDTH+j];

                suavity /= N_BLOCKS / 2;

                totalSuavity += pow(suavity, 2) / N_BLOCKS / 2 * sDeviation;
            }else{
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[i*WIDTH+(j+1)];
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[(i+1)*WIDTH+j];
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[i*WIDTH+(j-1)];
                suavity += sCandidate.permeability[i*WIDTH+j] - sCandidate.permeability[(i-1)*WIDTH+j];

                suavity /= N_BLOCKS;

                totalSuavity += pow(suavity, 2) / N_BLOCKS * sDeviation;
            }
            cout << suavity << endl;
        }
    }

    cout << totalSuavity << endl;

    double minSuavity = 750, maxSuavity = 100;

    totalSuavity = Normalize(totalSuavity, minSuavity, maxSuavity);

    for(int i = 0; i < TOTAL_CELLS; i++){
        suavityImage[i] = Rand_double(MIN_LAMBDA, MAX_LAMBDA) * abs(totalSuavity);
        //cout << suavityImage[i] << " " << abs(totalSuavity) << endl;
    }
}

void tabu_search::GetNeighbors(individual bestCandidate){
    for(int i = 0; i < SIZE; i++){
        if(i < (SIZE / 2)){
            double randomPorosity[N_POROSITY];
            double randomPermeability[TOTAL_CELLS];

            for(int j = 0; j < N_POROSITY; j++){
                randomPorosity[j] = Rand_double(bestCandidate.porosity[j], bestCandidate.porosity[j]+0.02);
                this->sNeighborhood[i].porosity[j] = Min(randomPorosity[j], MAX_POROSITY);
            }

            for(int j = 0; j < TOTAL_CELLS; j++){
                if(bestCandidate.permeability[j] < 50){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]+5);
                    this->sNeighborhood[i].permeability[j] = Min(randomPermeability[j], MAX_PERMEABILITY_1);
                }else if(bestCandidate.permeability[j] >= 50 && bestCandidate.permeability[j] < 500){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]+40);
                    this->sNeighborhood[i].permeability[j] = Min(randomPermeability[j], MAX_PERMEABILITY_2);
                }else if(               bestCandidate.permeability[j] >= 500 && bestCandidate.permeability[j] < 2000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]+100);
                    this->sNeighborhood[i].permeability[j] = Min(randomPermeability[j], MAX_PERMEABILITY_3);
                }else if(bestCandidate.permeability[j] >= 2000 && bestCandidate.permeability[j] < 4000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]+200);
                    this->sNeighborhood[i].permeability[j] = Min(randomPermeability[j], MAX_PERMEABILITY_4);
                }else if(bestCandidate.permeability[j] >= 4000 && bestCandidate.permeability[j] < 8000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]+350);
                    this->sNeighborhood[i].permeability[j] = Min(randomPermeability[j], MAX_PERMEABILITY_5);
                }
            }

        }else{
            double randomPorosity[N_POROSITY];
            double randomPermeability[TOTAL_CELLS];

            for(int j = 0; j < N_POROSITY; j++){
                randomPorosity[j] = Rand_double(bestCandidate.porosity[j], bestCandidate.porosity[j]-0.02);
                this->sNeighborhood[i].porosity[j] = Min(randomPorosity[j], MAX_POROSITY);
            }

            for(int j = 0; j < TOTAL_CELLS; j++){
                if(bestCandidate.permeability[j] < 50){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]-5);
                    this->sNeighborhood[i].permeability[j] = Max(randomPermeability[j], MIN_PERMEABILITY_1);
                }else if(bestCandidate.permeability[j] >= 50 && bestCandidate.permeability[j] < 500){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]-40);
                    this->sNeighborhood[i].permeability[j] = Max(randomPermeability[j], MIN_PERMEABILITY_2);
                }else if(bestCandidate.permeability[j] >= 500 && bestCandidate.permeability[j] < 2000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]-100);
                    this->sNeighborhood[i].permeability[j] = Max(randomPermeability[j], MIN_PERMEABILITY_3);
                }else if(bestCandidate.permeability[j] >= 2000 && bestCandidate.permeability[j] < 4000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]-200);
                    this->sNeighborhood[i].permeability[j] = Max(randomPermeability[j], MIN_PERMEABILITY_4);
                }else if(bestCandidate.permeability[j] >= 4000 && bestCandidate.permeability[j] < 8000){
                    randomPermeability[j] = Rand_double(bestCandidate.permeability[j], bestCandidate.permeability[j]-350);
                    this->sNeighborhood[i].permeability[j] = Max(randomPermeability[j], MIN_PERMEABILITY_5);
                }
            }
        }
    }
}

bool tabu_search::Contains(individual sCandidate){
    bool contains = false;

    // for(int i = 0; i < this->tabuList.size(); i++){
    //     if((sCandidate.permeability[0][0].permeability_1 == this->tabuList[i].permeability[0][0].permeability_1) and
    //     (sCandidate.permeability[0][0].permeability_2 == this->tabuList[i].permeability[0][0].permeability_2) and
    //     (sCandidate.permeability[0][0].permeability_3 == this->tabuList[i].permeability[0][0].permeability_3)){
    //         contains = true;
    //     }
    // }

    return contains;
}

void tabu_search::SaveTabuList(){
    CreateResultDir(N_ITERATIONS+1);

    for(int i = 0; i < tabuList.size(); i++){
        WriteSimulationFile(N_ITERATIONS+1, i, false, simulationFile, fileName, permeabilityFile, this->tabuList[i]);
    }

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(N_ITERATIONS+1)+"/TOPSVALUES.DATA"));

    Simulation(N_ITERATIONS+1, 0, this->tabuList.size(), fileName, false);
    for(int i = 0; i < tabuList.size(); i++){
        this->tabuList[i].error_rank = Fitness(N_ITERATIONS+1, i, false, this->tabuList[i]);
    }

    for(int i = 0; i < tabuList.size(); i++){
        WriteErrorFile(N_ITERATIONS+1, 0, false, this->tabuList[i]);
    }
}

void tabu_search::SaveBest(){
    CreateResultDir(N_ITERATIONS+2);

    WriteSimulationFile(N_ITERATIONS+2, 0, false, simulationFile, fileName, permeabilityFile, this->sBest);

    system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(N_ITERATIONS+2)+"/TOPSVALUES.DATA"));

    Simulation(N_ITERATIONS+2, 0, 1, fileName, false);
    sBest.error_rank = Fitness(N_ITERATIONS+2, 0, false, this->sBest);

    WriteErrorFile(N_ITERATIONS+2, 0, false, this->sBest);
}

void tabu_search::Superiorization(individual image, int idIteration){
    int n = 0;
    int l = -2;
    while (n < SUPERIOZATION_SIZE){
        CreateSupDir(idIteration, n);
        cout << "Iteração " << n << " do método de superiorização" << endl;
        individual imageSup = image;
        bool loop = true;
        int count = 0;
        while(loop){
            l++;
            double beta = pow(a, l);
            individual nextImage;

            if(idIteration != 0){
                Suavity(imageSup);
            }

            for(int i = 0; i < N_POROSITY; i++){
                nextImage.porosity[i] = Rand_double(MIN_POROSITY, MAX_POROSITY);    
            }

            for(int i = 0; i < TOTAL_CELLS; i++){
                nextImage.permeability[i] = image.permeability[i] + beta * suavityImage[i];
                cout << nextImage.permeability[i] << " = " << image.permeability[i] << " + " << beta << " * " << suavityImage[i] << endl;
            }


            WriteSimulationFile(idIteration, n, true, simulationFile, fileName, permeabilityFile, nextImage);

            system(Command("cp ../Input/TOPSVALUES.DATA ../Output/"+to_string(idIteration)+"/superiorizacao/"+to_string(n)+"/TOPSVALUES.DATA"));

            Simulation(idIteration, n, 1, fileName, true);

            nextImage.error_rank = Fitness(idIteration, n, true, nextImage);

            WriteErrorFile(idIteration, n, true, nextImage);

            imageSup = nextImage;

            if((nextImage.error_rank <= image.error_rank) || (count+1 == 10) || (nextImage.error_rank <= STOP)){
                n++;
                image = nextImage;
                loop = false;
            }
            count++;
        }
        this->bestCandidate = image;
    }
    
}

void tabu_search::Init(){
    CreateOutputDir();

    string oilInputResult = ReadFileInput(inputOil);
    string waterInputResult = ReadFileInput(inputWater);
    string gasInputResult = ReadFileInput(inputGas);

    this->realResults = ConvertStringInputToDoubleResult(waterInputResult, oilInputResult, gasInputResult); 

    ifstream priors("../Input/priors.txt", ios::in);
    string line, content;

    while(!priors.eof()){
        getline(priors, line);
        content += line;
        content += " ";
    }

    priors.close();

    vector<string> suavitySplit{split(content, ' ')};
    vector<double>suavityValues;

    for(int i = 0; i < suavitySplit.size(); i++){
        double partialSuavity;
        partialSuavity = stod(suavitySplit[i]);
        suavityValues.push_back(partialSuavity);
    }

    double minSuavity = 10000, maxSuavity = 0;

    for(int i = 0; i < suavityValues.size(); i++){
        minSuavity = Min(minSuavity, suavityValues[i]);
        maxSuavity = Max(maxSuavity, suavityValues[i]);
    }

    for(int i = 0; i < suavityValues.size(); i++){
        this->suavityImage[i] = Normalize(suavityValues[i], minSuavity, maxSuavity);
    }

    FirstSimulation();
    int count = 1;
    // while(count <= N_ITERATIONS && this->sBest.error_rank > STOP){
    //     OthersSimulations(count);
    //     count++;
    // }

    // SaveTabuList();

    // SaveBest();

}
