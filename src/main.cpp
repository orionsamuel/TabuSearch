#include <iostream>
#include "../include/tabu.hpp"

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    tabu_search ts;
    
    ts.Init();

    cout << "Finish" << endl;
    
    auto end = std::chrono::high_resolution_clock::now();

    auto totalTime = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    cout << "Tempo total de execução: " << totalTime.count() << " segundos" << endl;

    return 0;
}
