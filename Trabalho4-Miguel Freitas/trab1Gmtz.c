/* UFMT - ED2 - TRABALHO 4 - GRAFOS
 MATRIZ DE ADJCÊNCIA
 MIGUEL FREITAS
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct tipoGrafo{
	int contV;
	int max;
	int *vertices;
	int **arestas;
}tipoGrafo;

//protótipos das funcoes
int contaV();
tipoGrafo *inicializaGrafo(int n);
int insereVertice(tipoGrafo *G,int ind); //funcao (a)
int buscaVertice(tipoGrafo *G,int ind); // funcao (d)
void insereAresta(tipoGrafo *G,int v1,int v2,int peso); // funcao (b) 
void CarregaGrafo(tipoGrafo *G);
void imprime(tipoGrafo *G);
int veVisita(tipoGrafo *G,int ind,int *visitado);
void Largura(tipoGrafo *G,int ind,int *visitado,int partida);
void percursoLargura(tipoGrafo *G,int ind); //funcao (g)
void Profundidade(tipoGrafo *G,int ind, int *visitado,int cont);
void percursoProfundidade(tipoGrafo *G,int ind); // funcao (h)
int GrauVertice(tipoGrafo *G,int ind); // funcao (f)
void removeVertice(tipoGrafo *G,int ind); // funcao (c)
void vizinhosVertice(tipoGrafo *G,int ind); // funcao (e)
int VerticeMaiorGrau(tipoGrafo *G);



int main(){

	int tam,i,j,ex;
	tipoGrafo *G;
	G = NULL;
	tam = contaV();
	//tam = 5000;
	clock_t Ticks[2];

	Ticks[0] = clock();
	G = inicializaGrafo(tam);
	CarregaGrafo(G);
	percursoLargura(G,1);
	percursoProfundidade(G,1);
	VerticeMaiorGrau(G);
	puts("");
	Ticks[1] = clock();

	double Tempo =( (Ticks[1] - Ticks[0]) * 1000.0 );
	printf("\n\nTempo Gasto: %g\n",Tempo);


	return 0;
}

//funcoes
int contaV(){
	FILE *arq;
	int flag,v1,v2,p,j,i,tam;
	char entrada[10];
	// precisa alterar o nome do arquivo para contar a quantia dos verteces (trocar na funcao CarregaGrafo() tbm)
	arq = fopen("Arq[0][5000].txt","r");
	if( arq == NULL){
		puts("Falha na abertura do arquivo");
		return 0;
	}
	
	fscanf(arq,"%s",entrada);
	//printf("%s\n",entrada);
	flag = 1;
	tam = 0;
	while( flag == 1){
		fscanf(arq,"%s",entrada);
		if( strcmp(entrada,"#arestas#") == 0){
			flag = 0;
		} else {
			printf("%s\n",entrada);
			tam++;
		}
	}
	//printf("%d\n",tam);
	fclose(arq);
	return tam;	
}


tipoGrafo *inicializaGrafo(int n){
	int i, j;
	tipoGrafo *G;
	G = (tipoGrafo*) malloc( sizeof(tipoGrafo) );
	G->contV = 0;
	G->max = n;
	G->vertices = (int*) malloc( n * sizeof(int) );
	G->arestas = (int**) malloc( n * sizeof(int*) );
	for(i = 0; i < n; i++){
		G->arestas[i] = (int*) malloc( n * sizeof(int) );

	};
	for(i = 0; i < n; i++){
		for(i = j; j < n; j++){
			G->arestas[i][j] = 0;
		}
	}

	return G;
}

int insereVertice(tipoGrafo *G,int ind){
	int i, flag,pos;
	if(G->contV <= G->max){

		flag  = 0;

		for(i = 0; i < G->contV; i++){

			if(G->vertices[i] == ind){
				//vertice ja inserido
				flag = 1;
			}
			if(G->vertices[i] == -1){
				//insere em posição que foi removido
				pos = i;
				flag = 2;
			}

		}
		if( flag == 0){
			G->vertices[i] = ind;
			G->contV++;
			return 1;
		} else if( flag == 2){
			G->vertices[pos] = ind;
			G->contV++;
			return 1;
		} else {
			puts("Vertice já existente no seu grafo");
			return 0;
		}
	}
}
int buscaVertice(tipoGrafo *G,int ind){
	int i;
	for(i = 0; i < G->contV; i++){
		if(G->vertices[i] == ind){
			return i;
		}
	}
	return -1;
}


void insereAresta(tipoGrafo *G,int v1,int v2,int peso){
	int pos1,pos2,aux;

	pos1 = buscaVertice(G,v1);
	pos2 = buscaVertice(G,v2);

	if( ( pos1 > -1)  && (pos2 > -1) ){
 		if(pos2 < pos1){
 			
 			aux = pos2;
 			pos2 = pos1;
 			pos1 = aux;
 		};

 		G->arestas[pos1][pos2] = peso;

	} else {
		//printf("%d %d\n",pos1,pos2);
		printf("(%d %d) - Algum ou os dois vértices não existem\n",v1,v2);

	}

}

void CarregaGrafo(tipoGrafo *G){
	
	FILE *arq;
	int flag,v1,v2,p,j,i,tam;
	char entrada[10],entradaV2[10],peso[1];

	//abre arquivo para leitura
	arq = fopen("Arq[0][5000].txt","r");
	if( arq == NULL){
		puts("Falha na abertura do arquivo");
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
			insereVertice(G,v1);
		}
		
	}
	puts("Carregou vertices...");
	puts("#arestas#");
	while( fscanf(arq,"%d %d %d",&v1,&v2,&p) != EOF ){

		insereAresta(G,v1,v2,p);
		//printf("%d %d %d\n",v1,v2,p);
		//puts("inserindo...");
		//printf("v1 %d",v1 );
		//printf("v2 %d",v2 );
		//printf("p %d",p );
	}
	puts("Carregou arestas...");
	puts("Carregou Grafo!!!");

	fclose(arq);
}

void imprime(tipoGrafo *G){
	int i,j;
	
	if(G != NULL){
		for(i = 0; i < G->contV; i++){
			if( G->vertices[i] != -1){

				printf("[%d]->",G->vertices[i] );
				for(j = 0; j < G->contV; j++){
					if(j < i){
						if(G->arestas[j][i] != 0){
							printf("(%d)->",G->vertices[j]);
						}
					} else {
						if(G->arestas[i][j] != 0){
							printf("(%d)->",G->vertices[j]);
						}
					}
					
				}
				puts("NULL");
			}
		}
	}
}

int veVisita(tipoGrafo *G,int ind,int *visitado){
	int pos;
	pos = buscaVertice(G,ind);
	if(visitado[pos] == 0){
		return 1;
	} else {
		return 0;
	}

}


void Largura(tipoGrafo *G,int ind,int *visitado,int partida){
	int i,pos,posAux,contF;

	int *fila;
	contF = 0;

	fila = (int*) malloc( G->contV * sizeof(int) );

	if( visitado == NULL){
		visitado = (int*) malloc( G->contV * sizeof(int) );
		
		for( i = 0; i < G->contV; i++){
			visitado[i] = 0;
	 	}
	}


	pos = buscaVertice(G,ind);
	visitado[pos] = 1;

	for(i = 0; i < G->contV; i++){
		if(i < pos){
	 		if( G->arestas[i][pos] != 0 ){
	 			//puts("passou ?");
	 			if( veVisita(G,G->vertices[i],visitado) ){

	 				printf("[%d]",G->vertices[i]);
	 				fila[contF++] = G->vertices[i];
	 				posAux = buscaVertice(G,G->vertices[i]);
	 				visitado[posAux] = 1;


	 			}
				
			}
		} else {
			if(G->arestas[pos][i] != 0){
				//puts("passou ?");
				if( veVisita(G,G->vertices[i],visitado) == 1 ){
					printf("[%d]",G->vertices[i]);
					fila[contF++] = G->vertices[i];
					posAux = buscaVertice(G,G->vertices[i]);
					visitado[posAux] = 1;
				}
				
			}
		}
	}
	for( i = 0; i < contF; i++){
		Largura(G,fila[i],visitado,partida);
	}

	if(ind == partida){
		//libera o vetor de controle da memória
	 	free(visitado);
	}
	//libera a fila construida da memoria a cada chamada
	free(fila);

}

void percursoLargura(tipoGrafo *G,int ind){

	printf("[%d]: ",ind );
	Largura(G,ind,NULL, ind);
	puts("");

}

void Profundidade(tipoGrafo *G,int ind, int *visitado,int cont){
	int i,pos;

	pos = buscaVertice(G,ind);
	visitado[pos] = cont;

	for(i = 0; i < G->contV; i++){
		if(i < pos){
			if(G->arestas[i][pos] != 0){
				
				if(veVisita(G,G->vertices[i],visitado) == 1 ){
					Profundidade(G,G->vertices[i],visitado,cont+1);
				}
			}
		} else {
			if(G->arestas[pos][i] != 0){

				if(veVisita(G,G->vertices[i],visitado) == 1 ){
					Profundidade(G,G->vertices[i],visitado,cont+1);
				}	
			}
		}
	}
}

void percursoProfundidade(tipoGrafo *G,int ind){
	int *visitado,i,cont,j,prof;

	visitado = (int*) malloc( G->contV * sizeof(int) );
	
	for( i = 0; i < G->contV; i++){
		visitado[i] = 0;
	}
	cont = 1;
	Profundidade(G,ind,visitado,cont);

	for(i = 0; i < G->contV; i++){
		printf("(%d,%d)",G->vertices[i],visitado[i]);

	}

	puts("");
}
int GrauVertice(tipoGrafo *G,int ind){
	int pos,i,contG;
	pos = buscaVertice(G,ind);
	contG = 0;
	if( pos > -1){
		//printf("[%d]->Grau: ",G->vertices[pos]);
		for(i = 0; i < G->contV; i++){
			if( i < pos){
				if(G->arestas[i][pos] != 0){
					contG++;
				}
			} else {
				if(G->arestas[pos][i] != 0){
					contG++;
				}
			}
		}
		return contG;
		//printf("%d\n",contG);

	}
}

void removeVertice(tipoGrafo *G,int ind){
	int pos,flag,i;

	pos = buscaVertice(G,ind);
	//printf("test - %d\n",pos );
	if( pos > -1){
		for(i = 0; i < G->contV; i++){

			if( i < pos ){
				G->arestas[i][pos] = 0;
			} else {
				G->arestas[pos][i] = 0;
			}
			
			
		}
		G->vertices[pos] = -1;
		// for(i = pos; i < G->contV-1; i ++){
		// 	G->vertices[i] = G->vertices[i+1];
		// }
		G->contV--;
	} else {
		puts("Vértice inexistente");
	}

}

void vizinhosVertice(tipoGrafo *G,int ind){
	int pos,i;
	pos = buscaVertice(G,ind);
	if( pos > -1){
		printf("[%d]->",G->vertices[pos]);
		for(i = 0; i < G->contV; i++){
			if( i < pos){
				if(G->arestas[i][pos] != 0){
					printf("(%d)->",G->vertices[i] );
				}
			} else {
				if(G->arestas[pos][i] != 0){
					printf("(%d)->",G->vertices[i] );
				}
			}
		}
		puts("NULL");

	}
}


int VerticeMaiorGrau(tipoGrafo *G){
	int i, maior,pos,aux,ind;

	maior = GrauVertice(G,1);
	for( i = 0; i < G->contV; i++){
		pos = buscaVertice(G,i);
		if( pos > -1){
			aux = GrauVertice(G,i);
			if( maior < aux ){
				maior = aux;
				ind = i;
			}
		}

	}
	printf("%d %d\n",ind,maior);
}