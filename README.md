# Torre de Hanói com Pilha Dinâmica Encadeada

Este projeto implementa o clássico jogo **Torre de Hanói** utilizando uma **Pilha Dinâmica Encadeada (LIFO)** construída em linguagem C sem o uso de bibliotecas de estruturas de dados prontas.

## Estrutura de Dados e Operações da Pilha

A estrutura baseia-se em nós encadeados dinamicamente:

* **`No`**: Armazena o valor correspondente ao tamanho do `disco` e o ponteiro `proximo`.
* **`Pilha`**: Armazena a referência para o nó no `topo` e o inteiro `quantidade`.

```text
[Pilha] -> Topo -> [ Disco 1 ] -> [ Disco 2 ] -> [ Disco 3 ] -> [ Disco 4 ] -> NULL
```

### Operações Implementadas

1. **`inicializar_pilha`**: Aloca e retorna uma nova pilha com topo `NULL` e quantidade `0`.
2. **`empilhar`** ($O(1)$): Adiciona um novo nó contendo o disco no topo da pilha.
3. **`desempilhar`** ($O(1)$): Remove e retorna o disco do topo da pilha, liberando sua memória.
4. **`topo`** ($O(1)$): Consulta o valor do disco no topo sem removê-lo.
5. **`imprimir`**: Exibe visualmente a pilha da posição do topo até a base.

---

## Instruções de Compilação e Execução

### Compilação
No terminal, execute:

```bash
gcc -std=c99 main.c -o hanoi
```

### Execução
* **Linux / macOS:**
  ```bash
  ./hanoi
  ```
* **Windows (PowerShell / CMD):**
  ```bash
  .\hanoi.exe
  ```

---

## Exemplo de Execução do Jogo

```text
==================== ESTADO DAS TORRES ====================
Torre 1 (A): [Topo] [1] [2] [3] [4] 
Torre 2 (B): (vazia)
Torre 3 (C): (vazia)
Movimentos realizados: 0
===========================================================

[SUCESSO] Moveu o disco 1 da Torre A para a Torre C.

==================== ESTADO DAS TORRES ====================
Torre 1 (A): [Topo] [2] [3] [4] 
Torre 2 (B): (vazia)
Torre 3 (C): [Topo] [1] 
Movimentos realizados: 1
===========================================================
```

---

## Bateria de Testes e Resultados

A aplicação conta com uma suíte automatizada de testes que valida as regras de negócio e o comportamento da pilha LIFO:

| Caso de Teste | Operação Avaliada | Resultado Esperado | Resultado |
| :--- | :--- | :--- | :---: |
| **Pilha LIFO** | `empilhar` (10, 20) $\rightarrow$ `desempilhar` | Retorna o elemento 20 (último inserido) | **APROVADO** |
| **Origem Vazia** | Mover de torre sem discos | Operação rejeitada com mensagem de erro | **APROVADO** |
| **Regra de Tamanho** | Colocar disco maior sobre menor | Operação negada e estado mantido | **APROVADO** |
| **Contagem** | Movimento válido | Incrementa a quantidade de movimentos | **APROVADO** |
| **Condição de Vitória**| Mover 4 discos para a Torre C | Identifica finalização da partida | **APROVADO** |
