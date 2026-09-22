#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int disco;           // Tamanho do disco (ex: 1, 2, 3, 4)
    struct No *proximo;
} No;

typedef struct {
    No *topo;
    int quantidade;
} Pilha;

//  OPERAÇÕES OBRIGATÓRIAS DA PILHA (LIFO)


Pilha* inicializar_pilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
        p->quantidade = 0;
    }
    return p;
}

int empilhar(Pilha *p, int disco) {
    if (p == NULL) return 0;
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) return 0; // Falha na alocação

    novo->disco = disco;
    novo->proximo = p->topo;
    p->topo = novo;
    p->quantidade++;
    return 1;
}

int desempilhar(Pilha *p) {
    if (p == NULL || p->topo == NULL) {
        return -1; // Pilha vazia
    }
    No *temp = p->topo;
    int disco_removido = temp->disco;

    p->topo = temp->proximo;
    free(temp);
    p->quantidade--;

    return disco_removido;
}

int topo(Pilha *p) {
    if (p == NULL || p->topo == NULL) {
        return -1; // Pilha vazia
    }
    return p->topo->disco;
}

void imprimir(Pilha *p) {
    if (p == NULL || p->topo == NULL) {
        printf("(vazia)");
        return;
    }

    // Como o topo é impresso primeiro na pilha, vamos exibir do topo para a base
    No *atual = p->topo;
    printf("[Topo] ");
    while (atual != NULL) {
        printf("[%d] ", atual->disco);
        atual = atual->proximo;
    }
}

void liberar_pilha(Pilha *p) {
    if (p == NULL) return;
    while (p->topo != NULL) {
        desempilhar(p);
    }
    free(p);
}

//  LÓGICA DO JOGO TORRE DE HANÓI (4 DISCOS)

#define NUM_DISCOS 4

typedef struct {
    Pilha *torres[3]; // Torres 0, 1 e 2 (A, B e C)
    int movimentos;
} JogoHanoi;

JogoHanoi* inicializar_jogo() {
    JogoHanoi *jogo = (JogoHanoi*) malloc(sizeof(JogoHanoi));
    for (int i = 0; i < 3; i++) {
        jogo->torres[i] = inicializar_pilha();
    }
    jogo->movimentos = 0;

    // Coloca os 4 discos na Torre 0 (do maior para o menor: 4, 3, 2, 1)
    for (int d = NUM_DISCOS; d >= 1; d--) {
        empilhar(jogo->torres[0], d);
    }

    return jogo;
}

void desenhar_torres(JogoHanoi *jogo) {
    printf("\n==================== ESTADO DAS TORRES ====================\n");
    for (int i = 0; i < 3; i++) {
        printf("Torre %d (%c): ", i + 1, 'A' + i);
        imprimir(jogo->torres[i]);
        printf("\n");
    }
    printf("Movimentos realizados: %d\n", jogo->movimentos);
    printf("===========================================================\n");
}

int mover_disco(JogoHanoi *jogo, int orig, int dest) {
    // Validação dos índices das torres (0, 1 ou 2)
    if (orig < 0 || orig > 2 || dest < 0 || dest > 2) {
        printf("\n[ERRO] Torre de origem ou destino invalida!\n");
        return 0;
    }

    if (orig == dest) {
        printf("\n[ERRO] A torre de origem e destino devem ser diferentes!\n");
        return 0;
    }

    Pilha *p_orig = jogo->torres[orig];
    Pilha *p_dest = jogo->torres[dest];

    // Regra 1: Não pode retirar de uma torre vazia
    if (p_orig->topo == NULL) {
        printf("\n[MOVIMENTO INVALIDO] A torre de origem %d (%c) esta vazia!\n", orig + 1, 'A' + orig);
        return 0;
    }

    int disco_mover = topo(p_orig);
    int disco_destino = topo(p_dest);

    // Regra 2: Disco maior não pode ficar sobre disco menor
    if (p_dest->topo != NULL && disco_mover > disco_destino) {
        printf("\n[MOVIMENTO INVALIDO] Nao e permitido colocar um disco maior (%d) sobre um menor (%d)!\n",
               disco_mover, disco_destino);
        return 0;
    }

    // Movimento Válido
    desempilhar(p_orig);
    empilhar(p_dest, disco_mover);
    jogo->movimentos++;
    printf("\n[SUCESSO] Movel o disco %d da Torre %c para a Torre %c.\n", disco_mover, 'A' + orig, 'A' + dest);
    return 1;
}

