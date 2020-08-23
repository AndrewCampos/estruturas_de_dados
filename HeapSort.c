#include <stdio.h>
#include <stdlib.h>
#define COLOR_RED  "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_WHITE "\x1b[37m"
int N;

/* Troca a posição de dois itens no vetor */
void troca(int* V, int i1, int i2){
    int aux;
    aux = V[i1];
    V[i1] = V[i2];
    V[i2] = aux;
}

/* Imprime vetor completo */
void imprime(int* V, int tam){
    int i;
    for(i=1;i<=tam;i++) printf("%d ",V[i]);
    printf("\n");
}

/* Verifica heap entre pai e filhos */
void max_heapfy(int* V, int ind){
    int esq, dir, max;
    esq = ind*2;
    dir = esq+1;
    // confere se existe filhos e se os valores sao maiores que o pai
    if(esq <= N && V[esq] > V[ind]) max = esq;
    else max = ind;
    if(dir <= N && V[dir] > V[max]) max = dir;
    // troca o a posicao [max] com a posicao [ind]
    if(max != ind){
        troca(V,ind,max);
        max_heapfy(V,max);
    }
}

/* Constroi Heap */
void build_max_heap(int* V){
    int i;
    for(i=N/2;i>=1;i--)
        max_heapfy(V,i);
}

/* Reposiciona o maior elemento do heap */
int heap_extract_max(int* V){
    int max;
    if(N < 1){
        printf(COLOR_RED "Underflow\n");
        return -1;
    }
    troca(V,1,N);
    N--;
    max_heapfy(V,1);
    return max;
}

/* Ordena vetor */
void heapSort(int* Vin){
    build_max_heap(Vin);
    while(N > 0) heap_extract_max(Vin);
}

/* Função principal */
int main(){
    int tam,i,*vet;
    // le numeros de entrada
    printf("\n========== HEAP SORT ==========\n");
    printf("Insira a quantidade de elementos: "COLOR_BLUE);
    scanf("%d",&N);
    tam = N;
    vet = malloc((N+1)*sizeof(int));
    printf(COLOR_WHITE"Insira os elementos a serem ordenados: "COLOR_BLUE);
    for(i=1;i<N+1;i++) scanf("%d",&vet[i]);
    printf(COLOR_GREEN "Construindo Max-Heap...\n" COLOR_WHITE);
    build_max_heap(vet);
    imprime(vet, tam);
    printf(COLOR_GREEN "Ordenando vetor...\n" COLOR_WHITE);
    heapSort(vet);
    imprime(vet, tam);
    printf(COLOR_GREEN"Fim da execussão!\n\n"COLOR_WHITE);
    return 0;
}