
#include <stdio.h>
#include <stdlib.h>


#define T 2
#define MAX_CHAVES ( 2 * T - 1 )	//Máximo de registros
#define MAX_FILHOS ( 2 * T )		//Máximo de filhos
#define MIN_CHAVES ( T - 1 )		//Mínimo de registros;

typedef struct tipoArvB{
	int contV;
	int chaves[MAX_CHAVES];
	int folha;
	struct tipoArvB *filhos[MAX_FILHOS]; 

}tipoArvB;

tipoArvB *AlocaNovoNo(){
	int i;
	tipoArvB *no;
	no = (tipoArvB*) malloc(sizeof(tipoArvB));
	no->contV = 0;
	no->folha = 0;
	i = 0;
	while( i < MAX_CHAVES){
		no->chaves[i] = 0;
		no->filhos[i] = NULL;
		i++;
	}
	return no;
}

void InsereChav(tipoArvB *no, int valorRet, tipoArvB *filhoDir){
	int i;
	
	i = (no)->contV;
	while( ( i > 0) && ( valorRet < (no)->chaves[i-1] ) ){
		(no)->chaves[i] = (no)->chaves[i-1];
		(no)->filhos[i+1] = (no)->filhos[i];
		i--;
	}
	(no)->chaves[i] = valorRet;
	(no)->filhos[i+1] = filhoDir;
	(no)->contV++;

}


int BuscaPos(tipoArvB *no, int valor){
	int pos;
	pos = no->contV;
	while( (pos > 0) && (valor < no->chaves[pos-1]) ){
		pos--;
	}
	return pos;
}

tipoArvB *insere(tipoArvB *no,int valor, int *flag,int *valorRet){
	tipoArvB *noAux, *filhoDir;
	int i, pos, meio;

	if(no == NULL){
		*flag = 1;
		*valorRet = valor;
		return NULL;
	} else {

		pos = BuscaPos(no, valor);

		if( (pos < no->contV) && (no->chaves[pos] == valor) ){
			//deu ruim, chave já presente
			*flag = 0;
			return NULL;
		} else {
			if(no->chaves[pos] < valor && (no->chaves[pos] != 0)){
				pos++;
			}

			filhoDir = insere(no->filhos[pos], valor, flag, valorRet);
			if(*flag){
				if(no->contV < MAX_CHAVES){
					InsereChav(no,*valorRet,filhoDir);
					*flag = 0;
				} else {
					noAux = AlocaNovoNo();
					meio = no->chaves[MIN_CHAVES];

					noAux->filhos[0] = no->filhos[MIN_CHAVES+1];

					for(i = MIN_CHAVES+1 ; i < MAX_CHAVES; i++){
						InsereChav(noAux,no->chaves[i], no->filhos[i+1]);
					}

					for (i = MIN_CHAVES; i < MAX_CHAVES; i++) {
						no->chaves[i] = 0;
						no->filhos[i+1] = NULL;
						no->contV--;
					}

					if( pos <= MIN_CHAVES){
						InsereChav(no, *valorRet, filhoDir);
					} else {
						InsereChav(noAux, *valorRet, filhoDir);
					}
					*flag = 1;
					*valorRet = meio;
					return (noAux);

				}
			}
		}
	}
}

tipoArvB *insereArvB(tipoArvB *raiz,int valor){
	tipoArvB *filhoDir, *novaRaiz;
	int valorRet,flag;

	filhoDir = insere(raiz,valor,&flag,&valorRet);

	if(flag){
		novaRaiz = AlocaNovoNo();
		novaRaiz->contV = 1;
		novaRaiz->chaves[0] = valorRet;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->folha = 0;
		return novaRaiz; 
	}
	return raiz;
}


void PreOrdem(tipoArvB *no){
    int i;
    i=0;
    if( no != NULL ){
        while ( ( i < (no)->contV)){
            printf("[%d]",(no)->chaves[i]);
            i++;
        }
   		puts("");
   		i = 0;
   		while( i <= no->contV){
   			PreOrdem( (no)->filhos[i]);
   			i++;	
   		}
    	
        
    }
}





int main(){

	tipoArvB *Tree;
	Tree = NULL;
	Tree = insereArvB(Tree,20);
	Tree = insereArvB(Tree,10);
	Tree = insereArvB(Tree,30);
	Tree = insereArvB(Tree,4);
	Tree = insereArvB(Tree,5);
	Tree = insereArvB(Tree,12);
	Tree = insereArvB(Tree,40);
	Tree = insereArvB(Tree,50);
	Tree = insereArvB(Tree,13);
	Tree = insereArvB(Tree,15);
	Tree = insereArvB(Tree,60);

	PreOrdem(Tree);

	return 0;
}