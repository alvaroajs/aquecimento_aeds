#include "simulacao.hpp"


void simulacao(){
    int lineSize = 0, columSize = 0, fireStart_X = 0, fireStart_Y = 0;
    string linha;
    ifstream input =  abrirArquivo(); //funcao abrirArquivo() retorna um um ponteiro do tipo ifstream
    if (!input) { // verifica se o arquivo foi aberto corretamente
        cout << "Erro ao abrir o arquivo: " << "../input.dat" << endl;
        return;
    }
    input >> lineSize >> columSize; //leitura do tamanho da matriz
    input >> fireStart_X >> fireStart_Y; //leitura da posicao do animal
    getline(input, linha); // descarta o restante da linha
    
    vector<vector<int>> inicialMatrix = lerMatriz(input, lineSize, columSize); //leitura da matriz
    cout << K_MAX << endl; 
    
    
    //interation(inicialMatrix, lineSize, columSize, fireStart_X, fireStart_Y);
    if(posicaoValida(1, 5, lineSize, columSize)){
        cout << "Posicao valida" << endl;
    }else{
        cout << "Posicao invalida" << endl;
    }
    input.close();
}
void interation(vector<vector<int>>& matriz, int lineSize, int columSize, int fireStart_X, int fireStart_Y){    
    
    vector<vector<int>> auxMatrix = matriz;

    if(westWind == true){
        
        cout << "Entrou no westWind" << endl;

        for(int i = 0; i < lineSize; i++){
            for(int j = 0; j < columSize; j++){
                if(auxMatrix[i][j] == 2){
                    auxMatrix[i][j + 1] = 2;
                }
                
            }
            
        }

    }
    

    //showMatrix(auxMatrix, lineSize, columSize);

}

void showMatrix(vector<vector<int>>& matriz, int lineSize, int columSize){
    cout << "Matriz atualizada: " << endl;
    for(int i = 0; i < lineSize; i++){
        for(int j = 0; j < columSize; j++){
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }

}
bool posicaoValida(int x, int y, int linhas, int colunas) {
    return (x >= 0 && x < linhas && y >= 0 && y < colunas);
}



