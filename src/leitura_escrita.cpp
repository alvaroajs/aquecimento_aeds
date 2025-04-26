#include "leitura_escrita.hpp"

ifstream abrirArquivo() {
    ifstream input("data/input.dat");   
    return input;

}
ifstream abrirSaida() {
    const string caminho = "data/output.dat";

    
    ofstream limpaArquivo(caminho); 
    limpaArquivo.close();

    ifstream output(caminho);
    return output;
}

vector<vector<int>> lerMatriz(ifstream &input, int lineSize, int columSize) {
    
    vector<vector<int>> matriz(lineSize, vector<int>(columSize)); 
    for (int i = 0; i < lineSize; i++) {
        for (int j = 0; j < columSize; j++) {
            input >> matriz[i][j];
        }
    }    
    return matriz;
}

void escreverNoOutput(string mensagem) {
    ofstream output("data/output.dat", ios::app);
   
    output << mensagem;
    output.close();
    
}