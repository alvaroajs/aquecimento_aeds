#include "leitura_escrita.hpp"

ifstream abrirArquivo() {
    ifstream input("data/input.dat");   
    return input;

}
ifstream abrirSaida() {
    const string caminho = "data/output.dat";

    // Garante que a pasta existe

    // Abre com ofstream para apagar o conteúdo
    ofstream limpaArquivo(caminho); // modo truncado (ios::trunc) é o padrão
    limpaArquivo.close();

    // Agora abre com ifstream para leitura
    ifstream output(caminho);
    return output;
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

void escreverNoOutput(string mensagem) {
    ofstream output("data/output.dat", ios::app); // Abre o arquivo em modo de anexação
    if (output.is_open()) {
        output << mensagem;
        output.close();
    } else {
        cout << "Erro ao abrir o arquivo de saída." << endl;
    }
}