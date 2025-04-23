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

- **Propagação Dinâmica do Fogo**  
  - Implementar dois modos de propagação:  
    - **Sem vento**: Expansão linear para todas as direções ortogonais.  
    - **Com vento**: Direcionamento preferencial (configurável via `config.hpp`).  
  - Garantir que árvores em chamas (`2`) se tornem queimadas (`3`) após um ciclo.  

- **Inteligência do Animal**  
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
