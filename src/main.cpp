
#include "simulacao.hpp"
#include <iostream>
#include <chrono>

int main(){
    auto inicio = std::chrono::high_resolution_clock::now();
    simulacao();
    auto fim = std::chrono::high_resolution_clock::now();

    // Calcula a duração
    std::chrono::duration<double> duracao = fim - inicio;

    // Exibe o tempo em segundos
    std::cout << "\nTempo de execução: " << duracao.count() << " segundos" << std::endl;

    return 0;
}