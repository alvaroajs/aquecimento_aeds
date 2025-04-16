#pragma once
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>
#include "leitura.hpp"
#include "config.hpp"
#include "interaction.hpp"

void simulacao();
bool interation(vector<vector<int>>& inicialMatrix, int lineSize, int columSize, int fireStart_X, int fireStart_Y, vector<tuple<int, int, int>>& propag, int k);
void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize);
bool posicaoValida(int x, int y, int linhas, int colunas);