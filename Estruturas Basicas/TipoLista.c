#include <stdio.h>
#include <stdlib.h>
#include "../constantes.h"
#define POPULAR -1

/* Tipos para operação */
//enum OP{Sair, RmInd, RmVal, InsFim, InsInd};

/* Tipo definido para o item da lista */
typedef struct Item{
    int valor;
    struct Item *prox;
    // Demais parâmetros do item da lista
} Item;

/* Tipo definido pra raiz da lista */
typedef struct Lista{
    struct Item *inicio;
    int tam;
} Lista;

/* Inicializa a lista como vazia */
void _init_Lista(Lista *l){
    l->inicio = NULL;
    l->tam = 0;
}

/* Cria novo item a ser inserido */
Item* criaNovo(int val){
    Item *novo = (Item*)malloc(sizeof(Item));
    novo->valor = val;
    novo->prox = NULL;
    return novo;
}

/* Insere novo item na posição indiacda da lista */
int insereLista(Lista *l, int val, int pos){
    int loc=0;
    Item *aux,*novo;

    if(pos > l->tam){
        printf(N_VERM "Erro! " RESET "Índice fora do alcance da lista\n");
        return FALSE;
    }
    novo = (Item*)malloc(sizeof(Item));
    aux = (Item*)malloc(sizeof(Item));
    aux = l->inicio;
    novo = criaNovo(val);

    if(l->tam == 0){ // caso a lista esteja vazia
        l->inicio = novo;
        l->tam++;
        return TRUE;

    }else if (pos == POPULAR){ // caso apenas queira popular, insere no fim da lista
        while(aux->prox != NULL) aux = aux->prox; // encontra o fim da lista
        aux->prox = novo;
        l->tam++;
        return TRUE;

    }else{
        if(pos == 0){
            novo->prox = l->inicio;
            l->inicio = novo;
            l->tam++;
            return TRUE;
        }

        while(loc<pos-1){
            aux = aux->prox;
            loc++;   
        }
        novo->prox = aux->prox;
        aux->prox = novo;
        l->tam++;
    }

    return TRUE;
}

/* Imprime toda a lista */
void imprimeLista(Lista *l){
    int i;
    Item *aux;
    aux = malloc(sizeof(Item));
    aux = l->inicio;
    for(i=0;i<l->tam;i++){
        printf(VERD "%d -> ", aux->valor);
        aux = aux->prox;
    }
    printf("null\n" RESET);
}

/* Remove item indicado pelo indice da lista */
Item* removeInd(Lista *l, int loc){
    Item *aux,*ret;
    int i;
    aux = malloc(sizeof(Item));
    ret = malloc(sizeof(Item));
    aux = l->inicio;

    if(loc >= l->tam){
        printf(N_VERM "Erro! " RESET "Índice fora do alcance da lista\n");
        return NULL;
    }

    if(loc == 0){ // caso o item a ser removido sej o primeiro
        l->inicio = aux->prox;
        l->tam--;
        return aux;
    }

    for(i=1;i<loc;i++) aux = aux->prox; // encontra item anterior ao que vai ser removido
    ret = aux->prox;
    aux->prox = aux->prox->prox;
    l->tam--;
    return ret;
}

/* Remove primeira ocorrencia do item indicado */
Item* removeVal(Lista *l, int val){
    Item *aux,*ret;
    int i;
    ret = malloc(sizeof(Item));
    aux = l->inicio;

    if(l->tam == 0){ // caso a lista esteja vazia
        printf(N_VERM "Erro! " RESET "Lista vazia.\n");
        return NULL;
    }

    if(aux->valor == val){ // caso o item removido seja o primeiro
        l->inicio = aux->prox;
        l->tam--;
        return aux;
    }

    while(aux->prox != NULL){
        if(aux->prox->valor == val) break;
        aux = aux->prox;
    }

    if(aux->prox == NULL){
        printf(N_VERM "Erro! " RESET "Item não encontrado.\n");
        return NULL;
    }
    
    ret = aux->prox;
    aux->prox = aux->prox->prox;
    l->tam--;
    return ret;
}

int main(){
    Lista lista;
    Item *rm;
    int i,in,item,op=TRUE;

    printf(N_VERD "\nCÓDIGO EXEMPLO: LISTA ENCADEADA\n" RESET);
    _init_Lista(&lista);
    printf("Insira o tamanho da lista: " AZ);
    scanf("%d",&in);
    printf(RESET "Insira os itens da lista: " AZ);

    for (i=0;i<in;i++){
        scanf("%d", &item);
        if(insereLista(&lista,item,POPULAR) == FALSE) printf(N_VERM "Erro ao inserir item!\n" RESET);
    }
    printf(RESET "\nLista gerada: ");
    imprimeLista(&lista);
    printf(RESET "Tamanho: " VERD "%d\n",lista.tam);

    while(op == TRUE){
        printf(RESET "\nInsira a operação desejada\n"
                     "  0 - Sair\n"
                     "  1 - Remoção por índice\n"
                     "  2 - Remoção por valor\n"
                     "  3 - Inserção no fim\n"
                     "  4 - Inserção por índice\n"
                     "  5 - Impressão da lista\n>> " AZ);
        scanf("%d",&in);

        switch (in){
        case Sair:
            op = FALSE;
            break;

        case RmInd:
            printf(N_BRC "\nRemoção por índice!\n"
                   RESET "Insira o indice do elemento a ser removido: " AZ);
            scanf("%d",&in);
            rm = removeInd(&lista,in);

            if(rm == NULL) printf(N_VERM "Impossível remover item!\n" RESET);
            else printf(RESET "Elemento removido: " VERD "%d\n" RESET,rm->valor);
            break;

        case RmVal:
            printf(N_BRC "\nRemoção por valor!\n"
                   RESET "Insira o valor do elemento a ser removido: " AZ);
            scanf("%d",&in);
            rm = removeVal(&lista,in);

            if(rm == NULL) printf(N_VERM "Impossível remover item!\n" RESET);
            else printf(RESET "Elemento removido: " VERD "%d\n" RESET,rm->valor);
            break;
        
        case InsFim:
            printf(N_BRC "\nInsrerção no fim!\n"
                   RESET "Insira o valor do elemento a ser inserido: " AZ);
            scanf("%d",&item);
            if(insereLista(&lista,item,POPULAR)) printf(RESET "Elemento inserido com sucesso\n\n");
            else printf(N_VERM "Impossível inserir item!\n" RESET);
            break;

        case InsInd:
            printf(N_BRC "\nInsrerção no fim!\n"
                   RESET "Insira o valor do elemento a ser inserido: " AZ);
            scanf("%d",&item);
            printf(RESET "Insira o índice do elemento: " AZ);
            scanf("%d",&in);
            if(insereLista(&lista,item,in)) printf(RESET "Elemento inserido com sucesso\n");
            else printf(N_VERM "Impossível inserir item!\n" RESET);
            break;

        case Imprime:
            printf(RESET "Lista atual: ");
            imprimeLista(&lista);
            break;

        default:
            printf(N_VERM "Erro! " RESET "Operação inválida. [%d]\n",in);
            break;
        }
    }

    printf(RESET "\nLista após alterações: ");
    imprimeLista(&lista);
    printf(RESET "Novo tamanho: " VERD "%d\n",lista.tam);
    printf(N_VERD "Fim da execussão!\n\n" RESET);
    return 0;
}