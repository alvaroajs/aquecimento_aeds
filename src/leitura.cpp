#include "leitura.hpp"

ifstream abrirArquivo() {
    ifstream input("data/input.dat");
    int lineSize = 0, columSize = 0;
   
    return input;

}

vector<vector<int>> lerMatriz(ifstream &input, int lineSize, int columSize) {
    
    vector<vector<int>> matriz(lineSize, vector<int>(columSize)); // criando a matriz
    for (int i = 0; i < lineSize; i++) {
        for (int j = 0; j < columSize; j++) {
            input >> matriz[i][j];
        }
    }
    
    
    return matriz;

}