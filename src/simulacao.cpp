#include "simulacao.hpp"


void simulacao(){
    int lineSize = 0, columSize = 0, fireStart_X = 0, fireStart_Y = 0;
    string linha;
    ifstream input =  abrirArquivo(); //funcao abrirArquivo() retorna um um ponteiro do tipo ifstream
    ifstream output = abrirSaida();
    bool stop;

    vector<tuple<int, int, int>> propag;

    tuple<int, int, int, int> animal; //posx, posy, passos, quantas vezes ta parado na mesma posição
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
        moverAnimal(animal, animalPosAnt, inicialMatrix, lineSize, columSize);
        showMatrix(inicialMatrix, lineSize, columSize, k);
        cout << "Animal na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos" << endl;
        if(!stop){
            cout << "Animal parou na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos" << endl;
            {
                if(get<3>(animal) != -1){
                    ostringstream oss;
                    oss << "Animal parou na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos.\n";
                    escreverNoOutput(oss.str());
                }
                else{
                    ostringstream oss;
                    oss << "Animal morreu na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos.\n";
                    escreverNoOutput(oss.str());
                }
            }
            break;
        }

    }
    input.close();
}
bool interation(vector<vector<int>>& matriz, int linhas, int colunas, int fireStart_X, int fireStart_Y, vector<tuple<int, int, int>>& propag, int k) {
    vector<vector<int>> novaMatriz = matriz;
    
    // Adicionar posição inicial se for a primeira iteração (k=0)
    if (k == 0) {
        propag.push_back(make_tuple(fireStart_X, fireStart_Y, 0));
        novaMatriz[fireStart_X][fireStart_Y] = 2;
    }
    
    bool houvePropagacao = false;
    
    // Propaga o fogo das posições atuais
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) {
                // Propaga para o norte (acima)
                if (i > 0 && matriz[i - 1][j] == 1 && northWind) {
                    novaMatriz[i - 1][j] = 2;
                    propag.push_back(make_tuple(i - 1, j, 0));
                    houvePropagacao = true;
                }
                // Propaga para o sul (abaixo)
                if (i < linhas - 1 && matriz[i + 1][j] == 1 && southWind) {
                    novaMatriz[i + 1][j] = 2;
                    propag.push_back(make_tuple(i + 1, j, 0));
                    houvePropagacao = true;
                }
                // Propaga para o oeste (esquerda)
                if (j > 0 && matriz[i][j - 1] == 1 && westWind) {
                    novaMatriz[i][j - 1] = 2;
                    propag.push_back(make_tuple(i, j - 1, 0));
                    houvePropagacao = true;
                }
                // Propaga para o leste (direita)
                if (j < colunas - 1 && matriz[i][j + 1] == 1 && eastWind) {
                    novaMatriz[i][j + 1] = 2;
                    propag.push_back(make_tuple(i, j + 1, 0));
                    houvePropagacao = true;
                }
            }
        }
    }
    
    // Atualiza as árvores em chamas que devem virar árvores queimadas
    for (auto it = propag.begin(); it != propag.end();) {
        int x = get<0>(*it);
        int y = get<1>(*it);
        int interacoes = get<2>(*it);
        
        if (interacoes >= 2) {
            novaMatriz[x][y] = 3; // Árvore queimada
            it = propag.erase(it); // Remove da lista
        } else {
            *it = make_tuple(x, y, interacoes + 1); // Incrementa contador
            ++it;
        }
    }
    
    matriz = novaMatriz;
    return houvePropagacao;
}

tuple<int, int, int, int> setPosAnimal(vector<vector<int>>& inicialMatrix, int lineSize, int columSize){
    int x = 0, y = 0;

    for (int i = (lineSize - 1); i >= 0; i--){
        for(int j = columSize - 1; j >= 0; j--){
            if(inicialMatrix[i][j]  == 0){
                return make_tuple(i, j, 0, 0);
            }
        }
    }
    return make_tuple(0, 0, 0, 0);
}


