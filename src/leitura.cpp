#include "leitura.hpp"

void lerarquivo() {
    ifstream input("data/input.dat");
    int lineSize = 0, columSize = 0;
    if (!input) {
        cout << "Erro ao abrir o arquivo: " << "../input.dat" << endl;
        return;
    }
    string linha;
    input >> lineSize >> columSize;
    cout << "Tamanho da linha: " << lineSize << endl;
    cout << "Tamanho da coluna: " << columSize << endl;
    while (getline(input, linha)) {
        cout << linha << endl;
    }
    if (input.is_open()) {
        input.close();
    }
    cout << "Arquivo lido com sucesso!" << endl;



}