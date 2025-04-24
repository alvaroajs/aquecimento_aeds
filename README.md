<div align="center">
  <h1>Aquecimento AEDS 1</h1>
  <h3>Simulação de Propagação de Incêndios</h3>
  <img src="img/incencioFlorestal.gif" width="350"/>
</div>

## Introdução  

A propagação de incêndios florestais é um fenômeno crítico, influenciado por fatores como densidade da vegetação, condições climáticas e interações dinâmicas com o ambiente. Este projeto tem como objetivo implementar um **simulador computacional** que modela a expansão do fogo em uma floresta representada por uma matriz, além de incorporar a movimentação inteligente de um animal em busca de rotas de fuga.  

### Descrição do Problema  

A floresta é modelada como uma **matriz dinâmica** de dimensões `N × M`, onde cada célula pode assumir um dos seguintes estados:  
- `0`: Área vazia (não inflamável, segura para o animal).  
- `1`: Árvore saudável (susceptível a pegar fogo).  
- `2`: Árvore em chamas (propaga fogo para vizinhas).  
- `3`: Árvore queimada (não propaga mais fogo).  
- `4`: Fonte de água (extingue fogo e protege áreas adjacentes).

## Objetivos e Desafios  

- **Propagação do Fogo**  
  - Implementar dois modos de propagação:  
    - **Sem vento**: Expansão linear para todas as direções ortogonais.  
    - **Com vento**: Direcionamento preferencial (configurável via `config.hpp`).  
  - Garantir que árvores em chamas (`2`) se tornem queimadas (`3`) após um ciclo.  

- **Movimentação do Animal**  
  - Priorizar movimentos para células seguras (`0`), água (`4`), ou evitar fogo (`2`).  
  - Oferecer "segunda chance" de movimento se o animal for atingido pelo fogo.  
  - Registrar trajetória, passos e eventos críticos (ex: morte do animal).  

- **Eficiência Computacional**  
  - Utilizar estruturas de dados otimizadas (e.g., `vector<vector<int>>` para a matriz).  
  - Garantir desempenho escalável para matrizes grandes (ex: `100x100`).

## 🖥️ Ambiente de Criação

O código foi desenvolvido utilizando as seguintes ferramentas:

