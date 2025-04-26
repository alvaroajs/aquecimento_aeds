#include "simulacao.hpp"


void simulacao(){
    int lineSize = 0, columSize = 0, fireStart_X = 0, fireStart_Y = 0;
    string linha;
    ifstream input =  abrirArquivo(); //funcao abrirArquivo() retorna um um ponteiro do tipo ifstream
    ifstream output = abrirSaida();
    bool stop;
    ostringstream oss;

    vector<tuple<int, int, int>> propag;

    tuple<int, int, int, int> animal; //posx, posy, passos, quantas vezes ta parado na mesma posição

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
        stop = interation(inicialMatrix, lineSize, columSize, fireStart_X, fireStart_Y, propag, k); 
        moverAnimal(animal, inicialMatrix, lineSize, columSize);
        escreverNoOutput(oss.str());
        showMatrix(inicialMatrix, lineSize, columSize, k);
        if(!stop){

            {
                if(get<3>(animal) != -1){

                    oss << "Animal sobreviveu, parou na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos.\n";    
                    escreverNoOutput(oss.str());
                    direcaoVento();
                }
                else{
                    oss << "Animal morreu na posição x: " << get<0>(animal) << " y: " << get<1>(animal) << " com " << get<2>(animal) << " passos.\n";
                    escreverNoOutput(oss.str());
                    direcaoVento();
                }
            }
            break;
        }

    }
    input.close();
    output.close();

    return;
}
bool interation(vector<vector<int>>& matriz, int linhas, int colunas, int fireStart_X, int fireStart_Y, vector<tuple<int, int, int>>& propag, int k) {
    vector<pair<int, int>> novasPropagacoes;

    // Adiciona a posição inicial do fogo à lista na primeira chamada
    if (k == 0) {
        propag.push_back(make_tuple(fireStart_X, fireStart_Y, 0));
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 2) {
                if (i > 0 && matriz[i - 1][j] == 1 && northWind) {
                    novasPropagacoes.push_back({i - 1, j});
                }
                if (i < linhas - 1 && matriz[i + 1][j] == 1 && southWind) {
                    novasPropagacoes.push_back({i + 1, j});
                }
                if (j > 0 && matriz[i][j - 1] == 1 && eastWind) {
                    novasPropagacoes.push_back({i, j - 1});
                }
                if (j < colunas - 1 && matriz[i][j + 1] == 1 && westWind) {
                    novasPropagacoes.push_back({i, j + 1});
                }
            }
        }
    }

    for (auto& pos : novasPropagacoes) {
        int x = pos.first;
        int y = pos.second;
        matriz[x][y] = 2;
        propag.push_back(make_tuple(x, y, 0));
    }

    
    for (auto it = propag.begin(); it != propag.end();) {
        int x = get<0>(*it);
        int y = get<1>(*it);
        int interacoes = get<2>(*it);

        if (interacoes >= 2) {
            matriz[x][y] = 3;
            it = propag.erase(it);
        } else {
            matriz[x][y] = 2;
            *it = make_tuple(x, y, interacoes + 1);
            ++it;
        }
    }

    if (k >= 1) {
        matriz[fireStart_X][fireStart_Y] = 3;
    }    
    return (!novasPropagacoes.empty() || !propag.empty());
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

void moverAnimal(tuple<int, int, int, int>& animal, vector<vector<int>>& matriz, int lineSize, int columSize) {
    int x = get<0>(animal);
    int y = get<1>(animal);
    int passos = get<2>(animal);
    int parado = get<3>(animal);
    
    if (parado == -1) return;
    
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    
    bool emPerigo = (matriz[x][y] == 2);
    
    // Função para verificar se animal pode se mover para uma célula com valor específico
    auto procurarCelula = [&](int valorCelula) -> bool {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (posicaoValida(nx, ny, lineSize, columSize) && matriz[nx][ny] == valorCelula) {
    
                if (valorCelula == 4) {
                    apagarFogo(nx, ny, matriz, lineSize, columSize);
                    matriz[nx][ny] = 0; // Transforma água em espaço vazio após uso
                }
                
                animal = make_tuple(nx, ny, passos + 1, 0);
                return true;
            }
        }
        return false;
    };
    
    // tenta encontrar células na ordem de prioridade
    if (procurarCelula(4)) return;      // prioridade 1: Água
    if (procurarCelula(1)) return;      // prioridade 2: Árvore saudável
    if (procurarCelula(0)) return;      // prioridade 3: Área vazia
    if (procurarCelula(3)) return;      // prioridade 4: Árvore queimada
    
    // Se chegou aqui, não conseguiu se mover
    if (emPerigo) {// segunda chance falhou - o animal morre
        // Segunda chance falhou - o animal morre
        animal = make_tuple(x, y, passos, -1);
    } 
    else if (matriz[x][y] == 0 && parado <= 2) {// pode permanecer em área vazia por até 3 iterações
        animal = make_tuple(x, y, passos, parado + 1);
    }
    else if (matriz[x][y] == 0 && parado > 2) { // animal não conseguiu se mover após 3 iterações
        animal = make_tuple(x, y, passos, -1);
    }
    else { // para qualquer outro caso, o animal permanece onde está
        animal = make_tuple(x, y, passos, parado);
    }
}
void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize, int k){
    escreverNoOutput("Interacao: " + to_string(k + 1) + "\n");
    for(int i = 0; i < lineSize; i++){
        for(int j = 0; j < columSize; j++){
            escreverNoOutput(to_string(matriz[i][j])); // escreve no arquivo de saída
            escreverNoOutput(" ");
        }
        escreverNoOutput("\n");
    }
    escreverNoOutput("\n");

}
bool posicaoValida(int x, int y, int linhas, int colunas) {
    return (x >= 0 && x < linhas && y >= 0 && y < colunas);
}

void apagarFogo(int x, int y, vector<vector<int>>& matriz, int lineSize, int columSize){
    matriz[x][y] = 0;
    if(posicaoValida(x + 1, y, lineSize, columSize) && matriz[x + 1][y] == 2){
        matriz[x + 1][y] = 1; 
    }
    if(posicaoValida(x - 1, y, lineSize, columSize) && matriz[x - 1][y] == 2){
        matriz[x - 1][y] = 1; 
    }
    if(posicaoValida(x, y + 1, lineSize, columSize) && matriz[x][y + 1] == 2){
        matriz[x][y + 1] = 1; 
    }
    if(posicaoValida(x, y - 1, lineSize, columSize) && matriz[x][y - 1] == 2){
        matriz[x][y - 1] = 1; 
    }
}

void direcaoVento(){
    if(southWind == true){
        escreverNoOutput("Vento Sul ativo\n");
    }
    if(northWind == true){
        escreverNoOutput("Vento Norte ativo\n");
    }
    if(eastWind == true){
        escreverNoOutput("Vento Leste ativo\n");
    }
    if(westWind == true){
        escreverNoOutput("Vento Oeste ativo\n");
    }
    return;
}