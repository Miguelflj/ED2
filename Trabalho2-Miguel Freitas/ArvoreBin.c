#include <stdio.h>
#include <stdlib.h>



struct estArvoreBinaria {
    int valor;
    struct estArvoreBinaria *esq;
    struct estArvoreBinaria *dir;
};


typedef struct estArvoreBinaria arvBin;


void InsereArvore(arvBin **raiz, int vlr);
arvBin* BuscaArvore(arvBin **raiz,int vlr);
void Pre_ordem(arvBin *raiz);
void Ordem(arvBin *raiz);
void Pos_ordem(arvBin *raiz);
void ImprimeNivel(arvBin *raiz, int nivel, int nivelPassagem);
int BuscaNivel(arvBin *raiz, int vlr);
int alturaArv(arvBin *raiz);

int main(int argc, char *argv[] ){
    
    int op,n,pos;
    arvBin *raiz, *aux;
    raiz = NULL;

    FILE *arqv;
    if(argc <= 1){
        puts("Passe nome do arquivo de entrada!");
        return 0;
    }

    arqv = fopen(argv[1],"r");
    
    if( arqv == NULL){
        puts("Erro na abertura do arquvio.");
        return 0;
    }
    while( fscanf(arqv,"%d",&n) != EOF){
        InsereArvore(&raiz, n);
    }


    n = alturaArv(raiz);
    if( n < 0){
        puts("Arvore vazia");
    } else {
        printf("Altura: %d\n", n);
    }

    /*
    do{
    puts("Digite a opção:\n1-Inserir\n2-Buscar\n3-Remover\n4-Pré Ordem\n5-Ordem\n6-Pós Ordem\n7-Imprime niveis\n8-Busca nó por valor\n9-Altura arvore\n0-Sair");
    scanf("%d", &op);
    system("clear");
    switch(op){
        case 1:
            puts("Digite um valor");
            scanf("%d", &n);
            InsereArvore(&raiz, n);
            break;
        case 2:
            puts("Digite um valor");
            scanf("%d", &n);
            aux = BuscaArvore(&raiz, n);
            if( aux == NULL){
                puts("valor invalido");
            } else {
                printf("[%d]\n", aux->valor);
            }
            break;
        case 3:
            
            break;
        case 4:
            Pre_ordem(raiz);
            break;
        case 5:
            Ordem(raiz);
            break;
        case 6:
           Pos_ordem(raiz);
            break;
        case 7:
            puts("Digite o nivel que deseja imprimir");
            scanf("%d",&pos);
            ImprimeNivel(raiz,pos, 0);
            break;
        case 8:
            puts("Digite o valor desejado");
            scanf("%d",&n);
            n = BuscaNivel(raiz, n);
            if( n < 0){
                puts("Valor invalido");
            } else {
                printf("Nó na pos: %d\n", n);
            }
            break;
        case 9:
            n = alturaArv(raiz);
            if( n < 0){
                puts("Arvore vazia");
            } else {
                printf("Altura da arvore eh : %d\n", n);
            }
            break;
        default:
            break;
        
    }
    }while(op != 0); 


*/




    return 0;
}

void InsereArvore(arvBin **raiz, int vlr){
    arvBin *novo, *no;
    no = (*raiz);
    if( (*raiz) == NULL){
        novo = (arvBin*) malloc(sizeof(arvBin*));
        novo->valor = vlr;
        novo->esq = NULL;
        novo->dir = NULL;
        //na ponta do no que está inserindo
        (*raiz) = novo;
        
    } else {
        if( vlr < (no)->valor){
            InsereArvore(&(no->esq), vlr);

        } else {
            InsereArvore(&(no->dir), vlr);

        }
    }

}

arvBin* BuscaArvore(arvBin **raiz,int vlr){
    arvBin *no;
    no = (*raiz);

    if( no == NULL) {
        return NULL;
    } else {
            if( vlr == no->valor){
                return no;
            } else {
                if(vlr < no->valor){
                    BuscaArvore(&(no->esq), vlr);
                } else {
                    BuscaArvore(&(no->dir), vlr);
                }
            }
        }

}

void Pre_ordem(arvBin *raiz){
    arvBin *no;
    no = raiz;
    if( no != NULL){
        printf("[%d]\n",no->valor);
        Pre_ordem((no->esq));
        Pre_ordem((no->dir));
    }
}


void Ordem(arvBin *raiz){
    arvBin *no;
    no = raiz;
    if( no != NULL){
        Ordem((no->esq));
        printf("[%d]\n",no->valor);
        Ordem((no->dir));
    }
}

void Pos_ordem(arvBin *raiz){
    arvBin *no;
    no = raiz;
    if( no != NULL){
        Pos_ordem((no->esq));
        Pos_ordem((no->dir));
        printf("[%d]\n",no->valor);
    }
}

int BuscaNivel(arvBin *raiz, int vlr){
    int nivel=0,soma;
    arvBin *aux;
    aux = raiz;
    if(raiz != NULL){
        if(vlr == aux->valor){
            return 0;
        } else {
            if( vlr < aux->valor){
                nivel = BuscaNivel(aux->esq,vlr);
                
            } else {
                nivel = BuscaNivel(aux->dir,vlr);
            }
            if(nivel < 0){
                return nivel;
            } else {
                return nivel+1;
            }
        }
    } else {
        return -1 ;
    }
}


void ImprimeNivel(arvBin *raiz, int nivel, int nivelPassagem){
    arvBin *aux;
    aux = raiz;
    if(raiz != NULL){
                ImprimeNivel(aux->esq,nivel,nivelPassagem+1);
                ImprimeNivel(aux->dir,nivel, nivelPassagem+1);
                
                if(nivel == nivelPassagem){
                    printf("[%d]\n",aux->valor);
                }
    } else {
    }
}

int alturaArv(arvBin *raiz){
    if( raiz == NULL){
        return -1;
    } else {
        int esq=0, dir=0;
        esq = alturaArv(raiz->esq);
        dir = alturaArv(raiz->dir);
        if(esq>dir) {
            return esq+1;
        } else {
            return dir+1;
        }
    }
    
    
}
