#pragma once
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include "leitura_escrita.hpp"
#include "config.hpp"

void simulacao();
bool interation(vector<vector<int>>& inicialMatrix, int lineSize, int columSize, int fireStart_X, int fireStart_Y, vector<tuple<int, int, int>>& propag, int k);
void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize, int k);

tuple<int, int, int, int> setPosAnimal(vector<vector<int>>& inicialMatrix, int lineSize, int columSize);

void moverAnimal(tuple<int, int, int, int>& animal, pair<int, int>& animalPosAnt, vector<vector<int>>& matriz, int lineSize, int columSize);

bool posicaoValida(int x, int y, int linhas, int colunas);

void apagarFogo(int x, int y, vector<vector<int>>& matriz, int lineSize, int columSize);