[![Linguagem](https://img.shields.io/badge/Linguagem-C++-blue)](https://www.w3schools.com/cpp/)
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blueviolet)](https://code.visualstudio.com/docs/?dv=linux64_deb)
[![Sistema Operacional](https://img.shields.io/badge/ISO-Ubuntu%20Linux%2024.04%20LTS-red)](https://ubuntu.com/)

## ⚙️ Ambiente de Compilação

O projeto foi compilado utilizando a ferramenta abaixo:

[![Compilador](https://img.shields.io/badge/Ferramenta-Make-orange)](https://www.gnu.org/software/make/)

## 📁 Estrutura de Diretórios
## 📁 Estrutura de Diretórios

```text
📦 aquecimento_aeds
├── 📂 build                 # Arquivos temporários da compilação
├── 📂 data                  # Arquivos de entrada e saída
│   ├── input.dat           
│   └── output.dat.cpp      
├── 📂 img                   # GIFs e imagens do README
├── 📂 src                   # Código-fonte (.cpp e .h)
│   ├── main.cpp             # Arquivo principal
│   ├── simulacao.cpp        # Lógica da simulação
│   ├── simulacao.hpp        
│   ├── config.hpp           
│   ├── leitura_escrita.cpp  # Leitura e escrita
│   └── leitura_escrita.hpp  
├── 📄 Makefile              # Script de compilação
├── 📄 README.md             # Documentação do projeto
```

## Direções do Vento e numero de interações

A propagação do fogo é diretamente afetada pela configuração do vento no arquivo `config.hpp`. Cada direção corresponde a um movimento ortogonal específico na matriz, simulando como o vento "empurra" as chamas. Abaixo está a explicação detalhada de cada parâmetro:  

### 1. **`northWind` (Vento Norte)**  
- **Efeito**: Permite que o fogo se propague para **cima** (direção norte).  
- **Comportamento na Matriz**:  
  - Se uma célula em chamas `(i, j)` tem `northWind = true`, ela irá incendiar a célula acima: `(i-1, j)`.  
  - Exemplo:  
    ```cpp
    const bool northWind = true;  // Fogo se espalha para cima
    ```  
- **Cenário Típico**: Simula um vento soprando **do sul para o norte**, acelerando a propagação em direção ao topo da matriz.  

---

### 2. **`eastWind` (Vento Leste)**  
- **Efeito**: Permite que o fogo se propague para a **direita** (direção leste).  
- **Comportamento na Matriz**:  
  - Se uma célula em chamas `(i, j)` tem `eastWind = true`, ela irá incendiar a célula à direita: `(i, j+1)`.  
  - Exemplo:  
    ```cpp
    const bool eastWind = true;   // Fogo se espalha para direita
    ```  
- **Cenário Típico**: Simula um vento soprando **do oeste para o leste**, comum em regiões costeiras.  

---

### 3. **`southWind` (Vento Sul)**  
- **Efeito**: Permite que o fogo se propague para **baixo** (direção sul).  
- **Comportamento na Matriz**:  
  - Se uma célula em chamas `(i, j)` tem `southWind = true`, ela irá incendiar a célula abaixo: `(i+1, j)`.  
  - Exemplo:  
    ```cpp
    const bool southWind = true;  // Fogo se espalha para baixo
    ```  
- **Cenário Típico**: Simula um vento soprando **do norte para o sul**, comum em áreas montanhosas.  

---

### 4. **`westWind` (Vento Oeste)**  
- **Efeito**: Permite que o fogo se propague para a **esquerda** (direção oeste).  
- **Comportamento na Matriz**:  
  - Se uma célula em chamas `(i, j)` tem `westWind = true`, ela irá incendiar a célula à esquerda: `(i, j-1)`.  
  - Exemplo:  
    ```cpp
    const bool westWind = true;   // Fogo se espalha para esquerda
    ```  
- **Cenário Típico**: Simula um vento soprando **do leste para o oeste**, típico em zonas de alta pressão.  

---

### Combinações de Vento  
- **Vento Omnidirecional** (padrão):  
  ```cpp
  const bool northWind = true;
  const bool eastWind = true;
  const bool southWind = true;
  const bool westWind = true;
  ```

### Controle de Iterações: A Constante `K_MAX`  

Assim como a configuração do vento, a constante **`K_MAX`**, definida no arquivo `config.hpp`, determina o **número máximo de iterações** que a simulação pode executar. Esse parâmetro é essencial para garantir que a simulação não entre em loop infinito e para comparar desempenho em diferentes cenários.  

### Funcionalidade da `K_MAX`  
- **Limite de Ciclos**:  
  - A simulação é interrompida automaticamente após `K_MAX` iterações, mesmo que ainda haja células em chamas.  
  - Exemplo: Se `K_MAX = 25`, o programa executará no máximo 25 ciclos de propagação e movimentação do animal.  

- **Uso no Código**:  
  - O loop principal da simulação (`simulacao.cpp`) utiliza `K_MAX` como condição de parada:  
    ```cpp
    for(int k = 0; k < K_MAX; k++) {
        // Executa propagação e movimentação
    }
    ```  

### Por Que Ajustar `K_MAX`?  
1. **Cenários de Curto Prazo**:  
   - Valores menores (ex: `K_MAX = 10`) são úteis para simular incêndios rápidos ou testar comportamentos iniciais do animal.  

2. **Cenários de Longo Prazo**:  
   - Valores maiores (ex: `K_MAX = 100`) permitem analisar padrões de propagação em florestas extensas ou avaliar a eficiência do algoritmo em matrizes grandes.  


### Como Modificar `K_MAX`  
Edite o arquivo `config.hpp` e altere o valor da constante:  
```cpp
const int K_MAX = 50;  // Altere para o número desejado
```

## Principais Funções do Código  

Para organizar a explicação das funções, comece pela **função principal** que coordena a simulação e depois detalhe as subfunções. Segue uma sugestão de estrutura:

---

### **`simulacao()`** (`simulacao.cpp`)  
**Propósito**: Função principal que gerencia o fluxo completo da simulação.  
**Funcionalidades**:  
- Lê o arquivo `input.dat` para obter a matriz inicial e parâmetros.  
- Inicializa a posição do animal (via `setPosAnimal()`).  
- Executa o loop principal por `K_MAX` iterações.  
- Chama `interation()` para propagar o fogo e `moverAnimal()` para atualizar a posição do animal.  
- Exibe a matriz atualizada a cada iteração (via `showMatrix()`).  
- Grava resultados no `output.dat`.  

**Codigo**:  
```cpp
void simulacao(){
    int lineSize = 0, columSize = 0, fireStart_X = 0, fireStart_Y = 0;
    string linha;
    ifstream input =  abrirArquivo(); //funcao abrirArquivo() retorna um um ponteiro do tipo ifstream
    ifstream output = abrirSaida();
    bool stop;

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
        cout << "\nInteracao: " << k + 1 << endl;
        stop = interation(inicialMatrix, lineSize, columSize, fireStart_X, fireStart_Y, propag, k); 
        moverAnimal(animal, inicialMatrix, lineSize, columSize);
        showMatrix(inicialMatrix, lineSize, columSize, k);
        if(!stop){
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
    output.close();

    return;
}
```
---
### Módulo de Leitura/Escrita (`leitura_escrita.cpp` e `leitura_escrita.hpp`)

### Funções Principais:


#### **`abrirArquivo()`**  
**Propósito**: Abre o arquivo de entrada `input.dat` para leitura.  
**Funcionalidades**:  
- Define o caminho do arquivo como `data/input.dat`.  
- Retorna um objeto `ifstream` para operações de leitura.  
- **Validação**: Se o arquivo não existir ou não puder ser aberto, o erro é tratado posteriormente em `simulacao()`.
- Define o caminho do arquivo de saída `output.dat`.
- Escreve no arquivo de saída.

**Código**:  
```cpp
#include "leitura_escrita.hpp"

ifstream abrirArquivo() {
    ifstream input("data/input.dat");   
    return input;

}
ifstream abrirSaida() {
    const string caminho = "data/output.dat";

    
    ofstream limpaArquivo(caminho); 
    limpaArquivo.close();

    ifstream output(caminho);
    return output;
}

vector<vector<int>> lerMatriz(ifstream &input, int lineSize, int columSize) {
    
    vector<vector<int>> matriz(lineSize, vector<int>(columSize)); 
    for (int i = 0; i < lineSize; i++) {
        for (int j = 0; j < columSize; j++) {
            input >> matriz[i][j];
        }
    }    
    return matriz;
}

void escreverNoOutput(string mensagem) {
    ofstream output("data/output.dat", ios::app);
    if (output.is_open()) {
        output << mensagem;
        output.close();
    } else {
        cout << "Erro ao abrir o arquivo de saída." << endl;
    }
}
```
---
# 🧪 Casos de Teste

Temos aqui um exemplo de uma matriz 5x5, a primeira linha é referente aos dados da matriz, sendo os dois primeiros números as dimensões linhas e colunas, respectivamente, já os dois últimos numéros as cordenadas do ínicio do íncendio, para esse teste temos o fogo se propagando para todas as direções ortogonais

### Arquivo de Entrada (`input.dat`)  
```plaintext
5 5 1 1       // [N=5] [M=5] [Fogo inicia em (X=1, Y=1)]
1 1 1 1 4     // Linha 0: [1][1][1][1][4]
1 2 1 1 1     // Linha 1: [1][🔥][1][1][1]
1 1 1 1 4     // Linha 2: [1][1][1][1][4]
0 0 1 1 1     // Linha 3: [🟢][🟢][1][1][1]
1 4 1 0 4     // Linha 4: [1][💧][1][🟢][💧]

``` 

# 🔥 Análise Detalhada por Iteração  

## **Iteração 1**  
### **Estado da Matriz**:  
``` plaintext
1 2 1 1 4
2 2 2 1 1
1 2 1 1 4
0 0 1 1 1
1 4 1 0 0
```
- **Propagação do Fogo**:  
  - Fogo iniciou em `(1,1)` e se propagou para as 4 direções: `(0,1)`, `(2,1)`, `(1,0)`, `(1,2)`.  
  - Célula `(1,1)` virou queimada (`3` → não aparece devido a erro no log).  

- **Movimento do Animal**:  
  - Encontrou água em `(4,3)` (linha 4, coluna 3), apagando fogo adjacente.  
  - Nova posição: `(4,4)` (passos: 1).  


## **Iteração 2**  
### **Estado da Matriz**:  
``` plaintext
2 2 2 1 4
2 2 2 2 1
2 2 2 1 4
0 0 1 1 1
1 4 1 0 0
```
- **Propagação do Fogo**:  
  - Novos focos em `(0,1)`, `(1,0)`, `(1,2)`, `(2,1)` queimam vizinhos.  
  - Exemplo: `(1,2)` incendeia `(1,3)`.  

- **Movimento do Animal**:  
  - Moveu-se para `(3,4)` (passos: 2).  



## **Iteração 3**  
### **Estado da Matriz**: 
``` plaintext
2 2 2 2 4
2 2 2 2 1
2 2 2 1 0
0 0 2 1 1
1 4 1 0 0
```
 **Evento Crítico**:  
  - Animal encontrou água em `(3,4)` (linha 3, coluna 4), convertendo-a para `0` e apagando adjacentes.  

- **Movimento do Animal**:  
  - Nova posição: `(2,4)` (passos: 3).  

## **Iteração 4**  
### **Estado da Matriz**:  
```plaintext
2 2 2 2 4
2 2 2 2 2
2 2 2 2 0
0 0 2 2 1
1 4 2 0 0
```

- **Propagação do Fogo**:  
  - Fogo atinge células inferiores (ex: `(4,2)`).  

- **Movimento do Animal**:  
  - Retorna para `(3,4)` (passos: 4), possivelmente devido a bloqueio por fogo.  

## **Iteração 5**  
### **Estado da Matriz**: 
```plaintext
2 2 2 2 4
2 2 2 2 2
2 2 2 2 0
0 0 2 2 2
1 4 2 0 0
```
- **Propagação do Fogo**:  
  - Fogo domina a região central. Células `(3,2)`, `(3,3)` e `(4,2)` queimam.  

- **Movimento do Animal**:  
  - Move-se para `(4,4)` (passos: 5), área segura (`0`).  

## **Iteração 6**  
### **Estado da Matriz**:  
```plaintext
2 2 2 2 4
2 2 2 2 2
2 2 2 2 0
0 0 2 2 2
1 4 2 0 0
```
- **Estagnação**:  
  - Matriz mantém-se inalterada (fogo não avança mais).  

- **Movimento do Animal**:  
  - Última posição: `(4,3)` (passos: 6), permanecendo em área segura (`0`).  

## **Conclusão da Simulação**  
- **Animal sobreviveu!**  
  - **Passos totais**: 6.  
  - **Água encontrada**: 2 vezes (Iterações 1 e 3).  
  - **Posição final**: `(4,3)`.  


