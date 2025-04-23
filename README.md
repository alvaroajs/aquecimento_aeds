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

3. **Prevenção de Loops Infinitos**:  
   - Garante que a simulação termine mesmo se o fogo não se extinguir naturalmente (ex: em uma floresta totalmente conectada por árvores saudáveis).  

### Como Modificar `K_MAX`  
Edite o arquivo `config.hpp` e altere o valor da constante:  
```cpp
const int K_MAX = 50;  // Altere para o número desejado
```