int verificar_vitoria(JogoHanoi *jogo) {
    // A vitória ocorre quando a Torre 3 (índice 2) possui todos os 4 discos
    return (jogo->torres[2]->quantidade == NUM_DISCOS);
}

void liberar_jogo(JogoHanoi *jogo) {
    for (int i = 0; i < 3; i++) {
        liberar_pilha(jogo->torres[i]);
    }
    free(jogo);
}

// BATERIA DE TESTES AUTOMATIZADOS

void executar_testes() {
    printf("\n====================================================\n");
    printf("     INICIANDO SUÍTE DE TESTES DA PILHA/HANÓI       \n");
    printf("====================================================\n\n");

    // Teste 1: Operações de Pilha (LIFO)
    Pilha *p = inicializar_pilha();
    printf("[Teste 1] Pilha Inicializada. Quantidade: %d (Esperado: 0)\n", p->quantidade);

    empilhar(p, 10);
    empilhar(p, 20);
    printf("[Teste 2] Empilhou 10 e 20. Topo atual: %d (Esperado: 20)\n", topo(p));

    int removido = desempilhar(p);
    printf("[Teste 3] Desempilhou elemento LIFO: %d (Esperado: 20)\n", removido);
    printf("[Teste 4] Topo apos desempilhar: %d (Esperado: 10)\n", topo(p));
    liberar_pilha(p);

    // Teste 2: Regras do Jogo
    JogoHanoi *jogo = inicializar_jogo();
    printf("\n[Teste 5] Tentativa de mover de torre vazia (Torre B -> Torre C):\n");
    mover_disco(jogo, 1, 2); // Deve falhar

    printf("\n[Teste 6] Movimento valido (Torre A -> Torre B):\n");
    mover_disco(jogo, 0, 1); // Move disco 1 para Torre B

    printf("\n[Teste 7] Tentativa de colocar disco maior sobre menor (Torre A [disco 2] -> Torre B [disco 1]):\n");
    mover_disco(jogo, 0, 1); // Deve falhar pela regra de tamanhos

    liberar_jogo(jogo);

}

// INTERFACE DE JOGO E MENU


void jogar_partida() {
    JogoHanoi *jogo = inicializar_jogo();
    int opcao = -1;

    while (1) {
        desenhar_torres(jogo);

        if (verificar_vitoria(jogo)) {
            printf("\n PARABÉNS! VOCÊ VENCEU O JOGO EM %d MOVIMENTOS! \n\n", jogo->movimentos);
            break;
        }

        printf("\nOpcoes:\n");
        printf("1. Realizar movimento\n");
        printf("2. Reiniciar partida\n");
        printf("0. Voltar ao menu principal / Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 0) {
            break;
        } else if (opcao == 2) {
            liberar_jogo(jogo);
            jogo = inicializar_jogo();
            printf("\n--- Partida Reiniciada! ---\n");
        } else if (opcao == 1) {
            int orig, dest;
            printf("Informe a Torre de ORIGEM (1, 2 ou 3): ");
            scanf("%d", &orig);
            printf("Informe a Torre de DESTINO (1, 2 ou 3): ");
            scanf("%d", &dest);

            mover_disco(jogo, orig - 1, dest - 1);
        } else {
            printf("\nOpcao invalida!\n");
        }
    }

    liberar_jogo(jogo);
}

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n================ JOGO TORRE DE HANÓI ================\n");
        printf("1. Iniciar Nova Partida\n");
        printf("2. Executar Testes Automatizados\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogar_partida();
                break;
            case 2:
                executar_testes();
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return 0;
}
