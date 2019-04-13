/*

Funções para lidar com matriz esparsa e controlar a captura de tecla

*/
#include <stdio.h>
#include <stdlib.h>


#ifndef _TIPO_MTZ_
#define _TIPO_MTZ_
typedef struct Cel{
	int valor;
	int idxC;
	int idxL;
	// proxL é o de andar na linha(horizontal)
	struct Cel *proxL;
	// proxC é o de andar nas colunas(vertical)
	struct Cel *proxC;
	// sim, ta trocado, seu zé.

}Cel;


typedef struct Cabe{
	int idx;
	struct Cabe *proxCabe;
	struct Cel *proxCel;

}Cabe;

typedef struct mtzEspaca{
	struct Cabe *Linha;
	struct Cabe *Coluna;

}mtzEspaca;

#endif

//Protótipos das funções
void InicializaCorner(mtzEspaca **corner);
Cabe *novoCabecalho(int pos);
void Cabecalho(mtzEspaca **corner,int posLinha,int PosColuna);
Cel *novaCelula(int valor,int posL,int posC);
void InsereCelula(mtzEspaca **corner,int linha,int coluna,int valor);
int VerificaCelula(Cel *navega,int posl,int posc,int valor);
void caminhaEguarda(mtzEspaca *corner);

void InicializaCorner(mtzEspaca **corner){

	*corner = (mtzEspaca*) malloc( sizeof(mtzEspaca) );

	(*corner)->Linha = NULL;
	(*corner)->Coluna = NULL;

};


Cabe *novoCabecalho(int pos){
	Cabe *novo;

	novo = (Cabe*) malloc(sizeof(Cabe));
	novo->idx = pos;
	novo->proxCabe = NULL;
	novo->proxCel = NULL;

	return novo;
}

Cel *novaCelula(int valor,int posL,int posC){
	Cel *novo;

	novo = (Cel*) malloc( sizeof(Cel) );
	novo->valor = valor;
	novo->idxC = posC;
	novo->idxL = posL;
	novo->proxL = NULL;
	novo->proxC = NULL;

	return novo;

}


void Cabecalho(mtzEspaca **corner,int posLinha,int posColuna){
	Cabe *aux,*novoL,*auxAnt,*novoC;

   
	// cria ou verifica a linha
    aux = (*corner)->Linha;
    auxAnt = NULL;

    while ( (aux != NULL) && (aux->idx < posLinha) ){

        auxAnt = aux;
        aux = aux->proxCabe;
        //puts("entrou");
   	}
   	//puts("passou");
   	
	if( (aux != NULL) && (auxAnt == NULL) && (aux->idx != posLinha) ) {
		//puts("entrouuu");
		// inser no inicio
		novoL = novoCabecalho(posLinha);
		novoL->proxCabe = aux;
		(*corner)->Linha = novoL;	

	} else if( (aux == NULL ) && ( auxAnt != NULL ) && (auxAnt->idx != posLinha) ){
		//inser no fim
		novoL = novoCabecalho(posLinha);
		auxAnt->proxCabe = novoL;

	}	else if( (aux != NULL) && (auxAnt != NULL) && (aux->idx != posLinha) && auxAnt->idx != posLinha) {
		inser no meio
		novoL = novoCabecalho(posLinha);
		novoL->proxCabe = aux;
		auxAnt->proxCabe = novoL;
	} else if(aux == NULL && auxAnt == NULL) {
		//inser no null
		novoL = novoCabecalho(posLinha);
		(*corner)->Linha = novoL;
		
	} else if(aux->idx == posLinha) {
		//puts("Já ecxziste a linha!");
	}
	
	   

	// cria ou verifica a coluna
    aux = (*corner)->Coluna;
    auxAnt = NULL;
    while ( (aux != NULL) && (aux->idx < posColuna) ){

        auxAnt = aux;
        aux = aux->proxCabe;
        //puts("entrou");
   	}

	if( (aux != NULL) && (auxAnt == NULL) && (aux->idx != posColuna) && (aux->idx != posColuna) ){

		novoL = novoCabecalho(posColuna);
		novoL->proxCabe = aux;	
		(*corner)->Coluna = novoL;
	
	} else if( (aux == NULL ) && ( auxAnt != NULL ) && (auxAnt->idx != posColuna) ){
		//puts("entrouuu");
		novoL = novoCabecalho(posColuna);
		auxAnt->proxCabe = novoL;	

	}else if( (aux != NULL) && (auxAnt != NULL) && (aux->idx != posColuna ) && (auxAnt->idx != posColuna) ) {
		novoL = novoCabecalho(posColuna);
		novoL->proxCabe = aux;
		auxAnt->proxCabe = novoL;
	} else if( (aux == NULL) && (auxAnt == NULL) ) {
		novoL = novoCabecalho(posColuna);
		(*corner)->Coluna = novoL;
		
	} else if( aux->idx == posColuna){
		//puts("Já ecxziste a coluna!");
	}

    
};


int VerificaCelula(Cel *navega,int posl,int posc,int valor){

	if(navega == NULL){
		return 0;
	} else{
		while( (navega != NULL) && (navega->idxL < posl) ){
			navega = navega->proxL;
		}
		if( (navega != NULL) && (navega->idxL == posl) ){
			if(navega->idxC == posc){
				navega->valor = valor;
				return 1;
			}
		} else{
			return 0;
		}

	}
	return 0;


};


