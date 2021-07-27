#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

/**
 * Possíveis operações na pilha
 */
enum Operacoes {Sair, Pop, Push, Imprimir};

/**
 * Tipo definido para o item da pilha
 */
typedef struct Item {
    struct Item *proximo; // Item seguinte da pilha
    int chave; // Valor referente ao item
    // Demais atributos do item da pilha
} Item;

/**
 * Tipo definido para o topo da pilha
 */
typedef struct Pilha{
    struct Item *topo; // Item do topo da pilha
    int tamanho; // Tamanho da pilha
} Pilha;

/**
 * Inicializa a pilha como vazia
 * @param p Pilha
 */
void inicializaPilha(Pilha *p) {
    p->tamanho = 0;
    p->topo = NULL;
}

/**
 * Cria novo item a ser inserido na pilha
 * @param chave Valor da chave do novo item
 * @return Novo item de pilha criado
 */
Item* novoItem(int chave) {
    Item *novo = (Item*)malloc(sizeof(Item));
    novo->chave = chave;
    novo->proximo = NULL;
    return novo;
}

/**
 * Insere novo item no topo da pilha
 * @param p Pilha
 * @param chave Valor da chave do item a ser inserido
 */
void push(Pilha *p, int chave) {
    Item *novo, *aux;
    novo = novoItem(chave);
    p->tamanho++;
    
    if (p->topo == NULL) {
        p->topo = novo;
        return;
    }

    aux = p->topo;
    p->topo = novo;
    novo->proximo = aux;
}

/**
 * Remove item do todo da pilha
 * @param p Pilha
 * @return Item removido
 */
Item* pop(Pilha *p) {
    Item *ret;

    if (p->topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }

    ret = p->topo;
    p->topo = ret->proximo;
    return ret;
}

/**
 * Imprime valores presentes na pilha
 * @param p Pilha
 */
void imprimePilha(Pilha *p) {
    Item *item = p->topo;

    printf("Tamanho da pilha: %d\nTopo", p->tamanho);

    while (item != NULL) {
        printf(" -> %d", item->chave);
        item = item->proximo;
    }
    printf("\n");
}

int main() {
    Pilha pilha;
    Item *removido;
    int qtdItens, i, novaChave, operacao, continuar = TRUE;

    inicializaPilha(&pilha);
    printf("Insira o tamanho inicial da pilha: ");
    scanf("%d", &qtdItens);

    if (qtdItens < 0) {
        printf("Erro! Valor fornecido inválido.\n");
        return 0;
    }

    for (i=0; i<qtdItens; i++) {
        scanf("%d", &novaChave);
        push(&pilha, novaChave);
    }

    printf("\nPilha gerada:\n");
    imprimePilha(&pilha);

    while (continuar) {
        printf("\nInsira a operação desejada\n"
                "  0 - Sair\n"
                "  1 - Pop\n"
                "  2 - Push\n"
                "  3 - Imprimir pilha\n>> ");
        scanf("%d", &operacao);

        switch (operacao) {
            case Sair:
                continuar = FALSE;
                break;
            
            case Pop:
                removido = pop(&pilha);
                if (removido != NULL) {
                    printf("Removido item de chave \"%d\"!\n", removido->chave);
                }
                break;

            case Push:
                printf("Insira o item a ser adicionado: ");
                scanf("%d", &novaChave);
                push(&pilha, novaChave);
                printf("Item inserido com sucesso!\n");
                break;

            case Imprimir:
                imprimePilha(&pilha);
                break;

            default:
                printf("Erro! Operação \"%d\" inválida!\n", operacao);
                break;
        }
    }

    printf("\nPilha após alterações:\n");
    imprimePilha(&pilha);
    printf("Fim da execução!\n");
    return 0;
}
