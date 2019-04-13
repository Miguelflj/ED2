

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTDP 20

//estrutura para contrucao do grafo
typedef struct aresta{
	int p;
	char l;
	struct aresta *prox;
}aresta;

typedef struct vertice{
	char **mtz;
	int index;
	struct vertice *proxV;
	aresta *proxA;
}vertice;	

//estrutura para guardar todas as palavras
typedef struct Dic{
	char palavra[3];
	int ver;
	struct Dic *prox;

}Dic;


// protótipos das funcoes utilizadas

//funcoes de percursos Largura/profunidade
void Profundidade(vertice *G,char v,int *visitado,int cont,int tam,char **mtz,int k);
void percursoP(vertice *G,char v,char **mtz,int k);


//funcoes para guardar as palavras validas
Dic *CarregaLista();
Dic *insereLista(Dic *palavras,char *vet);



int BuscaPalavra(Dic *p,int pos,char v,char *palavra){
	int i;


	while( p != NULL){
		if( p->palavra[pos] == v){

			for(i = 0; i < 3; i++){
				palavra[i] = p->palavra[i];
			}
			palavra[3] = '\0';
			return 1;
		}
		p = p->prox;
	}
	return -1;

}



vertice *NovoVertice(char **mtzEst,int n){
	vertice *novo;
	int i,j;

	novo = (vertice*) malloc( sizeof(vertice) );
	novo->mtz = (char**) malloc(3 * sizeof(char*) );
	for(i = 0; i < 3; i ++){
		novo->mtz[i] = (char*) malloc( 3 * sizeof(char) );
	}

	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			novo->mtz[i][j] = mtzEst[i][j];
		}
	}
	novo->proxV = NULL;
	novo->proxA = NULL;
	novo->index = n;

	return novo;
}
int cmpPalavra(Dic *p,char *vet){
	while( p != NULL){
		if( strcmp(p->palavra,vet) == 0){
			return 1;
		}
		p = p->prox;
	}
	return 0;
}

int VerificaMTZ(Dic *p,char **mtz){
	int i,j,flag;
	char vet[3];
	flag = 1;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3;j++){
			//verifica na horizontal
			vet[j] = mtz[i][j];

		}
		if( cmpPalavra(p,vet) == 0){
			flag = 0;
		}
	}
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3;j++){
			//verifica na vertical
			vet[j] = mtz[j][i];
		}
		if( cmpPalavra(p,vet) == 0){
			flag = 0;
		}
	}

	return flag;
}

void CriaGrafo(vertice *G,int v1,int v2,char **mtzEst){

}


void ConstroiMTZ(Dic *p){
	char **mtz,vet[3],v;
	int i,j,t;
	t =0 ;
	mtz = (char**) malloc( 3 * sizeof(char*) );
	for(i = 0 ; i < 3; i++){
		mtz[i] = (char*) malloc( 3 * sizeof(char) );
	}
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			mtz[i][j] = '-';
		}
	}

	mtz[0][0] = 'p';
	mtz[0][1] = 'u';
	mtz[0][2] = 's';
	mtz[1][0] = 'o';
	mtz[1][1] = 'v';
	mtz[1][2] = 'o';
	mtz[2][0] = 's';
	mtz[2][1] = 'a';
	mtz[2][2] = 'l';
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("[%c]",mtz[i][j]);
		}
		puts("");
	}	
	t = VerificaMTZ(p,mtz);
	if( t == 0){
		puts("nao eh solucao");
	} else {
		puts("Eh soluca0");
	}
}


int main(){

	vertice *G,*auxV;
	Dic *palavras;
	char vet[3],*v;
	int i;
	palavras = NULL;
	G = NULL;
	v = "s";
	for(i = 0; i < 3; i++){
		vet[i] = '-';
	}
	palavras = CarregaLista();
	ConstroiMTZ(palavras);
	//BuscaPalavra(palavras,1,*v,vet);
	//printf("%s\n",vet);

	return 0;
}	

Dic *CarregaLista(){
	FILE *arqV;
	char a,b,c,vet[3];
	Dic *palavras;
	palavras = NULL;

	arqV = fopen("palavras.txt","r");
	if(arqV == NULL){
		puts("Erro na abertura do arquivo");
	}
	while( fscanf(arqV,"palavra( [%c,%c,%c] )\n",&a,&b,&c) != EOF ){
		//puts("0");
		vet[0] = a;
		vet[1] = b;
		vet[2] = c;
		palavras = insereLista(palavras,vet);
 	}
 	fclose(arqV);;
 	return palavras;
}

