
/*

		Matrizes Esparças

*/


#include <stdio.h>
#include <stdlib.h>




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

// Protótipos das funções
void InicializaCorner(mtzEspaca **corner);
Cabe *novoCabecalho(int pos);
void Cabecalho(mtzEspaca **corner,int posLinha,int PosColuna);
Cel *novaCelula(int valor,int posL,int posC);
void imprime(mtzEspaca **corner);
void InsereCelula(mtzEspaca **corner,int linha,int coluna,int valor);
int VerificaCelula(Cel *navega,int posl,int posc,int valor);
void Menuzin(mtzEspaca *corner,int op);
Cel *BuscaCelula(mtzEspaca *corner);


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
		novoL = novoCabecalho(posLinha);
		novoL->proxCabe = aux;
		(*corner)->Linha = novoL;	

	} else if( (aux == NULL ) && ( auxAnt != NULL ) && (auxAnt->idx != posLinha) ){
		novoL = novoCabecalho(posLinha);
		auxAnt->proxCabe = novoL;

	}	else if( (aux != NULL) && (auxAnt != NULL) && (aux->idx != posLinha) && auxAnt->idx != posLinha) {
		novoL = novoCabecalho(posLinha);
		novoL->proxCabe = aux;
		auxAnt->proxCabe = novoL;
	} else if(aux == NULL && auxAnt == NULL) {
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
void imprime(mtzEspaca **corner){
	Cabe *auxL,*auxC;

	Cel *auxCelL,*auxCelC;
	auxL = (*corner)->Linha;
	auxC = (*corner)->Coluna;

	while( auxL != NULL){
		printf("Linha: %d\n",auxL->idx);
		auxCelL = auxL->proxCel;

		while(auxCelL != NULL){

			printf("valor: %d  posC: %d\n",auxCelL->valor,auxCelL->idxC);
			auxCelL = auxCelL->proxL;

		}
		auxL = auxL->proxCabe;
	}
	while(auxC != NULL){
		printf("Coluna: %d\n",auxC->idx);
		auxCelC = auxC->proxCel;
		while(auxCelC != NULL){
			printf("valor: %d  posL: %d\n",auxCelC->valor,auxCelC->idxL);
			auxCelC = auxCelC->proxC;
		}
		auxC = auxC->proxCabe;
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




 Cel *BuscaCelula(mtzEspaca *corner){
	Cabe *Cabe_Linha;
	Cel *aux_linha;
	int linha,coluna;
	puts("Digite a linha e coluna que deseja buscar");
	scanf("%d %d",&linha,&coluna);
	Cabe_Linha = corner->Linha;

	while( (Cabe_Linha != NULL) && (Cabe_Linha->idx < linha) ) {
		Cabe_Linha = Cabe_Linha->proxCabe;
	}
	if( (Cabe_Linha != NULL) && Cabe_Linha->idx == linha){
		aux_linha = Cabe_Linha->proxCel;
		while((aux_linha != NULL) && (aux_linha->idxC < coluna) ){
			aux_linha = aux_linha->proxL;
		}
		if(aux_linha != NULL && aux_linha->idxL == linha && aux_linha->idxC == coluna){
			return aux_linha;
		}
		return NULL;

	} else{
		return NULL;
	}

	
}
void Menuzin(mtzEspaca *corner,int op){
	FILE *arqv;
	int linha,coluna,valor;
	Cel *busca;
    system("clear");
    switch(op){
        case 1:
       		arqv = fopen("Celulas.txt","r");
   		 	if( arqv == NULL){
        		puts("Erro na abertura do arquivo.\n");
    		}
    		while(fscanf(arqv,"%d %d %d",&linha,&coluna,&valor) != EOF){
                InsereCelula(&corner,linha,coluna,valor);
            }
            fclose(arqv);
            puts("Carregado com sucesso");
            break;
        case 2:
       		busca = BuscaCelula(corner);
            if(busca != NULL){
				printf("valor: %d\n",busca->valor);
			} else {
				puts("Célula noEcxziste!");
			}
            
            break;
        case 3:
        	imprime(&corner);
        	break;
        default:
            break;
    
    }


};



int main(){

	mtzEspaca *corner;
	Cel *busca;
	int op;


	InicializaCorner(&corner);

	do{

		puts("Digite a opção:\n 1-Carrega tabela\n 2-Buscar\n 0-Sair");
	    scanf("%d", &op);
		Menuzin(corner,op);
	}while(op != 0);
	
	
	return 0;
}