#include "simulacao.hpp"


void simulacao(){
    int lineSize = 0, columSize = 0, fireStart_X = 0, fireStart_Y = 0;
    string linha;
    ifstream input =  abrirArquivo(); //funcao abrirArquivo() retorna um um ponteiro do tipo ifstream
    ifstream output = abrirSaida();
    bool stop;

    vector<tuple<int, int, int>> propag;

    tuple<int, int, int> animal; //posx, posy, passos
    pair<int, int> animalPosAnt;

    if (!input) { // verifica se o arquivo foi aberto corretamente
        cout << "Erro ao abrir o arquivo: " << "../input.dat" << endl;
        return;
    }
    if (!output) { // verifica se o arquivo foi aberto corretamente
        cout << "Erro ao abrir o arquivo: " << "../output.dat" << endl;
        return;
    }
    input >> lineSize >> columSize; //leitura do tamanho da matriz
    input >> fireStart_X >> fireStart_Y; //leitura da posicao do animal
    getline(input, linha); // descarta o restante da linha
    
    vector<vector<int>> inicialMatrix = lerMatriz(input, lineSize, columSize); //leitura da matriz
    animal = setPosAnimal(inicialMatrix,lineSize, columSize); 
    
    for(int k = 0; k < K_MAX; k++){
        cout << "\nInteracao: " << k + 1 << endl;
        stop = interation(inicialMatrix, lineSize, columSize, fireStart_X, fireStart_Y, propag, k); 

        showMatrix(inicialMatrix, lineSize, columSize, k);
        if(!stop){
            break;
        }

    }
    input.close();
}
bool interation(vector<vector<int>>& matriz, int linhas, int colunas, int fireStart_X, int fireStart_Y, vector<tuple<int, int, int>>& propag, int k) {
    vector<vector<int>> novaMatriz = matriz;
    // Adiciona a posição inicial do fogo à lista com contador 0
    propag.push_back(make_tuple(fireStart_X, fireStart_Y, 0));
    bool propagNorth = false, propagSouth = false, propagEast = false, propagWest = false;
    // Propaga o fogo das posições atuais
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2 ) {
                if (i > 0 && matriz[i - 1][j] == 1 && northWind) {
                    novaMatriz[i - 1][j] = 2;
                    propag.push_back(make_tuple(i - 1, j, 0));
                    propagNorth = true;
                }
                if (i < linhas - 1 && matriz[i + 1][j] == 1 && southWind) {
                    novaMatriz[i + 1][j] = 2;
                    propag.push_back(make_tuple(i + 1, j, 0));
                    propagSouth = true;
                }
                if (j > 0 && matriz[i][j - 1] == 1 && eastWind) {
                    novaMatriz[i][j - 1] = 2;
                    propag.push_back(make_tuple(i, j - 1, 0));
                    propagEast = true;
                }
                if (j < colunas - 1 && matriz[i][j + 1] == 1 && westWind) {
                    novaMatriz[i][j + 1] = 2;
                    propag.push_back(make_tuple(i, j + 1, 0));
                    propagWest = true;
                }
            }
        }
    }

    
    for (auto it = propag.begin(); it != propag.end();) {
        int x = get<0>(*it);
        int y = get<1>(*it);
        int interacoes = get<2>(*it);

        if (interacoes >= 2) {
            novaMatriz[x][y] = 3;
            it = propag.erase(it); // remove a célula que já virou 3
        } else {
            novaMatriz[x][y] = 2;
            *it = make_tuple(x, y, interacoes + 1); // incrementa o contador
            ++it;
        }
    }

    if (k >= 1){
        novaMatriz[fireStart_X][fireStart_Y] = 3; // marca a posição inicial do fogo como 2
    }
    matriz = novaMatriz;

    cout << "\nMatriz atualizada:\n" << endl;
    
    return (propagNorth || propagSouth || propagEast || propagWest); // retorna true se houver propagação
}

tuple<int, int, int> setPosAnimal(vector<vector<int>>& inicialMatrix, int lineSize, int columSize){
    int x = 0, y = 0;

    for (int i = (lineSize - 1); i >= 0; i--){
        for(int j = columSize - 1; j >= 0; i--){
            if(inicialMatrix[i][j]  != 2){
                return make_tuple(i, j, 0);
            }
        }
    }
}


void moverAnimal(vector<tuple<int, int, int>> animal, vector<pair<int, int>> animalPosAnt){




}




void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize, int k){
    escreverNoOutput("\nInteracao: " + to_string(k + 1) + "\n");
    for(int i = 0; i < lineSize; i++){
        for(int j = 0; j < columSize; j++){
            cout << matriz[i][j] << " ";
            escreverNoOutput(to_string(matriz[i][j])); // escreve no arquivo de saída
            escreverNoOutput(" ");
        }
        escreverNoOutput("\n");
        cout << endl;
    }
    escreverNoOutput("\n");

}
bool posicaoValida(int x, int y, int linhas, int colunas) {
    
    return (x > 0 && x < linhas - 1 ) || (y > 0 && y < colunas - 1); // verifica se pode ir mais para o norte ou sul

    
}



