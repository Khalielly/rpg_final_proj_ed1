# Sistema de Iniciativa — RPG (C++)

Este projeto implementa um sistema para jogos de RPG, permitindo que o usuário escolha o tipo de dado da sessão, crie personagens, realize rolagens de iniciativa e ordene a lista de combate utilizando diferentes algoritmos de ordenação, incluindo Merge Sort ou Quick Sort, conforme exigido na disciplina **Estrutura de Dados I — UFG**.

-----

## Estrutura de Arquivos

  * `src/`: Código fonte (`.cpp`).
  * `src/hpp/`: Arquivos de cabeçalho (`.hpp`).
  * `build/`: Arquivos objeto gerados durante a compilação.
  * `bin/`: Diretório reservado para binários.
  * `Makefile`: Script de compilação.

-----

## Funcionalidades

### Escolha do dado

O sistema permite definir um dado global para a sessão de jogo (d4, d6, d8, d10, d12 ou d20). Esta escolha impacta todas as rolagens de iniciativa subsequentes, garantindo consistência na partida.

### Criação de personagens

Permite adicionar personagens (Players ou NPCs) manualmente. O sistema gerencia:

  * **IDs únicos:** Incrementados automaticamente.
  * **Validação de Nível:** Garante valores entre 1 e 20.
  * **Tipagem:** Diferenciação entre Jogadores e NPCs.

### Rolagem de iniciativa

Calcula a iniciativa individual somando o resultado do dado base ao nível do personagem (`Resultado = 1dY + Nível`). Utiliza o algoritmo **Mersenne Twister** (`mt19937`) para geração de números aleatórios de alta qualidade e menor previsibilidade.

### Gerenciamento de Combate

O sistema controla o fluxo da batalha utilizando uma estrutura de fila circular:

  * **Controle de Turnos:** O personagem no topo da lista age e é movido para o final da fila.
  * **Contagem de Rodadas:** Monitora o fim de cada rodada (quando todos agiram) para permitir novas rolagens ou eventos.
  * **Reordenação Dinâmica:** Permite a inserção de novos combatentes durante a luta, mantendo a lista ordenada.

-----

## Estrutura de Dados e Algoritmos

### Lista Duplamente Encadeada

A base do projeto é uma classe `Lista` duplamente encadeada. Esta estrutura foi escolhida para permitir:

  * Remoção eficiente de personagens em qualquer posição (`remover(id)`).
  * Movimentação ágil de nós (início para fim) durante a rotação de turnos.
  * Iteração bidirecional (preparado para expansões futuras).

### Algoritmos de Ordenação

Conforme requisitos da disciplina, foram implementados dois métodos para organizar a iniciativa (da maior para a menor):

1.  **QuickSort:**

      * Utiliza a estratégia de "dividir para conquistar".
      * Implementado manipulando ponteiros da lista encadeada (sem arrays auxiliares).
      * *Complexidade média:* $O(n \log n)$.

2.  **MergeSort:**

      * Algoritmo estável que divide a lista recursivamente e funde as sublistas ordenadas.
      * Ideal para listas encadeadas, pois não requer acesso aleatório à memória.
      * *Critério de Desempate:* Em caso de valores iguais, o personagem com maior nível tem prioridade.

-----

## Como Compilar e Executar

O projeto utiliza um `Makefile` para automação do build. Certifique-se de ter o `g++` e o `make` instalados.

### Compilar

Para gerar o executável `rpg` na pasta raiz:

```bash
make
```

### Executar

Para iniciar o programa:

```bash
make run
# ou
./rpg
```

### Limpar

Para remover arquivos objeto (`.o`) e o executável:

```bash
make clean
```

-----

