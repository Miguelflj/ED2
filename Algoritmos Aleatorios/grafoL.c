/*
	UFMT -CCOMP -ESTRUTURA DE DADOS 2
	PROFESSOR: IVAIRTON
	TRABALHO 4 - GRAFOS (MATRIZ DE ADJACÊNCIA) E (LISTA ENCADEADA)
	MIGUEL FREITAS

*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct aresta{

	int peso;
	int v;
	struct aresta *prox;

}aresta;


typedef struct vertice{

	int contADJ;
	struct vertice *proxV;
	aresta *proxA;
	int v;

}vertice;	


vertice *novoVertice(int v){

	vertice *novo;

	novo = (vertice*) malloc( sizeof(vertice) );

	novo->proxV = NULL;
	novo->proxA = NULL;

	novo->contADJ = 0;

	novo->v = v;

	return novo;
}	

vertice *insereVertice(vertice *G,int v){
	vertice *aux;

	aux = G;

	if( G != NULL){
		while( ( aux->proxV != NULL ) &&  ( aux->v != v ) ){
			aux = aux->proxV;
		}
		if(aux->v != v){
			aux->proxV = novoVertice(v);	
		} else {
			//vertice ja existente
			return G;
		}
		


	} else {
		G = novoVertice(v);
	}

	return G;
}



int verificaVertice(vertice *G,int v){
	vertice *aux;

	aux = G;

	if( G != NULL){
		while( (aux != NULL) && (aux->v != v) ){
			aux = aux->proxV;
		}
		if( (aux != NULL) && (aux->v == v) ){
			return 1;

		} else {
			return -1;
		}
	}
	return -1;
}

aresta *novaAresta(int v,int p){
	aresta *nova;

	nova = (aresta*) malloc( sizeof(aresta) );
	//peso da aresta
	nova->peso = p;

	nova->v = v;

	nova->prox = NULL;

	return nova;
}

vertice *insereAresta(vertice *G,int v1,int v2,int p){

	vertice *auxV;
	aresta *auxA;
	int flag1,flag2,flagIn;
	
	auxV = G;

	if(G != NULL){

		flag1 = verificaVertice(G,v1);
		flag2 = verificaVertice(G,v2);

		if( (flag1 == 1) && (flag2 == 1) ){

			while( auxV != NULL){

				flagIn = 0;

				if( auxV->v == v1 ){

					auxA = auxV->proxA;
					if(auxA != NULL){

						while( (auxA->prox != NULL) && (auxA->v != v2) ){
							auxA = auxA->prox;
						}
						if(auxA->v != v2){

							flagIn = 1;
							auxA->prox = novaAresta(v2,p);

						} else {
							// aresta ja existente
						}

					} else {
						flagIn = 1;
						auxV->proxA = novaAresta(v2,p);
					}

				}

				if(auxV->v == v2){

					auxA = auxV->proxA;
					if(auxA != NULL){

						while( (auxA->prox != NULL) && (auxA->v != v1) ){
							auxA = auxA->prox;
						}

						if(auxA->v != v1){
							flagIn = 1;
							//puts("test");
							auxA->prox = novaAresta(v1,p);
						} else {
							// aresta ja existente
						}

					} else{
						flagIn = 1;
						auxV->proxA = novaAresta(v1,p);
					}

				}
				if(flagIn){
					auxV->contADJ++;
				}
				auxV = auxV->proxV;
			}

			return G;


		} else {
			//um dos vertices não existem
		}

	} else {
		// grafo nao existe

	}
}

void veGrafo(vertice *G){
	vertice *auxV;
	aresta *auxA;
	auxV = G;
	if( G != NULL){

		while( auxV != NULL){
			printf("[%d Grau:%d]->",auxV->v,auxV->contADJ);
			if(auxV->proxA != NULL){
				auxA = auxV->proxA;
				while( auxA != NULL){
					printf("(%d)->",auxA->v);
					auxA = auxA->prox;
				}
			}
			auxV = auxV->proxV;
			puts("NULL");
		}

	}
}

vertice *carregaGrafo(){
	vertice *G;
	FILE *fileG;
	char entrada[10];
	
	fileG = fopen("entrada.txt","r");
	if(fileG == NULL){
		puts("Erro na abertura do arquivo");
	}
	fscanf(fileG,"%c",&tam);
	
	
}

vertice *RemoveAresta(vertice *G,int v1,int v2){
	vertice *auxV;
	aresta *auxA,*sent;


	if( G != NULL){
		auxV = G;
		while( (auxV != NULL) && (auxV->v != v1) ){
			auxV = auxV->proxV;
		}
		if(auxV->v == v1){
			auxV->contADJ--;
			auxA = auxV->proxA;
			if(auxA != NULL){
				sent = NULL;
				while( (auxA != NULL) && (auxA->v != v2) ){
					sent = auxA;
					auxA = auxA->prox;
				}
				if(  (auxA->v == v2) && (sent != NULL) ){
					sent->prox = auxA->prox;
					free(auxA);
					return G;
				} else if( auxA->v == v2) {
					auxV->proxA = auxA->prox;
					free(auxA);
					return G;
				}
			}
		}
	}
}

vertice *RemoveA(vertice *G,int v1,int v2){
	int flag1,flag2;

	flag1 = verificaVertice(G,v1);
	flag2 = verificaVertice(G,v2);

	if( (flag1 == 1) && (flag2 == 1) ){
		G = RemoveAresta(G,v1,v2);
		G = RemoveAresta(G,v2,v1);
		return G;
	}
	// nao é possivel remover, aresta nao existente
}

void RemoveVertice(vertice *G,vertice *vertice,aresta *vizinho){
	if(vizinho->prox != NULL){
		RemoveVertice(G,vertice,vizinho->prox);
		RemoveAresta(G,vizinho->v,vertice->v);
		free(vizinho);
	} else {
		RemoveAresta(G,vizinho->v,vertice->v);
		free(vizinho);
	}
}

vertice *RemoveV(vertice *G,int v){
	vertice *auxV,*sent;
 	aresta *auxA;
 	int flag;

 	if(G != NULL){
 		flag = verificaVertice(G,v);
 		if( flag){

 			auxV = G;
 			sent = NULL;
 			while( (auxV != NULL) &&  (auxV->v != v)   ){
 				sent = auxV;
 				auxV = auxV->proxV;
 			}

 			if(auxV->v == v){
 				if(auxV->proxA != NULL){
 					RemoveVertice(G,auxV,auxV->proxA);
 					if(sent != NULL){
 						sent->proxV = auxV->proxV;
 					} else {
 						G->proxV = auxV->proxV;
 					}	
 					free(auxV);
 					return G;
 				} else {
 					if( sent != NULL){
 						sent->proxV = auxV->proxV;	
 					} else{
 						G->proxV = auxV->proxV;
 					}
 					free(auxV);
 					return G;
 					
 				}
 				
 			}
 		}
 	}
}


int GrauVertice(vertice *G,int v){
	vertice *auxV;
	
	if( G != NULL){
		auxV = G;
		while( (auxV != NULL) && (auxV->v != v)   ){
			auxV = auxV->proxV;
		}
		if(auxV->v == v){
			return G->contADJ;

		} else {
			return -1;
		}
	}
	return -1;
}

void Vizinhanca(vertice *G,int v){
	vertice *aux_vertice;
	aresta *aux_vizinhos;

	if(G != NULL){
		aux_vertice = G;
		while( (aux_vertice != NULL) && (aux_vertice->v != v) ){
			aux_vertice = aux_vertice->proxV;
		}
		if(aux_vertice->v == v){
			if(aux_vertice->proxA != NULL){
				printf("[%d]: ",aux_vertice->v );
				aux_vizinhos = aux_vertice->proxA;
				while( aux_vizinhos != NULL){
					printf("(%d)",aux_vizinhos->v);
					aux_vizinhos = aux_vizinhos->prox;
				}
				puts("");
			}
		}
	}
}
int posV(vertice *G,int v){
	vertice *auxV;
	int pos;
	if(G != NULL){
		pos = 0;
		auxV = G;
		while( (auxV != NULL) && (auxV->v != v) ){
			pos++;
			auxV = auxV->proxV;
		}
		if( (auxV != NULL) && (auxV->v == v) ){
			return pos;
		} else {
			return -1;
		}
	}
	return -1;
}

int VeVisita(vertice *G,int *visita,int v,int tam){
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

/*
void PercursoLargura(vertice *G,int v,int *vizinhos,char partida,int tam){
	int *fila;
	int i,contF,pos; 
	vertice *auxV;
	aresta *auxA;
	fila = (int*) malloc( tam * sizeof(int) );
	if( vizinhos == NULL){
		vizinhos = (int*) malloc( tam * sizeof(int) );

		for(i = 0; i < tam; i++){
			vizinhos[i] = 0;
		}
	}
	auxV = G;
	while( (auxV != NULL) && (auxV->v != v) ){
		auxV = auxV->proxV;
	}
	
	if(auxV->v == v){
		contF = 0;
		auxA = auxV->proxA;
	
		pos = posV(G,v);
		vizinhos[pos] = 1;
		while( (auxA != NULL) ){
			if(VeVisita(G,vizinhos,auxA->v,tam) == 1 ){
				pos = posV(G,auxA->v);
				vizinhos[pos] = 1;
				//printf("[%c]",auxA->l );
				//printf("posi:(%d)",pos );
				printf("[%d]",auxA->v );
				fila[contF++] = auxA->v;

				
			}
			auxA = auxA->prox;
			
		}
		for(i = 0; i < contF; i++){
			PercursoLargura(G,fila[i],vizinhos,partida,tam);
		}
	}

}



void PercursoL(vertice *G,char v){
	vertice *auxV;
	int tam;

	tam = 0;

	auxV = G;
	if( G != NULL){
		while(auxV != NULL){

			auxV = auxV->proxV;
			tam++;
		}
		printf("[%c]:",v);
		PercursoLargura(G,v,NULL,v,tam);
		puts("");

	}
}
void Profundidade(vertice *G,char v,int *visitado,int cont,int tam){
	int pos;
	vertice *auxV;
	aresta *auxA;

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
				Profundidade(G,auxA->l,visitado,cont+1,tam);
			}
			
			auxA = auxA->prox;
		}
	}
}



void percursoP(vertice *G,char v){
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
	Profundidade(G,v,visitado,cont,tam);
	auxV = G;
	for(i = 0; i < tam; i++){
		printf("(%c = %d) ",auxV->l,visitado[i]);
		auxV = auxV->proxV;
	}
	puts("");

} 
*/

int main(){
	vertice *G;
	int grau;
	char *v1,*v2;
	G = NULL;
	G = carregaGrafo();
	veGrafo(G);
	puts("");
	v1 = "e";
	v2 = "a";
	//G = RemoveV(G,*v1);
	//veGrafo(G);
	//Vizinhanca(G,*v2);
	// grau = GrauVertice(G,*v2);
	// printf("Vertice:%c Grau:%d\n",*v2,grau);
	return 0;
}	