Dic *insereLista(Dic *palavras,char *vet){

	if(palavras == NULL){
		palavras = (Dic*) malloc(sizeof(Dic) );
		strcpy(palavras->palavra,vet);
		palavras->ver = 0;
		return palavras;
	} else {
		palavras->prox = insereLista(palavras->prox,vet);
	}
}



// funcoes
/*
vertice *novoVertice(char l){

	vertice *novo;

	novo = (vertice*) malloc( sizeof(vertice) );

	novo->proxV = NULL;
	novo->proxA = NULL;

	novo->contADJ = 0;

	novo->l = l;

	return novo;
}	


vertice *insereVertice(vertice *G,char l){
	vertice *aux;

	aux = G;

	if( G != NULL){
		while( ( aux->proxV != NULL ) &&  ( aux->l != l ) ){
			aux = aux->proxV;
		}
		if(aux->l != l){
			aux->proxV = novoVertice(l);	
		} else {
			//vertice ja existente
			return G;
		}
		


	} else {
		G = novoVertice(l);
	}

	return G;
}

int verificaVertice(vertice *G,char l){
	vertice *aux;

	aux = G;

	if( G != NULL){
		while( (aux != NULL) && (aux->l != l) ){
			aux = aux->proxV;
		}
		if( (aux != NULL) && (aux->l == l) ){
			return 1;

		} else {
			return -1;
		}
	}
	return -1;

}

aresta *novaAresta(char l,int p){
	aresta *nova;

	nova = (aresta*) malloc( sizeof(aresta) );
	
	nova->p = p;

	nova->l = l;

	nova->prox = NULL;

	return nova;

}



vertice *insereAresta(vertice *G,char v1,char v2,int p){

	vertice *auxV;
	aresta *auxA;
	int flag1,flag2,flagIn;
	
	
	auxV = G;

	if(G != NULL){

		flag1 = verificaVertice(G,v1);
		flag2 = verificaVertice(G,v2);
		
		if( (flag1 == 1) && (flag2 == 1) ){

			while( (auxV != NULL) && (auxV->l != v1) ){
				auxV = auxV->proxV;
			}

			if(auxV->l == v1){

				auxA = auxV->proxA;
				//printf("auxV - %c\n",auxV->l);
				if( auxA != NULL){

					while( (auxA->prox != NULL) && (auxA->l != v2) ){

						auxA = auxA->prox;

					}

					if( (auxA->prox == NULL) && (auxA->l != v2) ) {

						auxV->contADJ++;
						auxA->prox = novaAresta(v2,p);

					} else {

						// aresta já existe
					}

				} else {

					auxV->contADJ++;
					auxV->proxA = novaAresta(v2,p);

				}

			} 
		}
		return G;	
	}
}


void veGrafo(vertice *G){
	vertice *auxV;
	aresta *auxA;
	auxV = G;
	if( G != NULL){

		while( auxV != NULL){
			printf("[%c Grau:%d]->",auxV->l,auxV->contADJ);
			if(auxV->proxA != NULL){
				auxA = auxV->proxA;
				while( auxA != NULL){
					printf("(%c,%d)->",auxA->l,auxA->p);
					auxA = auxA->prox;
				}
			}
			auxV = auxV->proxV;
			puts("NULL");
		}

	}
}


int GrauVertice(vertice *G,char v){
	vertice *auxV;
	
	if( G != NULL){
		auxV = G;
		while( (auxV != NULL) && (auxV->l != v)   ){
			auxV = auxV->proxV;
		}
		if(auxV->l == v){
			return G->contADJ;

		} else {
			return -1;
		}
	}
	return -1;
}

void Vizinhanca(vertice *G,char v){
	vertice *aux_vertice;
	aresta *aux_vizinhos;

	if(G != NULL){
		aux_vertice = G;
		while( (aux_vertice != NULL) && (aux_vertice->l != v) ){
			aux_vertice = aux_vertice->proxV;
		}
		if(aux_vertice->l == v){
			if(aux_vertice->proxA != NULL){
				printf("[%c]: ",aux_vertice->l );
				aux_vizinhos = aux_vertice->proxA;
				while( aux_vizinhos != NULL){
					printf("(%c)",aux_vizinhos->l);
					aux_vizinhos = aux_vizinhos->prox;
				}
				puts("");
			}
		}
	}
}
int posV(vertice *G,char v){
	vertice *auxV;
	int pos;
	if(G != NULL){
		pos = 0;
		auxV = G;
		while( (auxV != NULL) && (auxV->l != v) ){
			pos++;
			auxV = auxV->proxV;
		}
		if( (auxV != NULL) && (auxV->l == v) ){
			return pos;
		} else {
			return -1;
		}
	}
	return -1;
}

int VeVisita(vertice *G,int *visita,char v,int tam){
	int pos;

	if( G != NULL){
		pos = posV(G,v);
		//printf("posição: %d\n", pos);
		if(visita[pos] == 0){
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
} 	

void PercursoLargura(vertice *G,char v,int *vizinhos,char partida,int tam,int cont,char *out,int contS){
	char *fila;
	int i,contF,pos; 
	vertice *auxV;
	aresta *auxA;
	fila = (char*) malloc( tam * sizeof(char) );
	if( vizinhos == NULL){
		vizinhos = (int*) malloc( tam * sizeof(int) );

		for(i = 0; i < tam; i++){
			vizinhos[i] = 0;
		}
	}
	auxV = G;
	while( (auxV != NULL) && (auxV->l != v) ){
		auxV = auxV->proxV;
	}
	
	if(auxV->l == v){
		contF = 0;
		auxA = auxV->proxA;
	
		pos = posV(G,v);
		vizinhos[pos] = 1;
		while( (auxA != NULL) ){
			if(VeVisita(G,vizinhos,auxA->l,tam) == 1 ){
				pos = posV(G,auxA->l);
				vizinhos[pos] = 1;
				//printf("[%c]",auxA->l );
				//printf("posi:(%d)",pos );
				out[contS++]  = auxA->l;

				fila[contF++] = auxA->l;

				
			}
			auxA = auxA->prox;
			
		}
		for(i = 0; i < contF; i++){
			PercursoLargura(G,fila[i],vizinhos,partida,tam,cont+1,out,contS);
		}
	}

}

void PercursoL(vertice *G,char v){
	vertice *auxV;
	int tam,i;
	char *out;
	tam = 0;

	auxV = G;
	if( G != NULL){
		while(auxV != NULL){

			auxV = auxV->proxV;
			tam++;
		}
		out = (char*) malloc( tam-1 * sizeof(char) );
		for(i =0; i < tam-1; i++){
			out[i] = '-';
		}
		printf("[%c]:",v);
		PercursoLargura(G,v,NULL,v,tam,1,out,0);
		for(i =0; i < tam-1; i++){
			if(out[i] != '-'){
				//percursoP(G,out[i]);
				printf("[%c]",out[i]);	
			}
			
		}
		puts("");
	}
}
void Profundidade(vertice *G,char v,int *visitado,int cont,int tam,char **mtz,int k){
	int pos;
	vertice *auxV;
	aresta *auxA;
	int j = 1;
	pos = posV(G,v);
	visitado[pos] = cont;

	auxV = G;
	while( (auxV != NULL) && (auxV->l != v) ){
		auxV = auxV->proxV;
	}
	if(auxV->l == v){
		auxA = auxV->proxA;
		while(auxA != NULL){
			if(VeVisita(G,visitado,auxA->l,tam) == 1){
				if(j < 3){
					mtz[j++][k] = auxA->l;
					Profundidade(G,auxA->l,visitado,cont+1,tam,mtz,k);

				}
				
			}
			
			auxA = auxA->prox;
		}
	}
}



void percursoP(vertice *G,char v,char **mtz,int k){

	int *visitado,cont,i;
	vertice *auxV;
	int tam;
	tam = 0;

	auxV = G;
	if( G != NULL){
		while(auxV != NULL){

			auxV = auxV->proxV;
			tam++;
		}
	}
	visitado = (int*) malloc( tam * sizeof(int) );
	for(i = 0; i < tam; i++){
		visitado[i] = 0;
	}
	cont = 1;
	Profundidade(G,v,visitado,cont,tam,mtz,k);
	puts("");
} 
*/