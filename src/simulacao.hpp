#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "leitura.hpp"
#include "config.hpp"

void simulacao();
void interation(vector<vector<int>>& matriz, int lineSize, int columSize, int fireStart_X, int fireStart_Y);
void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize);
bool posicaoValida(int x, int y, int linhas, int colunas);