void InsereCelula(mtzEspaca **corner,int linha,int coluna,int valor){

	Cabe *Cabe_Linha,*Cabe_Coluna;
	//int linha, coluna,valor;

	Cel *novo,*auxCel,*auxAntCel;

	/*
	puts("Digite a linha e coluna que deseja inserior e o valor: linha coluna valor");
	scanf("%d %d %d",&linha,&coluna,&valor);
	*/

	//verifica se o cabeçalho da linha e colunha que deseja inserir a celula estão alocados
	Cabecalho(corner,linha,coluna);
	// o cabeçalho foi verificado/alocado e voce tem certeza da existencia dele corretamente

	Cabe_Linha = (*corner)->Linha;

	while( (Cabe_Linha != NULL) && (Cabe_Linha->idx < linha) ){
		Cabe_Linha = Cabe_Linha->proxCabe;
	}
	
	if( (Cabe_Linha != NULL) && (Cabe_Linha->idx == linha) ){ 

		auxCel = Cabe_Linha->proxCel;

		if( VerificaCelula(auxCel,linha,coluna,valor) ){

		} else{
			// CRIA A NOVA CELULA PRIMEIRAMENTE PELA LINHA
			auxCel = Cabe_Linha->proxCel;
			auxAntCel = NULL;
			
			while((auxCel != NULL) && (auxCel->idxC < coluna) ){
				// caminha ate a posição da celula
				auxAntCel = auxCel;
				auxCel = auxCel->proxL;
			}

			if( (auxCel != NULL) && (auxAntCel == NULL) ){
				novo = novaCelula(valor,linha,coluna);
				novo->proxL = auxCel;
				Cabe_Linha->proxCel = novo;

			}else if(auxCel == NULL && auxAntCel != NULL ){
				novo = novaCelula(valor,linha,coluna);
				auxAntCel->proxL = novo;

			}else if(auxCel == NULL && auxAntCel == NULL ){
				novo = novaCelula(valor,linha,coluna);
				Cabe_Linha->proxCel = novo;
			}
		}
				

	} else {
		puts("PAHHNNNNN --- ERRO DE LÓGICA");
		return;
	}


	Cabe_Coluna = (*corner)->Coluna;

	while( (Cabe_Coluna != NULL ) && (Cabe_Coluna->idx < coluna) ){
		Cabe_Coluna = Cabe_Coluna->proxCabe;
	}

	if( (Cabe_Coluna != NULL ) && (Cabe_Coluna->idx == coluna) ){
		auxCel = Cabe_Coluna->proxCel;
		if( VerificaCelula(auxCel,linha,coluna,valor) ){

		} else {
			auxCel = Cabe_Coluna->proxCel;
			auxAntCel = NULL;

			while( (auxCel != NULL) && (auxCel->idxL < linha) ){
				auxAntCel = auxCel;
				auxCel = auxCel->proxC;
			}
			
			if( (auxCel != NULL) && (auxAntCel == NULL) ){
				novo->proxC = auxCel;
				Cabe_Coluna->proxCel = novo;

			}else if(auxCel == NULL && auxAntCel != NULL ){
				auxAntCel->proxC = novo;

			}else if(auxCel == NULL && auxAntCel == NULL ){
				
				Cabe_Coluna->proxCel = novo;
			}
		}
	} else{
		puts("PAHHNNN ERRO LOGICA!!!!");
	}
}


void caminhaEguarda(mtzEspaca *corner){
	FILE *arqv;
	char mov;
	int linha,coluna;
	linha = 0;
	coluna = 0;

	arqv = fopen("PassosWhiteWalker.txt","w");
 	if( arqv == NULL){
		puts("Erro na abertura do arquivo.\n");
	}
	fprintf(arqv,"(•) Posição inicial: [%d,%d]\n",linha,coluna);
	do{
		puts("Digite qual direção deseja mover-se (W,A,S,D) ");
		scanf("%c",&mov);
		scanf("%*c");
		system("clear");
		if( (mov == 'W') && (linha > 0) ){
			linha--;
			puts("cima");
			fprintf(arqv,"(↥) Posição navegação: [%d,%d]\n",linha,coluna);
			InsereCelula(&corner,linha,coluna,0);

		} else if( (mov == 'A') && (coluna > 0) ){
			coluna--;
			puts("esquerda");
			fprintf(arqv,"(↤) Posição navegação: [%d,%d]\n",linha,coluna);
			InsereCelula(&corner,linha,coluna,0);
		}else if(mov == 'S'){
			linha++;
			puts("baixo");
			fprintf(arqv,"(↧) Posição navegação: [%d,%d]\n",linha,coluna);
			InsereCelula(&corner,linha,coluna,0);
		}else if(mov == 'D'){
			coluna++;
			puts("direita");
			fprintf(arqv,"(↦) Posição navegação: [%d,%d]\n",linha,coluna);
			InsereCelula(&corner,linha,coluna,0);
		} else if(mov != 'E') {
			puts("Movimento inválido!");
			
		}
	}while(mov != 'E');
	fprintf(arqv, "(○) Fim de passeio!\n");
	fclose(arqv);
}
