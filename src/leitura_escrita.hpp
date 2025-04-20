#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;
ifstream abrirArquivo();
ifstream abrirSaida();
void escreverNoOutput(string mensagem);


vector<vector<int>> lerMatriz(ifstream &input, int columSize, int lineSize);