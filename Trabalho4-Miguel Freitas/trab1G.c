/* UFMT - ED2 - TRABALHO 4 - GRAFOS
 LISTA ENCADEADA
 MIGUEL FREITAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct aresta{
	// peso da aresta
	int peso;
	//indexação do vertice vizinho
	int ind;
	//ponteiros
	struct aresta *nxAresta;
}aresta;

typedef struct vertice{
	//indexação dos vertices
	int ind;
	//variavel que conta quantos vizinhos tem o vertice
	int contVz;
	//ponteiros
	struct vertice *nxVertice;
	aresta *nxAresta;
}vertice;


//protótipos
vertice *novoVertice(int ind);
vertice *insereVertice(vertice *G,int ind); //funcao (a)
aresta *novaAresta(int ind,int peso);
vertice *insereAresta(vertice *G,int v1,int v2,int peso); //funcao (b)
vertice *posicionaVizinhos(vertice *G,int v1,int v2,int peso);
int buscaVertice(vertice *G, int ind); //funcao (d)
vertice *CarregaGrafo();
void veGrafo(vertice *G);
void VizinhoVertice(vertice *G,int ind); // funcao (e)
int GrauVertice(vertice *G,int ind); // funcao (f)
vertice *RemoveAresta(vertice *G,int v1,int v2);
vertice *RemoveA(vertice *G,int v1,int v2);
void RemoveVertice(vertice *G,vertice *vertice,aresta *vizinho);
vertice *RemoveV(vertice *G,int v); // funcao (c)
int posV(vertice *G,int v);
int VeVisita(vertice *G,int *visita,int v,int tam);
void PercursoLargura(vertice *G,int v,int *vizinhos,int partida,int tam);
void PercursoL(vertice *G,int v); // funcao (g)
void Profundidade(vertice *G,int v,int *visitado,int cont,int tam);
void percursoP(vertice *G,int v); // funcao (h)





int main(){

	//Declara grafo G 
	vertice *G,*aux;
	G = NULL;
	int maior,indV;
	clock_t Ticks[2];
	Ticks[0] = clock();
	G = CarregaGrafo();
	aux = G;
	maior = aux->contVz;
	indV = 1;
	while( aux != NULL){
		if(maior < aux->contVz){
			maior = aux->contVz;
			indV = aux->ind;
		}
		aux = aux->nxVertice;
	}

	PercursoL(G,1);
	percursoP(G,1);
	puts("");
	printf("%d %d\n",indV,maior);
	Ticks[1] = clock();
	double Tempo =( (Ticks[1] - Ticks[0]) * 1000.0 );
	printf("\n\nTempo Gasto: %g\n",Tempo);

	return 0;
}


//funcoes


// funcoes de insercao dos vertices

vertice *novoVertice(int ind){

	vertice *novo;

	novo = (vertice*) malloc( sizeof(vertice) );

	novo->nxVertice = NULL;
	novo->nxAresta = NULL;

	novo->contVz = 0;

	novo->ind  = ind;

	return novo;
}	



vertice *insereVertice(vertice *G,int ind){
	vertice *aux;

	aux = G;

	if( G != NULL){
		while( ( aux->nxVertice != NULL ) &&  ( aux->ind != ind ) ){
			aux = aux->nxVertice;
		}
		if(aux->ind != ind){
			aux->nxVertice = novoVertice(ind);	
		} else {
			//vertice ja existente
			return G;
		}
		

	} else {
		G = novoVertice(ind);
	}

	return G;
}


// funcoes de insercao das arestas
int buscaVertice(vertice *G, int ind){
	vertice *aux;
	aux = G;
	while( (aux != NULL) && (aux->ind != ind) ){
		aux = aux->nxVertice;
	}

	if( aux != NULL){
		if(aux->ind == ind){
			return 1;
		} else{
			return -1;
		}
	} else {
		return -1;
	}
}

aresta *novaAresta(int ind,int peso){
	aresta *nova;

	nova = (aresta*) malloc( sizeof(aresta) );
	
	nova->peso = peso;

	nova->ind = ind;

	nova->nxAresta = NULL;

	return nova;

}

vertice *posicionaVizinhos(vertice *G,int v1,int v2,int peso){
	vertice *auxVt;
	aresta  *auxAr;

	auxVt = G;
	while ( (auxVt->nxVertice != NULL) && (auxVt->ind != v1 ) ){
		auxVt = auxVt->nxVertice;
	}
	if(auxVt->ind == v1){

		auxAr = auxVt->nxAresta;
		
		if(auxAr != NULL){

			while( (auxAr->nxAresta != NULL) && (auxAr->ind != v2) ){
				auxAr = auxAr->nxAresta;
			}
			if( auxAr->ind != v2){
				auxAr->nxAresta = novaAresta(v2,peso);
				auxVt->contVz++;
			}else {
				// aresta já existente
			}
		} else {
			
			auxVt->nxAresta = novaAresta(v2,peso);
			auxVt->contVz++;
		}
	}
	return G;
}

vertice *insereAresta(vertice *G,int v1,int v2,int peso){
	int flag1,flag2;
	if( G != NULL){
		
		flag1 = buscaVertice(G,v1);
		
		flag2 = buscaVertice(G,v2);
		if( (flag1 == 1) && (flag2 == 1) ){
			if( v1 != v2){
				G = posicionaVizinhos(G,v1,v2,peso);
				G = posicionaVizinhos(G,v2,v1,peso);
			}
			
		} else {
			// vertice v1 ou v2 nao inseridos	
		}
	}

	return G;
}

vertice *CarregaGrafo(){
	vertice *G;
	G = NULL;
	FILE *arq;
	int flag,v1,v2,p,j,i,tam;
	char entrada[10],entradaV2[10],peso[1];

	arq = fopen("Arq[0][5000].txt","r");
	if( arq == NULL){
		puts("Falha na abertura do arquivo");
		return NULL;
	}
	
	fscanf(arq,"%s",entrada);
	printf("%s\n",entrada);
	flag = 1;
	while( flag == 1){
		fscanf(arq,"%s",entrada);
		if( strcmp(entrada,"#arestas#") == 0){
			flag = 0;
		} else {
			
			v1 = atoi(entrada);
			//printf("%d\n",v1);
			G = insereVertice(G,v1);
		}
		
	}
	puts("Carregou vertices...");
	puts("#arestas#");
	while( fscanf(arq,"%d %d %d",&v1,&v2,&p) != EOF ){

		G = insereAresta(G,v1,v2,p);
		//printf("%d %d %d\n",v1,v2,p);
		//puts("inserindo...");
		//pr//intf("v1 %d",v1 );
		//printf("v2 %d",v2 );
		//printf("p %d",p );
	}
	puts("Carregou arestas...");
	puts("Carregou Grafo!!!");
	fclose(arq);
	return G;
}

void veGrafo(vertice *G){
	vertice *auxV;
	aresta *auxA;
	auxV = G;
	if( G != NULL){

		while( auxV != NULL){
			printf("[%d Grau:%d]->",auxV->ind,auxV->contVz);
			if(auxV->nxAresta != NULL){
				auxA = auxV->nxAresta;
				while( auxA != NULL){
					printf("(%d)->",auxA->ind);
					auxA = auxA->nxAresta;
				}
			}
			auxV = auxV->nxVertice;
			puts("NULL");
		}

	}
}

void VizinhoVertice(vertice *G,int ind){
	vertice *auxVertice;
	aresta *auxAresta;
	auxVertice = G;
	if( auxVertice != NULL){
		while( (auxVertice->nxVertice != NULL) && (auxVertice->ind != ind) ){

			auxVertice = auxVertice->nxVertice;
		}
		if( auxVertice->ind == ind){
			printf("[%d Grau:%d]->",auxVertice->ind,auxVertice->contVz);
			auxAresta = auxVertice->nxAresta;
			while( auxAresta != NULL ){
				printf("(%d)->",auxAresta->ind);
				auxAresta = auxAresta->nxAresta;
			}
			puts("NULL");
		}
	} else {
		//grafo nullo
	}
}

int GrauVertice(vertice *G,int ind){
	vertice *auxVertice;
	auxVertice = G;
	if( auxVertice != NULL){
		while( (auxVertice->nxVertice != NULL) && (auxVertice->ind != ind) ){

			auxVertice = auxVertice->nxVertice;
		}
		if( auxVertice->ind == ind){
			return auxVertice->contVz;
		} else {
			return -1;
			//vertice nao existe
		}
	} 
	return -1;

}

vertice *RemoveAresta(vertice *G,int v1,int v2){
	vertice *auxV;
	aresta *auxA,*sent;


	if( G != NULL){
		auxV = G;
		while( (auxV != NULL) && (auxV->ind != v1) ){
			auxV = auxV->nxVertice;
		}
		if(auxV->ind == v1){
			auxV->contVz--;
			auxA = auxV->nxAresta;
			if(auxA != NULL){
				sent = NULL;
				while( (auxA != NULL) && (auxA->ind != v2) ){
					sent = auxA;
					auxA = auxA->nxAresta;
				}
				if(  (auxA->ind == v2) && (sent != NULL) ){
					sent->nxAresta = auxA->nxAresta;
					free(auxA);
					return G;
				} else if( auxA->ind == v2) {
					auxV->nxAresta = auxA->nxAresta;
					free(auxA);
					return G;
				}
			}
		}
	}
}

vertice *RemoveA(vertice *G,int v1,int v2){
	int flag1,flag2;

	flag1 = buscaVertice(G,v1);
	flag2 = buscaVertice(G,v2);

	if( (flag1 == 1) && (flag2 == 1) ){
		G = RemoveAresta(G,v1,v2);
		G = RemoveAresta(G,v2,v1);
		return G;
	}
	// nao é possivel remover, aresta nao existente
}

void RemoveVertice(vertice *G,vertice *vertice,aresta *vizinho){
	if(vizinho->nxAresta != NULL){
		RemoveVertice(G,vertice,vizinho->nxAresta);
		RemoveAresta(G,vizinho->ind,vertice->ind);
		free(vizinho);
	} else {
		RemoveAresta(G,vizinho->ind,vertice->ind);
		free(vizinho);
	}
}


vertice *RemoveV(vertice *G,int v){
	vertice *auxV,*sent;
 	aresta *auxA;
	int ind;
 	int flag;
 	if(G != NULL){
 		flag = buscaVertice(G,v);
 		if( flag){

 			auxV = G;
 			sent = NULL;
 			while( (auxV != NULL) &&  (auxV->ind != v)   ){
 				sent = auxV;
 				auxV = auxV->nxVertice;
 			}

 			if(auxV->ind == v){
 				if(auxV->nxAresta != NULL){
 					RemoveVertice(G,auxV,auxV->nxAresta);
 					if(sent != NULL){
 						sent->nxVertice = auxV->nxVertice;
 					} else {
 						G  = auxV->nxVertice;
 					}	
 					free(auxV);
 					return G;
 				} else {
 					if( sent != NULL){
 						sent->nxVertice = auxV->nxVertice;	
 					} else{
 						G->nxVertice = auxV->nxVertice;
 					}
 					free(auxV);
 					return G;
 					
 				}
 			}
 		}
 	}
}

// auxilia nos percursos
int posV(vertice *G,int v){
	vertice *auxV;
	int pos;
	if(G != NULL){
		pos = 0;
		auxV = G;
		while( (auxV != NULL) && (auxV->ind != v) ){
			pos++;
			auxV = auxV->nxVertice;
		}
		if( (auxV != NULL) && (auxV->ind == v) ){
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

void PercursoLargura(vertice *G,int v,int *vizinhos,int partida,int tam){
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
	while( (auxV != NULL) && (auxV->ind != v) ){
		auxV = auxV->nxVertice;
	}
	
	if(auxV->ind == v){
		contF = 0;
		auxA = auxV->nxAresta;
	
		pos = posV(G,v);

		vizinhos[pos] = 1;

		while( (auxA != NULL) ){
			if(VeVisita(G,vizinhos,auxA->ind,tam) == 1 ){
				pos = posV(G,auxA->ind);
				vizinhos[pos] = 1;
				//printf("[%c]",auxA->l );
				//printf("posi:(%d)",pos );
				printf("[%d]",auxA->ind );
				fila[contF++] = auxA->ind;

				
			}
			auxA = auxA->nxAresta;
			
		}
		for(i = 0; i < contF; i++){
			PercursoLargura(G,fila[i],vizinhos,partida,tam);
		}
	}

}



void PercursoL(vertice *G,int v){
	vertice *auxV;
	int tam,pos;

	tam = 0;
	pos = buscaVertice(G,v);
	if( pos != -1){
		auxV = G;
		if( G != NULL){
			while(auxV != NULL){

				auxV = auxV->nxVertice;
				tam++;
			}
			printf("[%d]:",v);
			PercursoLargura(G,v,NULL,v,tam);
			puts("");

		}
	}
}

void Profundidade(vertice *G,int v,int *visitado,int cont,int tam){
	int pos;
	vertice *auxV;
	aresta *auxA;

	pos = posV(G,v);
	visitado[pos] = cont;

	auxV = G;
	while( (auxV != NULL) && (auxV->ind != v) ){
		auxV = auxV->nxVertice;
	}
	if(auxV->ind == v){
		auxA = auxV->nxAresta;
		while(auxA != NULL){
			if(VeVisita(G,visitado,auxA->ind,tam) == 1){
				Profundidade(G,auxA->ind,visitado,cont+1,tam);
			}
			auxA = auxA->nxAresta;
		}
	}
}



void percursoP(vertice *G,int v){
	int *visitado,cont,i;
	vertice *auxV;
	int tam;

	tam = 0;

	auxV = G;
	if( G != NULL){
		while(auxV != NULL){

			auxV = auxV->nxVertice;
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
		//printf("(%d = %d) ",auxV->ind,visitado[i]);
		auxV = auxV->nxVertice;
	}
	puts("");

} 
