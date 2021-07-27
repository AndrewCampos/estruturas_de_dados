#include <stdio.h>
#include <stdlib.h>

#define POPULAR -1
#define FALSE 0
#define TRUE 1

/**
 * Possíveis operações na lista
 */
enum Operacoes {Sair, RemoverPorIndice, RemoverPorValor, InsereFim, InsereNoIndice, Imprime};

/**
 * Tipo definido para o item da lista
 */
typedef struct Item {
    int valor;
    struct Item *proximo;
    // Demais atributos do item da lista
} Item;

/**
 * Tipo definido pra raiz da lista
 */
typedef struct Lista {
    struct Item *inicio;
    int tamanho;
} Lista;

/**
 * Inicializa a lista como vazia
 * @param l Lista
 */
void inicializaLista(Lista *l) {
    l->inicio = NULL;
    l->tamanho = 0;
}

/**
 * Cria novo item a ser inserido
 * @param valor Valor do novo item
 * @return Novo item criado
 */
Item* criaNovo(int valor) {
    Item *novo = (Item*)malloc(sizeof(Item));
    novo->valor = valor;
    novo->proximo = NULL;
    return novo;
}

/**
 * Insere novo item na posição indicada da lista
 * @param l Lista
 * @param valor Valor a ser inserido
 * @param pos Posição a se inserir novo item
 * @return 1 caso sucesso, 0 caso falha
 */
int insereLista(Lista *l, int valor, int pos) {
    int loc=0;
    Item *aux,*novo;

    if (pos > l->tamanho) {
        printf( "Erro! Índice fora do alcance da lista\n");
        return FALSE;
    }
    aux = l->inicio;
    novo = criaNovo(valor);

    if (l->tamanho == 0) { // caso a lista esteja via
        l->inicio = novo;
        l->tamanho++;
        return TRUE;

    } else if (pos == POPULAR) { // caso apenas queira popular, insere no fim da lista
        while(aux->proximo != NULL) aux = aux->proximo; // encontra o fim da lista
        aux->proximo = novo;
        l->tamanho++;
        return TRUE;

    } else {
        if(pos == 0){
            novo->proximo = l->inicio;
            l->inicio = novo;
            l->tamanho++;
            return TRUE;
        }

        while (loc<pos-1) {
            aux = aux->proximo;
            loc++;   
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        l->tamanho++;
    }

    return TRUE;
}

/**
 * Imprime toda a lista
 * @param l Lista
 */
void imprimeLista(Lista *l) {
    int i;
    Item *aux;
    aux = l->inicio;

    for (i=0;i<l->tamanho;i++) {
        printf("%d -> ", aux->valor);
        aux = aux->proximo;
    }

    printf("null\n");
}

/**
 * Remove item indicado pelo indice da lista
 * @param l Lista
 * @param loc Indice do item a ser removido
 * @return Item removido
 */
Item* removeInd(Lista *l, int loc){
    Item *aux,*ret;
    int i;
    aux = l->inicio;

    if (loc >= l->tamanho) {
        printf("Erro! Índice fora do alcance da lista\n");
        return NULL;
    }

    if (loc == 0) { // caso o item a ser removido sej o primeiro
        l->inicio = aux->proximo;
        l->tamanho--;
        return aux;
    }

    for (i=1;i<loc;i++){ // encontra item anterior ao que vai ser removido
        aux = aux->proximo;
    } 

    ret = aux->proximo;
    aux->proximo = aux->proximo->proximo;
    l->tamanho--;
    return ret;
}

/**
 * Remove primeira ocorrencia do item indicado
 * @param l Lista
 * @param val Valor da chave do item a ser removido
 * @return Item removido
 */
Item* removeVal(Lista *l, int val){
    Item *aux,*ret;
    int i;
    aux = l->inicio;

    if (l->tamanho == 0) { // caso a lista esteja via
        printf("Erro! Lista via.\n");
        return NULL;
    }

    if (aux->valor == val) { // caso o item removido seja o primeiro
        l->inicio = aux->proximo;
        l->tamanho--;
        return aux;
    }

    while (aux->proximo != NULL) {
        if(aux->proximo->valor == val) break;
        aux = aux->proximo;
    }

    if (aux->proximo == NULL) {
        printf("Erro! Item não encontrado.\n");
        return NULL;
    }
    
    ret = aux->proximo;
    aux->proximo = aux->proximo->proximo;
    l->tamanho--;
    return ret;
}

int main() {
    Lista lista;
    Item *rm;
    int i, in, item, continuar=TRUE;

    printf("\nCÓDIGO EXEMPLO: LISTA ENCADEADA\n");
    inicializaLista(&lista);
    printf("Insira o tamanho inicial da lista: ");
    scanf("%d",&in);
    printf("Insira os itens da lista: ");

    for (i=0;i<in;i++) {
        scanf("%d", &item);
        if (insereLista(&lista,item,POPULAR) == FALSE) {
            printf( "Erro ao inserir item!\n" );
        }
    }

    printf( "\nLista gerada: ");
    imprimeLista(&lista);
    printf( "Tamanho: %d\n",lista.tamanho);

    while (continuar) {
        printf( "\nInsira a operação desejada\n"
                     "  0 - Sair\n"
                     "  1 - Remoção por índice\n"
                     "  2 - Remoção por valor\n"
                     "  3 - Inserção no fim\n"
                     "  4 - Inserção por índice\n"
                     "  5 - Impressão da lista\n>> " );
        scanf("%d",&in);

        switch (in) {
            case Sair:
                continuar = FALSE;
                break;

            case RemoverPorIndice:
                printf("\nRemoção por índice!\n"
                        "Insira o indice do elemento a ser removido: " );
                scanf("%d",&in);
                rm = removeInd(&lista,in);

                if (rm == NULL) {
                    printf( "Impossível remover item!\n" );
                } else {
                    printf( "Elemento removido: "  "%d\n" ,rm->valor);
                }
                break;

            case RemoverPorValor:
                printf("\nRemoção por valor!\n"
                        "Insira o valor do elemento a ser removido: " );
                scanf("%d",&in);
                rm = removeVal(&lista,in);

                if (rm == NULL) {
                    printf( "Impossível remover item!\n" );
                } else {
                    printf( "Elemento removido: "  "%d\n" ,rm->valor);
                }
                break;

            case InsereFim:
                printf("\nInsrerção no fim!\n"
                        "Insira o valor do elemento a ser inserido: " );
                scanf("%d",&item);

                if (insereLista(&lista,item,POPULAR)) {
                    printf( "Elemento inserido com sucesso\n\n");
                } else {
                    printf( "Impossível inserir item!\n" );
                }
                break;

            case InsereNoIndice:
                printf("\nInsrerção no fim!\n"
                        "Insira o valor do elemento a ser inserido: " );
                scanf("%d",&item);
                printf( "Insira o índice do elemento: " );
                scanf("%d",&in);

                if (insereLista(&lista,item,in)) {
                    printf("Elemento inserido com sucesso\n");
                } else {
                    printf("Impossível inserir item!\n" );
                }
                break;

            case Imprime:
                printf("Lista atual:\n");
                imprimeLista(&lista);
                break;

            default:
                printf("Erro! Operação inválida. [%d]\n",in);
                break;
        }
    }

    printf("\nLista após alterações: ");
    imprimeLista(&lista);
    printf("Novo tamanho: %d\n",lista.tamanho);
    printf("Fim da execução!\n\n" );
    return 0;
}