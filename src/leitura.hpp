#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
ifstream abrirArquivo();
vector<vector<int>> lerMatriz(ifstream &input, int columSize, int lineSize);