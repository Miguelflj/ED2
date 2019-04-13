/*
    UFMT - CCOMP
    Arvore AVL - ED2
    Miguel Freitas
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// https://www.cs.usfca.edu/~galles/visualization/AVLtree.html ( simulador AVL)


typedef struct tipoAvl{
    int valor;
    int fb;
    struct tipoAvl *esq;
    struct tipoAvl *dir;

}tipoAvl;



// Peso pro lado direito ficou (NEGATIVO)  e o pro lado esquerdo (POSITIVO)  


tipoAvl *RDir(tipoAvl *no,tipoAvl *r){
    
    no->esq = r->dir;
    r->dir = no;
    no->fb = 0;
    r->fb = 0;

    return r;
}


tipoAvl *REsq(tipoAvl *no,tipoAvl *r){

    no->dir = r->esq;
    r->esq = no;
    no->fb = 0;
    r->fb = 0;

    return r;
}


//Direita esquerda -- perfect
tipoAvl *RDrupoEsq(tipoAvl *no,tipoAvl *r){
    tipoAvl *aux;
    aux = r->esq;

    no->dir = aux->esq;
    r->esq = aux->dir;
    aux->esq = no;
    aux->dir = r;
    
    if(aux->fb == -1){
        no->fb = 1;
        r->fb = 0;
    } else if(aux->fb == 0){
        no->fb = 0;
        r->fb = 0;
    } else if(aux->fb == 1){
        no->fb = 0;
        r->fb = -1;
    }

    aux->fb = 0;

    return aux;
}


//esquerda direita -- perfect
tipoAvl *RDrupoDir(tipoAvl *no,tipoAvl *r){
    tipoAvl *aux;
    aux = r->dir;

    no->esq = aux->dir;
    r->dir = aux->esq;
    aux->esq = r;
    aux->dir = no;

    if(aux->fb == -1){
        no->fb = 0;
        r->fb = 1;
    } else if(aux->fb == 0){
        no->fb = 0;
        r->fb = 0;
    } else if(aux->fb == 1){
        no->fb = -1;
        r->fb = 0;

    }

    aux->fb = 0;

    return aux;
}
    

tipoAvl *InsereArvore(tipoAvl *no, int vlr,int *flag,long int rot[]){
    tipoAvl *novo,*fEsq,*fDir;
    


    if( no == NULL){
        novo = (tipoAvl*) malloc(sizeof(tipoAvl*));

        novo->valor = vlr;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        return novo;


    } else {
        if( vlr < no->valor){

            no->esq = InsereArvore(no->esq, vlr,flag,rot);


            if(*flag == 0){
                no->fb++;
                
            }
             if(no->fb == 0){
                *flag = 1;
            }

            if(no->fb == 2){
                

                fEsq = no->esq;
                switch(fEsq->fb){

                    case 1:
                        no = RDir(no,fEsq);
                        rot[0]++;
                        break;
                    case -1:
                        // esquerda direita
                        no = RDrupoDir(no,fEsq);
                        rot[0]++;
                        rot[0]++;
                        break;
                }
                // houve rotação, nao precisa continuar a analise do desbalanceamento
                *flag = 1;
            }
            
        } else {

            no->dir = InsereArvore(no->dir, vlr,flag,rot);

            if(*flag == 0){
                no->fb--;
            }
            if(no->fb == 0){
                *flag = 1;
            }
            if(no->fb == -2){
                

                fDir = no->dir;
                switch(fDir->fb){
                    case -1:
                        no = REsq(no,fDir);
                        rot[1]++;
                        break;
                    case 1:
                        //direita esquerda
                        no = RDrupoEsq(no,fDir);
                        rot[1]++;
                        rot[1]++;
                        break;

                }
                // houve rotação, nao precisa continuar a analise do desbalanceamento
                *flag = 1;
            }

            
        }
    }
    return no;

}


void Impressao(tipoAvl *raiz,int n){
    tipoAvl *no;
    int i ;
    no = (raiz);
    if(no != NULL){
        Impressao(no->dir,n+1);
        
        for(i = 0; i < n;i++){
            printf("\t");
        }
        printf("%d(%d)\n",no->valor,no->fb);
        Impressao(no->esq,n+1);
        
    }
}

int alturaArv(tipoAvl *raiz){
    if( raiz == NULL){
        return -1;
    } else {
        int esq=1, dir=1;
        esq = alturaArv(raiz->esq);
        dir = alturaArv(raiz->dir);
        if(esq>dir) {
            return esq+1;
        } else {
            return dir+1;
        }
    }
    
    
}



int main(int argc, char *argv[]){
    tipoAvl *T;
    int flag = 0;
    
    T = NULL;
    int op, valor,alt;
    long int rot[2], totalrot;
    // rot  = total de rotações
    rot[0] = 0;
    rot[1] = 0;
    FILE *arqv;


    if(argc <= 1){
        puts("Passe nome do arquivo de entrada!");
        return 0;
    }
    
    arqv = fopen(argv[1],"r");
    if( arqv == NULL){
        puts("Erro na abertura do arquivo");
        return 0;
    }
    while( fscanf(arqv,"%d",&valor) != EOF){
        flag = 0;
        T = InsereArvore(T,valor,&flag,rot);
    }
    /*
    do{
        puts("Opções:\n 1 - Inserção\n 2 - Imprimir\n");
        scanf("%d",&op);
        system("clear");
        switch(op){
            case 1:

                flag = 0;
                puts("Digite o valor");
                scanf("%d",&valor);
                T = InsereArvore(T,valor,&flag,rot);

                break;
            case 2:

                Impressao(T,0);

                break;
            case 0:
                break;
            default:
                puts("Op inválida!");
                break;
                
        }
    } while(op != 0);
    
    */
    totalrot = rot[0] + rot[1];
    //Impressao(T,0);
    printf("Total de rotações: %ld\n",totalrot);

    alt = alturaArv(T);
    if(alt == -1){
        puts("Arvore nula");
    } else{
        printf("Altura: %d\n",alt);
    }   

    return 0;
}




