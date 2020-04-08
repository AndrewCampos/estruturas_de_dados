#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
    int valor;
    struct Item *prox;
    // Demais parâmetros do item da lista
} Item;

typedef struct Lista{
    struct Item *inicio;
    int tam;
} Lista;

int _init_Lista(Lista *l){
    l->inicio = NULL;
    l->tam = 0;
}

int insereLista(Lista *l, Item i){
    int loc;
    Item *aux,*novo;
    novo = malloc(sizeof(Item));
    aux = malloc(sizeof(Item));
    aux = l->inicio;
    novo->valor = i.valor; // atualiza novo item
    novo->prox = i.prox;

    if(l->tam == 0){ // caso a lista esteja vazia
        l->inicio = novo;
        l->tam++;
        return 0;
    }else{
        while(aux->prox != NULL) aux = aux->prox; // encontra o fim da lista
        aux->prox = novo;
        l->tam++;
        return 0;
    }
    return -1;
}

void imprimeLista(Lista *l){
    int i;
    Item *aux;
    aux = malloc(sizeof(Item));
    aux = l->inicio;
    for(i=0;i<l->tam;i++){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
    printf("\n");
}

Item* removeLista(Lista *l, int loc){
    Item *aux,*ret;
    int i;
    aux = malloc(sizeof(Item));
    ret = malloc(sizeof(Item));
    aux = l->inicio;
    l->tam--;

    if(loc == 0){ // caso o item a ser removido sej o primeiro
        l->inicio = aux->prox;
        return aux;
    }

    for(i=1;i<loc;i++) aux = aux->prox; // encontra item anterior ao que vai ser removido
    ret = aux->prox;
    aux->prox = aux->prox->prox;
    return ret;
}

int main(){
    Lista lista;
    Item novo;
    int i,qtd;
    novo.prox = NULL;
    _init_Lista(&lista);
    scanf("%d",&qtd);

    for (i=0;i<qtd;i++){
        scanf("%d",&novo.valor);
        insereLista(&lista,novo);
    }
    imprimeLista(&lista);
    removeLista(&lista,1);
    imprimeLista(&lista);
    return 0;
}