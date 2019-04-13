
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T 2
#define MAX_CHAVES ( 2 * T - 1 )	//Máximo de registros
#define MAX_FILHOS ( 2 * T )		//Máximo de filhos
#define MIN_CHAVES ( T - 1 )		//Mínimo de registros;




typedef struct tipolivro{
	int codp1, codp2;
	long int cod;

	char nome[100];
}tipolivro;


typedef struct tipoArvB{
	int contV;
	struct tipolivro chaves[MAX_CHAVES];
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
		no->chaves[i].codp1 = 0;
		no->chaves[i].codp2 = 0;
		no->chaves[i].cod = 0;
		strcpy(no->chaves[i].nome, "nulo");
		no->filhos[i] = NULL;
		i++;
	}
	return no;
}

void InsereChav(tipoArvB *no, tipolivro valorRet, tipoArvB *filhoDir){
	int i;
	
	i = (no)->contV;
	while( ( i > 0) && ( valorRet.cod < (no)->chaves[i-1].cod ) ){
		(no)->chaves[i] = (no)->chaves[i-1];
		(no)->filhos[i+1] = (no)->filhos[i];
		i--;
	}
	(no)->chaves[i] = valorRet;
	(no)->filhos[i+1] = filhoDir;
	(no)->contV++;

}


int BuscaPos(tipoArvB *no, long int valor){
	int pos;
	pos = no->contV;
	while( (pos > 0) && (valor < no->chaves[pos-1].cod) ){
		pos--;
	}
	return pos;
}

tipoArvB *insere(tipoArvB *no,long int cod,int codp1,int codp2,char nome[], int *flag, tipolivro *livroRet){
	tipoArvB *noAux, *filhoDir;
	int i, pos;
	tipolivro meio;

	if(no == NULL){
		*flag = 1;

		livroRet->cod = cod;
		livroRet->codp1 = codp1;
		livroRet->codp2 = codp2;
		strcpy(livroRet->nome,nome);
		// tipolivro *aux = (tipolivro*) malloc(sizeof(tipolivro));
		// aux->cod = cod;
		// aux->codp1 = codp1;
		// aux->codp2 = codp2;
		// strcpy(aux->nome,nome);
		// livroRet = aux;
		// printf("%d\n",aux->codp1);

		
		return NULL;
	} else {

		pos = BuscaPos(no, cod);

		if( (pos < no->contV) && (no->chaves[pos].cod == cod) ){
			//deu ruim, chave já presente
			*flag = 0;
			return NULL;
		} else {
			if(no->chaves[pos].cod < cod && (no->chaves[pos].cod != 0)){
				pos++;
			}

			filhoDir = insere(no->filhos[pos],cod,codp1,codp2,nome, flag, livroRet);
			if(*flag){
				if(no->contV < MAX_CHAVES){
					InsereChav(no,*livroRet,filhoDir);
					*flag = 0;
				} else {
					noAux = AlocaNovoNo();
					meio = no->chaves[MIN_CHAVES];

					noAux->filhos[0] = no->filhos[MIN_CHAVES+1]; 

					for(i = MIN_CHAVES+1 ; i < MAX_CHAVES; i++){
						InsereChav(noAux,no->chaves[i], no->filhos[i+1]);
					}

					for (i = MIN_CHAVES; i < MAX_CHAVES; i++) {
						no->chaves[i].cod = 0;
						no->chaves[i].codp1 = 0;
						no->chaves[i].codp2 = 0;
						strcpy(no->chaves[i].nome, "zero");
						no->filhos[i+1] = NULL;
						no->contV--;
					}

					if( pos <= MIN_CHAVES){
						InsereChav(no, *livroRet, filhoDir);
					} else {
						InsereChav(noAux, *livroRet, filhoDir);
					}
					*flag = 1;
					*livroRet = meio;
					return (noAux);

				}
			}
		}
	}
}



tipoArvB *insereArvB(tipoArvB *raiz,long int cod,int codp1,int codp2,char nome[]){
	tipoArvB *filhoDir, *novaRaiz;
	int	flag;
	tipolivro livroRet;
	
	//printf("%d\n",codp1);
	filhoDir = insere(raiz,cod,codp1,codp2,nome,&flag, &livroRet);

	//printf("Test: %d \n", livroRet->codp1);

	if(flag){
		novaRaiz = AlocaNovoNo();
		novaRaiz->contV = 1;
		novaRaiz->chaves[0] = livroRet;
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
            printf("[%.4d-%.4d   %s]",(no)->chaves[i].codp1,(no)->chaves[i].codp2,(no)->chaves[i].nome);

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
	long int cod;
	FILE *arqv;
	int codp1,codp2;
	char nome[100];

	//arqv = fopen("livros.txt","r");
	// if(arqv == NULL){
	// 	puts("Falha na abertura do arquivo, por favor, melhore.");
	// 	return 0;
	// }

	// while( fscanf(arqv,"%d-%d %s",&codp1,&codp2,nome) != EOF){
 //    	cod = ( (codp1*10*10*10*10) + codp2);
 //    	Tree = insereArvB(Tree,cod,codp1,codp2,nome);
  		
 //    } 

	scanf("%d-%d %s",&codp1,&codp2,nome);
	scanf("%*c");
	Tree = insereArvB(Tree,cod,codp1,codp2,nome);
	scanf("%d-%d %s",&codp1,&codp2,nome);
	scanf("%*c");
	Tree = insereArvB(Tree,cod,codp1,codp2,nome);
	scanf("%d-%d %s",&codp1,&codp2,nome);
	scanf("%*c");
	Tree = insereArvB(Tree,cod,codp1,codp2,nome);

	// PreOrdem(Tree);
	fclose(arqv);	
	

	return 0;
}