#include <stdio.h>
#include <stdlib.h>
#define COLOR_RED  "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_WHITE "\x1b[37m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define True 1
#define False 0
/* Variável Booleana */
typedef int Boolean;

/* Nó da árvore */
typedef struct TNo{
    int indice; // valor da chave do nó
    int fEQ; // fator de equilíbrio
    struct TNo *dir, *esq; // filhos da esquerda e da direita
}TNo;

/* Estrutura básica da árvore */
typedef struct TArvore{
    struct TNo *ini;
    int tam;
    int altura;
}TArvore;

/* Inicializa a arvore */
void _init_Arvore(TArvore *A){
    A->ini = NULL;
    A->tam = 0;
    A->altura = 0;
}

/* Mede a altura da arvore */
int medeAltura(TNo *no, int h){
    int hesq,hdir;
    if(no == NULL) return h;
    h++;
    hdir = medeAltura(no->dir,h);
    hesq = medeAltura(no->esq,h);
    if(hdir > hesq) return hdir;
    else return hesq;
}

/* Atualiza fator de equilíbrio */
void attEQ(TNo *no){
    int hesq,hdir;
    if(no == NULL) return;
    attEQ(no->esq);
    attEQ(no->dir);
    hesq = medeAltura(no->esq,0);
    hdir = medeAltura(no->dir,0);
    no->fEQ = hesq - hdir;
}

/* Rotação simples à esquerda */
TNo* RR(TNo *A){
    TNo *B;
    int hesq,hdir;
    B = A->dir;
    // rotaciona nó A para baixo
    A->dir = B->esq;
    // rotaciona nó B para cima
    B->esq = A;
    B->fEQ = 0;
    return B;
}

/* Rotação direita-esquerda */
TNo* RL(TNo *A){
    TNo *B,*C;
    int hesq,hdir;
    B = A->dir;
    C = B->esq;
    // rotaciona B para baixo
    B->esq = C->dir;
    // rotaciona C para cima
    C->dir = B;
    // rotaciona A para baixo
    A->dir = C->esq;
    // rotaciona C para cima
    C->esq = A;
    C->fEQ = 0;
    return C;
}

/* Rotação simples à direita */
TNo* LL(TNo *A){
    TNo *B;
    int hesq,hdir;
    B = A->esq;
    // rotaciona nó A para baixo
    A->esq = B->dir;
    // rotaciona nó B para cima
    B->dir = A;
    B->fEQ = 0;
    return B;
}

/* Rotação dupla para a direita */
TNo* LR(TNo *A){
    TNo *B,*C;
    int hesq,hdir;
    B = A->esq;
    C = B->dir;
    // rotaciona B para baixo
    B->dir = C->esq;
    // rotaciona C para cima
    C->esq = B;
    // rotaciona A para baixo
    A->esq = C->dir;
    // rotaciona c para cima
    C->dir = A;
    C->fEQ = 0;
    return C;
}

/* Confere os fatores de equilibrio e balanceia a árvore se necessário */
TNo* balanceia(TArvore *A, TNo *no){
    Boolean flag = False;
    // confere se o nó existe
    if(no == NULL) return NULL;
    if(no == A->ini) flag = True;

    // balanceia as sub arvores (pós-ordem)
    no->esq = balanceia(A,no->esq);
    no->dir = balanceia(A,no->dir);
    // confere balanceamento do nó
    if(no->fEQ>1){
        if(no->esq->fEQ<0) no = LR(no);
        else no = LL(no);
    }else if(no->fEQ<-1){
        if(no->dir->fEQ>0) no = RL(no);
        else no = RR(no);
    } 
    attEQ(A->ini);
    if(flag) A->ini = no;
    return no;
}

/* Cria novo nó */
TNo* novoNO(int chave){
    TNo *novo;
    novo = malloc(sizeof(TNo));
    novo->fEQ = 0;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->indice = chave;
    return novo;
}

/* Insere novo no na arvore */
int insereNO(TArvore *A, int chave){
    int h = 1;
    TNo *pont;
    pont = A->ini;
    if(A->tam == 0){
        A->ini = novoNO(chave);
        A->tam++;
        A->altura++;
        return 0;
    }

    while(pont != NULL){
        h++;
        if(chave < pont->indice){ // verifica se a chave vai ser inserida a esquerda ou a direita
            pont->fEQ++;
            if(pont->esq != NULL){ // verifica se existe filho a esquerda
                pont = pont->esq;
            }
            else{
                pont->esq = novoNO(chave);
                A->tam++;
                if(h > A->altura) A->altura = h; // atualiza altura
                return 0;
            }
        }else{
            pont->fEQ--;
            if(pont->dir != NULL){ // verifica se existe filho a direita
                pont = pont->dir;
            }
            else{
                pont->dir = novoNO(chave);
                A->tam++;
                if(h > A->altura) A->altura = h; // atualiza altura
                return 0;
            }
        }
    }
    return -1;
}

