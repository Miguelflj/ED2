

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct estGrafo{
	int contV;
	int max;
	char *vertices;
	int **arestas;

}estGrafo;


//n é o tamanho definido pelo usuário, e será a quantia maxima de vertices no meu grafo;
estGrafo *inicializaGrafo(int n){
	int i, j;
	estGrafo *G;
	G = (estGrafo*) malloc( sizeof(estGrafo) );
	G->contV = 0;
	G->max = n;
	G->vertices = (char*) malloc( n * sizeof(char) );
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


int insereVertice(estGrafo *G,char letra){
	int i, flag;
	if(G->contV < G->max){
		flag  = 0;
		for(i = 0; i < G->contV; i++){
			if(G->vertices[i] == letra){
				flag = 1;
			}
		}
		if( flag == 0){

			G->vertices[i] = letra;
			G->contV++;
			return 1;
		} else {
			puts("Vertice já existente no seu grafo");
			return 0;
		}
	}
}


int buscaVertice(estGrafo *G,char v){
	int i;
	for(i = 0; i < G->contV; i++){
		if(G->vertices[i] == v){
			return i;
		}
	}
	return -1;
}


void insereAresta(estGrafo *G,char v1,char v2,int peso){
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
		printf("(%c %c) - Algum ou os dois vértices não existem\n",v1,v2);

	}

}



int buscaAresta(estGrafo *G, char v1,char v2){
	int pos1,pos2,aux;

	pos1 = buscaVertice(G,v1);
	pos2 = buscaVertice(G,v2);

	if( ( pos1 > -1)  && (pos2 > -1) ){
 		if(pos2 < pos1){
 			
 			aux = pos2;
 			pos2 = pos1;
 			pos1 = aux;
 		}

 		if( G->arestas[pos1][pos2] != 0){
 			return 1;
 		} else {
 			return 0;
 		}

	} else {
		puts("Algum ou os dois vértices não existem");
		return 0;
	};

}





void removeAresta(estGrafo *G,char v1,char v2){
	int pos1,pos2,aux;

	
	pos1 = buscaVertice(G,v1);
	pos2 = buscaVertice(G,v2);

	if( ( pos1 > -1)  && (pos2 > -1) ){
 		if(pos2 < pos1){
 			
 			aux = pos2;
 			pos2 = pos1;
 			pos1 = aux;
 		}
 		G->arestas[pos1][pos2] = 0;

	} else {
		puts("Algum ou os dois vértices não existem");
		
	}

}

void removeVertice(estGrafo *G,char v){
	int pos,flag,i;
	char *nullV;

	nullV = "-";
	pos = buscaVertice(G,v);
	//printf("test - %d\n",pos );
	if( pos > -1){
		for(i = 0; i < G->contV; i++){

			if( i < pos ){
				G->arestas[i][pos] = 0;
			} else {
				G->arestas[pos][i] = 0;
			}
			
			
		}
		G->vertices[pos] = *nullV;
		// for(i = pos; i < G->contV-1; i ++){
		// 	G->vertices[i] = G->vertices[i+1];
		// }
		G->contV--;
	} else {
		puts("Vértice inexistente");
	}

}
void imprime(estGrafo *G){
	int i,j;
	char *nullV;

	nullV = "-";
	if(G != NULL){
		for(i = 0; i < G->contV; i++){
			if( G->vertices[i] != *nullV){

				printf("[%c]->",G->vertices[i] );
				for(j = 0; j < G->contV; j++){
					if(j < i){
						if(G->arestas[j][i] != 0){
							printf("(%c)->",G->vertices[j]);
						}
					} else {
						if(G->arestas[i][j] != 0){
							printf("(%c)->",G->vertices[j]);
						}
					}
					
				}
				puts("NULL");
			}
		}
	}
}
estGrafo *carregaGrafo(){
	estGrafo *G;
	FILE *fileG;
	char entrada[100],vertice[100],arestas[100];

	int flag,peso[100],t;
	char v1,v2;
	int n,na,i,j,p;


	fileG = fopen("arqgrafo.txt","r");
	if(fileG == NULL){
		puts("Erro na abertura do arquvio");
		return 0;
	}

	n = 0;
	flag = 3;
	na = 0;
	t = 0;
	while( fscanf(fileG,"%s",entrada) != EOF){	
		if( flag == 1){
			//printf("vertice - %c\n",entrada[0]);
			vertice[n++] = entrada[0];
		} else if(flag == 0){
			arestas[na++] = entrada[0];
			//printf("test-%c\n",entrada[1]);
			peso[t++] = entrada[4] - '0';
			arestas[na++] = entrada[2];

	
		} else if(flag == 2){
			puts("Arquivo mal estruturado! PAHHHHHH!!!!");
			return NULL;
		}

		if( strcmp(entrada,"#vertices") == 0){
			flag = 1;
			//puts("entrou");
		} else if(strcmp(entrada,"#arestas") == 0){
			flag = 0;
			//puts("noups");
		} else if( (flag != 1) && (flag != 0) ) {
			flag = 2;
		}

		
	}
	n = n-1;
	G = inicializaGrafo(n);

	for(i = 0; i < n; i++){
		v1 = vertice[i];
		insereVertice(G,v1);
	}

	j = 0;
	for(i = 0; i < na;i = i + 2){
		v1 = arestas[i];
		v2 = arestas[i+1];
		p = peso[j++];


		//printf("v1:%c - v2:%c\n",v1,v2);
		insereAresta(G,v1,v2,p);
	}

	return G;

}