void moverAnimal(tuple<int, int, int, int>& animal, pair<int, int>& animalPosAnt, vector<vector<int>>& matriz, int lineSize, int columSize) {
    int x = get<0>(animal);
    int y = get<1>(animal);
    int passos = get<2>(animal);
    int parado = get<3>(animal);
    animalPosAnt = make_pair(x, y);

    // !!! Verifica se a posição atual do animal foi atingida pelo fogo (valor 2) !!!
    if (matriz[x][y] == 2) {
        // Segunda chance - tenta mover o animal para uma posição segura
        
        // Primeira prioridade: Água (valor 4)
        if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 4){        
            apagarFogo(x + 1, y, matriz, lineSize, columSize);
            animal = make_tuple(x + 1, y, passos + 1, 0);
            matriz[x + 1][y] = 0; 
            return;
        }
        else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 4){
            apagarFogo(x - 1, y, matriz, lineSize, columSize);
            animal = make_tuple(x - 1, y, passos + 1, 0);
            matriz[x - 1][y] = 0;
            return;
        }
        else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 4){
            apagarFogo(x, y + 1, matriz, lineSize, columSize);
            animal = make_tuple(x, y + 1, passos + 1, 0);
            matriz[x][y + 1] = 0;
            return;
        }
        else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 4){
            apagarFogo(x, y - 1, matriz, lineSize, columSize);
            animal = make_tuple(x, y - 1, passos + 1, 0);
            matriz[x][y - 1] = 0;
            return;
        }
        
        // Segunda prioridade: Árvore saudável (valor 1)
        if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 1){
            animal = make_tuple(x + 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 1){
            animal = make_tuple(x - 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 1){
            animal = make_tuple(x, y + 1, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 1){
            animal = make_tuple(x, y - 1, passos + 1, 0);
            return;
        }
        
        // Terceira prioridade: Área vazia (valor 0)
        if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 0){
            animal = make_tuple(x + 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 0){
            animal = make_tuple(x - 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 0){
            animal = make_tuple(x, y + 1, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 0){
            animal = make_tuple(x, y - 1, passos + 1, 0);
            return;
        }
        
        // Quarta prioridade: Árvore queimada (valor 3)
        if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 3){
            animal = make_tuple(x + 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 3){
            animal = make_tuple(x - 1, y, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 3){
            animal = make_tuple(x, y + 1, passos + 1, 0);
            return;
        }
        else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 3){
            animal = make_tuple(x, y - 1, passos + 1, 0);
            return;
        }
        
        // Se não houver opção segura, o animal morre
        animal = make_tuple(x, y, passos, -1); // -1 indica que o animal morreu
        return;
    }
    
    // Movimento normal (quando a posição não está em chamas)
    
    // prioridade 1: Água (valor 4)
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 4){        
        apagarFogo(x + 1, y, matriz, lineSize, columSize);
        animal = make_tuple(x + 1, y, passos + 1, 0);
        matriz[x + 1][y] = 0; 
        cout << "Apagou na x: "<< x << ", y: " << y << endl;
        return;
    }
    else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 4){
        apagarFogo(x - 1, y, matriz, lineSize, columSize);
        animal = make_tuple(x - 1, y, passos + 1, 0);
        matriz[x - 1][y] = 0;
        cout << "Apagou na x: "<< x << ", y: " << y << endl;

        return;
    }
    else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 4){
        apagarFogo(x, y + 1, matriz, lineSize, columSize);
        animal = make_tuple(x, y + 1, passos + 1, 0);
        matriz[x][y + 1] = 0;
        cout << "Apagou na x: "<< x << ", y: " << y << endl;

        return;
    }
    else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 4){
        apagarFogo(x, y - 1, matriz, lineSize, columSize);
        animal = make_tuple(x, y - 1, passos + 1, 0);
        matriz[x][y - 1] = 0;
        cout << "Apagou na x: "<< x << ", y: " << y << endl;

        return;
    }
    
    // prioridade 4: Árvore saudável (valor 1)
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 1){
        animal = make_tuple(x + 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 1){
        animal = make_tuple(x - 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 1){
        animal = make_tuple(x, y + 1, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 1){
        animal = make_tuple(x, y - 1, passos + 1, 0);
        return;
    }
    
    // prioridade 3: Área vazia (valor 0)
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 0){
        animal = make_tuple(x + 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 0){
        animal = make_tuple(x - 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 0){
        animal = make_tuple(x, y + 1, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 0){
        animal = make_tuple(x, y - 1, passos + 1, 0);
        return;
    }
    
    // prioridade 4: Árvore queimada (valor 3)
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 3){
        animal = make_tuple(x + 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 3){
        animal = make_tuple(x - 1, y, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 3){
        animal = make_tuple(x, y + 1, passos + 1, 0);
        return;
    }
    else if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 3){
        animal = make_tuple(x, y - 1, passos + 1, 0);
        return;
    }

    // se o animal está em uma área vazia (valor 0), ele pode permanecer nela por até 3 iterações
    if(matriz[x][y] == 0 && parado <= 2){
        animal = make_tuple(x, y, passos, parado + 1);
        return;
    }
    // se o animal já está parado há 3 iterações, ele deve se mover
    else if(matriz[x][y] == 0 && parado > 2){
        // O animal não conseguiu se mover após 3 iterações
        animal = make_tuple(x, y, passos, -1);
        return;
    }
    // para qualquer outro caso, o animal permanece onde está
    animal = make_tuple(x, y, passos, parado);
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
    
    return (x >= 0 && x < linhas && y >= 0 && y < colunas);
    
}

void apagarFogo(int x, int y, vector<vector<int>>& matriz, int lineSize, int columSize){
    matriz[x][y] = 0;
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 2){
        matriz[x + 1][y] = 1; // Apaga o fogo
    }
    if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 2){
        matriz[x - 1][y] = 1; // Apaga o fogo
    }
    if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 2){
        matriz[x][y + 1] = 1; // Apaga o fogo
    }
    if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 2){
        matriz[x][y - 1] = 1; // Apaga o fogo
    }
}