

/* Regras da arvore RN

1 - todo nó é vermelho ou preto
2 - se um nó é folha então ele é preto
3 - a raiz é preta
4 - qualquer caminnho da raiz até uma folha têm numero igual de nós pretos
5 - o pai de um nó vermelho é pretd
6 - se um nó vermelho então seus filhos são pretos
7 - todo novo nó é posto como vermelho


*/


#include <stdio.h>
#include <stdlib.h>



typedef struct tipoRN{
    int valor,cor;
    struct tipoRN *esq, *dir;
        
}tipoRN;

// 0 = preto, 1 = vermelho


tipoRN *RD(tipoRN *no,tipoRN *pai,tipoRN *avo){
	avo->esq = pai->dir;
	pai->dir = avo;
	pai->cor = 0; //preto
	avo->cor = 1; //vermelho
	return pai;
}

tipoRN *RE(tipoRN *no,tipoRN *pai, tipoRN *avo){
	avo->dir = pai->esq;
	pai->esq = avo;

	pai->cor = 0; //preto
	avo->cor = 1; //vermelho
	return pai;
}

tipoRN *RED(tipoRN *no,tipoRN *pai,tipoRN *avo){
	pai->dir = no->esq;
	avo->esq = no->dir;
	no->esq = pai;
	no->dir = avo;

	no->cor = 0; //preto
	pai->cor = 1; //vermelho
	avo->cor = 1; //vermelho
	return no;
}

tipoRN *RDE(tipoRN *no,tipoRN *pai,tipoRN *avo){
	pai->esq = no->dir;
	avo->dir = no->esq;
	no->esq = avo;
	no->dir = pai;

	no->cor = 0; //preto
	pai->cor = 1; //preto
	avo->cor = 1; //preto

	return no;
}




int balanceamento(tipoRN *no, tipoRN *pai, tipoRN *avo,tipoRN *bisavo, tipoRN **raiz){
	tipoRN *tio, *raizsub;
	int flagb;
	flagb = 2;
	if(pai != NULL){
		if(pai->cor == 1){
			//verifica tio
			if(pai == avo->esq){
				tio = avo->dir;

			} else {
				tio = avo->esq;
			}
			
			if( (tio == NULL) || (tio->cor == 0) ){
				// se sim, precisa acontecer um rodamento
				if(pai == avo->esq){

					if(no == pai->esq ){
						//se o pai é filho esq e o no tb é filho esq, entao rotacao simples à direita
                        raizsub = RD(no,pai,avo); //atualiza raizSubArv
                    } else {
                    	//se o pai é filho esq, mas o no é filho direito, entao rotacao dupla esq-dir
                        raizsub = RED(no,pai,avo); //atualiza raizSubArv
                    }


				} else {

					if(no == pai->dir){
						 //se o pai é filho dir e o no tb, entao rotacao simples à esq
                        raizsub = RE(no,pai,avo); //atualiza raizSubArv
					} else {
						//se o pai é filho dir e o no é filho dir, entao rotacao dupla dir-esq
                        raizsub = RDE(no,pai,avo); //atualiza raizSubArv
					}

				}
				if(bisavo != NULL){
					if(no->valor < bisavo->valor){
						bisavo->esq = raizsub;
					} else {
						bisavo->dir = raizsub;
					}
				} else {
					*raiz = raizsub;
				}

			} else {
				//Se o tio é VERMELHO, entao basta atualizar as cores
                pai->cor = 0;
                tio->cor = 0;
                avo->cor = 1;
                flagb = 0;
			}
		}
		return flagb;
	} else {
		//Caso o pai seja nulo, nao há nada a fazer, estamos em um no filho da raiz;
		return 2;
	}
}

int insere_em_RN(tipoRN *no,int valor,tipoRN *pai, tipoRN *avo,tipoRN **raiz){
	tipoRN **aux;
	int flagS;
	if(no == NULL){
		no = (tipoRN*)malloc(sizeof(tipoRN));
		no->valor = valor;
		no->esq = NULL;
		no->dir = NULL;
		no->cor = 1;
		if( (*raiz) == NULL){
			(*raiz) = no;
		} else {
			if(valor < pai->valor){
				pai->esq = no;
			} else {
				pai->dir = no;
			}
			//inserção certinha bitcho
			return 1;
		}

	} else {
		if( valor != no->valor){
			if( valor < no->valor){
				aux = &(no->esq);
			} else {
				aux = &(no->dir);
			}
			flagS = insere_em_RN(*aux, valor, no, pai, raiz); //Chamada recursiva
			switch(flagS){
				case 0:
					return 1;
					break;
				case 1:
					return balanceamento(*aux,no,pai,avo,raiz);
					// função balanceamento
				/*
					if(aux == NULL){
						if(valor < no->valor){
							return balanceamento(no->esq,no,pai,avo,raiz);
						} else {
							return balanceamento(no->dir,no,pai,avo,raiz);
						}
					}
				*/
					break;
				case 2:
					return 2;
					break;
			}
		} else {
			// inserção com valor já existente 
			return 0;
		}
	}
}

tipoRN *insereRN(tipoRN *T, int valor){
	tipoRN *raiz;
	raiz = T;
	insere_em_RN(T,valor,NULL,NULL, &raiz);  //Parametros: arv, valor, pai, avo, raiz
	raiz->cor = 0;
	return raiz;
}





void Impressao(tipoRN *raiz,int n){
    tipoRN *no;
    int i;
    no = (raiz);
    if(no != NULL){
        Impressao(no->dir,n+1);
        
        for(i = 0; i < n;i++){
            printf("\t");
        }
        printf("%d(%d)\n",no->valor,no->cor);
        Impressao(no->esq,n+1);
        
    }
}


int main(){
	tipoRN *T;

	T = NULL;
	T = insereRN(T,80);
	T = insereRN(T,15);
	T = insereRN(T,89);
	T = insereRN(T,50);
	/*
	T = insereRN(T,67);
	T = insereRN(T,37);
	T = insereRN(T,82);
	T = insereRN(T,79);
	T = insereRN(T,41);
	T = insereRN(T,49);
	T = insereRN(T,22);
	*/
	Impressao(T,0);

	return 0;
}