/* Remove um no da arvore */
TNo* removeNO(TArvore *A, TNo *no){
    TNo *aux;
    A->tam--;
    // caso no removido seja folha
    if(no->dir == NULL && no->esq == NULL){
        return NULL;
    }
    // caso o no removido tenha os dois filhos
    if(no->esq != NULL && no->dir != NULL){
        aux = no->dir;
        while(aux->esq->esq != NULL) aux = aux->esq;
        no->indice = aux->esq->indice; // copia o menor filho
        aux->esq = aux->esq->dir; // sobe o filho da direita do menor filho
        return no;
    }
    // caso no tenha apenas o filho direito
    if(no->dir != NULL)
        return no->dir;
    // caso no tenha apenas o filho esquerdo
    if(no->esq != NULL)
        return no->esq;
    exit -1;
}

/* Busca um determinado nó da árvore e caso ele exista o remove */
Boolean buscaNO(TArvore *A, int chave){
    TNo *aux;
    aux = A->ini;
    if(aux->indice == chave) A->ini = removeNO(A,aux); // confere se o nó buscadpo é raiz
    while (True){
        if(chave > aux->indice){ // confere para qual lado o nó buscado está
            if(aux->dir == NULL) return False; // caso o nó não tenha filho da direita
            if(aux->dir->indice == chave){ // caso filho da direita seja o nó buscado
                aux->dir = removeNO(A,aux->dir);
                balanceia(A,A->ini);
                A->altura = medeAltura(A->ini,0);
                return True;
            }else aux = aux->dir; // caso o filho da direita não seja o nó buscado
        }else{
            if(aux->esq == NULL) return False; // caso no não tenha filho da esquerda
            if(aux->esq->indice == chave){ // caso filho da esquerda seja o nó buscado
                aux->esq = removeNO(A,aux->esq);
                balanceia(A,A->ini);
                A->altura = medeAltura(A->ini,0);
                return True;
            }else aux = aux->esq; // caso o filho da esquerda não seja o no buscado
        }
    }
    return False;
}

/* Confere se a arvore respeita os parametros para uma AVL */ 
Boolean checaEQ(TNo *no){
    Boolean EQ=True;
    if(no == NULL) return EQ;
    if(!checaEQ(no->esq)) return False;
    if(!checaEQ(no->dir)) return False;
    if(no->fEQ > 1 || no->fEQ < -1) return False;
    return True;    
}

/* Imprime árvore na forma de parênteses aninhados */
void imprimeArvore(TNo *no){
    printf("(");
    if(no == NULL) return;
    printf("%d ",no->indice);
    imprimeArvore(no->esq);
    printf(")");
    imprimeArvore(no->dir);
    printf(")");
}

int main(){
    int chave,i,cont=0,busca;
    Boolean EQ;
    TArvore A;
    _init_Arvore(&A);
    printf(COLOR_WHITE "Insira, separado por espaços, as chaves a serem inseridas na árvore: " COLOR_GREEN);
    while(True){
        scanf("%d",&chave);
        if(chave < 0) break;
        insereNO(&A,chave);
        balanceia(&A,A.ini);
        A.altura = medeAltura(A.ini,0);
        cont++;
    }
    if(checaEQ(A.ini)){
        printf(COLOR_WHITE "\nA ÁRVORE RERSPEITA A CONDIÇÃO DE AVL!\n" COLOR_GREEN);
        imprimeArvore(A.ini);
        printf("\n");
        printf(COLOR_WHITE "Insira o valor a ser buscado: " COLOR_GREEN);
        scanf("%d",&busca);

        if(buscaNO(&A,busca) == False){
            printf(COLOR_WHITE "Nó %d não encontrado! Inserindo nó.\n", busca);
            insereNO(&A,busca);

        }else printf(COLOR_WHITE "Nó %d removido com sucesso!\n" COLOR_GREEN,busca);
    }
    printf(COLOR_WHITE "Balanceando árvore...\n" COLOR_GREEN);
    i = 0;

    while(!checaEQ(A.ini)){
        i++;
        balanceia(&A,A.ini);
        if(i == 5) return -1;
    }
    printf(COLOR_WHITE "Árvore balanceada!\n" COLOR_GREEN);
    imprimeArvore(A.ini);
    printf("\n");
    printf(COLOR_WHITE "Altura inicial: " COLOR_GREEN "%d\n",A.altura);
    printf(COLOR_WHITE "Altura balanceada: " COLOR_GREEN "%d\n",medeAltura(A.ini,0));
    return 0;
}