int veVisita(estGrafo *G,char l,int *visitado){
	int pos;
	pos = buscaVertice(G,l);
	if(visitado[pos] == 0){
		return 1;
	} else {
		return 0;
	}

}


void Largura(estGrafo *G,char l,int *visitado,char partida){
	int i,pos,posAux,contF;

	char *fila;
	contF = 0;

	fila = (char*) malloc( G->contV * sizeof(char) );

	if( visitado == NULL){
		visitado = (int*) malloc( G->contV * sizeof(int) );
		
		for( i = 0; i < G->contV; i++){
			visitado[i] = 0;
	 	}
	}


	pos = buscaVertice(G,l);
	visitado[pos] = 1;

	for(i = 0; i < G->contV; i++){
		if(i < pos){
	 		if( G->arestas[i][pos] != 0 ){
	 			//puts("passou ?");
	 			if( veVisita(G,G->vertices[i],visitado) ){

	 				printf("[%c]",G->vertices[i]);
	 				fila[contF++] = G->vertices[i];
	 				posAux = buscaVertice(G,G->vertices[i]);
	 				visitado[posAux] = 1;


	 			}
				
			}
		} else {
			if(G->arestas[pos][i] != 0){
				//puts("passou ?");
				if( veVisita(G,G->vertices[i],visitado) == 1 ){
					printf("[%c]",G->vertices[i]);
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

	if(l == partida){
		//libera o vetor de controle da memória
	 	free(visitado);
	}
	//libera a fila construida da memoria a cada chamada
	free(fila);

}

void percursoLargura(estGrafo *G,char l){

	printf("[%c]: ",l );
	Largura(G,l,NULL, l);
	puts("");

}

char *maiorGrau(estGrafo *G){

	int t,pos,contVizinho,maior,i,j;
	contVizinho = 0;
	char *ver;

	ver = (char*) malloc( G->contV * sizeof(char) );

	maior = 0;
	t = 1;
	if( G != NULL ){
		for(i = 0; i < G->contV; i++){
			for(j = 0; j < G->contV; j++){
				if( j < i){

					if(G->arestas[j][i] != 0){
						contVizinho++;
					}

				} else{

					if(G->arestas[i][j] != 0){
						contVizinho++;
						
					}

				}
			}

			if(contVizinho >= maior){

				if(contVizinho == maior){
					maior = contVizinho;
					ver[t++] = G->vertices[i];
				} else{
					t = 0;
					maior = contVizinho;
					ver[t++] = G->vertices[i];
					ver[t] = '\0';	
				}
				
				
			}
			contVizinho = 0;
		}

		//printf("vertice mais popular:%c\n",ver[0]);
		return ver;
	}

}


void Profundidade(estGrafo *G,char l, int *visitado,int cont){
	int i,pos;

	pos = buscaVertice(G,l);
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

void percursoProfundidade(estGrafo *G,char *l){
	int *visitado,i,cont,j,prof;

	visitado = (int*) malloc( G->contV * sizeof(int) );
	
	for( i = 0; i < G->contV; i++){
		visitado[i] = 0;
	}
	cont = 1;
	Profundidade(G,*l,visitado,cont);

	for(i = 0; i < G->contV; i++){
		printf("(%c,%d)",G->vertices[i],visitado[i]);

	}

	puts("");
}


int GrauVertice(estGrafo *G,char v){
	int pos,i,contG;
	pos = buscaVertice(G,v);
	contG = 0;
	if( pos > -1){
		printf("[%c]->Grau: ",G->vertices[pos]);
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
		printf("%d\n",contG);

	}
}
void vizinhosVertice(estGrafo *G,char v){
	int pos,i;
	pos = buscaVertice(G,v);
	if( pos > -1){
		printf("[%c]->",G->vertices[pos]);
		for(i = 0; i < G->contV; i++){
			if( i < pos){
				if(G->arestas[i][pos] != 0){
					printf("(%c)->",G->vertices[i] );
				}
			} else {
				if(G->arestas[pos][i] != 0){
					printf("(%c)->",G->vertices[i] );
				}
			}
		}
		puts("NULL");

	}
}
int main(){
	estGrafo *G;
	int i,pos;
	char *l,*l1,*ver;


	G = carregaGrafo();
	imprime(G);
	l = "b";
	GrauVertice(G,*l);
	vizinhosVertice(G,*l);
	// removeVertice(G,*l);
	//percursoLargura(G,*l);
	//l1 = "b";
	//imprime(G);

	return 0;
}	