

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct aresta{
	int p;
	char l;
	struct aresta *prox;
}aresta;

typedef struct vertice{
	int contADJ;
	struct vertice *proxV;
	aresta *proxA;
	char l;

}vertice;	

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

			while( auxV != NULL){

				flagIn = 0;

				if( auxV->l == v1 ){

					auxA = auxV->proxA;
					if(auxA != NULL){

						while( (auxA->prox != NULL) && (auxA->l != v2) ){
							auxA = auxA->prox;
						}
						if(auxA->l != v2){

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

				if(auxV->l == v2){

					auxA = auxV->proxA;
					if(auxA != NULL){

						while( (auxA->prox != NULL) && (auxA->l != v1) ){
							auxA = auxA->prox;
						}

						if(auxA->l != v1){
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
			printf("[%c Grau:%d]->",auxV->l,auxV->contADJ);
			if(auxV->proxA != NULL){
				auxA = auxV->proxA;
				while( auxA != NULL){
					printf("(%c)->",auxA->l);
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
	char entrada[100],ver[100],arestas[100];

	int flag,peso[100],t;
	char v1,v2;
	int n,na,i,j,p;

	G = NULL;

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
			ver[n++] = entrada[0];
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

	for(i = 0; i < n; i++){
		v1 = ver[i];
		G = insereVertice(G,v1);
	}

	j = 0;
	for(i = 0; i < na;i = i + 2){
		v1 = arestas[i];
		v2 = arestas[i+1];
		p = peso[j++];


		//printf("v1:%c - v2:%c\n",v1,v2);
		G = insereAresta(G,v1,v2,p);
	}

	return G;

}
vertice *RemoveAresta(vertice *G,char v1,char v2){
	vertice *auxV;
	aresta *auxA,*sent;


	if( G != NULL){
		auxV = G;
		while( (auxV != NULL) && (auxV->l != v1) ){
			auxV = auxV->proxV;
		}
		if(auxV->l == v1){
			auxV->contADJ--;
			auxA = auxV->proxA;
			if(auxA != NULL){
				sent = NULL;
				while( (auxA != NULL) && (auxA->l != v2) ){
					sent = auxA;
					auxA = auxA->prox;
				}
				if(  (auxA->l == v2) && (sent != NULL) ){
					sent->prox = auxA->prox;
					free(auxA);
					return G;
				} else if( auxA->l == v2) {
					auxV->proxA = auxA->prox;
					free(auxA);
					return G;
				}
			}
		}
	}
}

vertice *RemoveA(vertice *G,char v1,char v2){
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
		RemoveAresta(G,vizinho->l,vertice->l);
		free(vizinho);
	} else {
		RemoveAresta(G,vizinho->l,vertice->l);
		free(vizinho);
	}
}


vertice *RemoveV(vertice *G,char v){
	vertice *auxV,*sent;
 	aresta *auxA;
	char l;
 	int flag;
 	if(G != NULL){
 		flag = verificaVertice(G,v);
 		if( flag){

 			auxV = G;
 			sent = NULL;
 			while( (auxV != NULL) &&  (auxV->l != v)   ){
 				sent = auxV;
 				auxV = auxV->proxV;
 			}

 			if(auxV->l == v){
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

void PercursoLargura(vertice *G,char v,int *vizinhos,char partida,int tam){
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
				printf("[%c]",auxA->l );
				fila[contF++] = auxA->l;

				
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
int contV(vertice *G){
	int tam;
	vertice *aux;
	tam = 0;
	aux = G;

	while(aux != NULL){
		aux = aux->proxV;
		tam++;
	}
	return tam;
}
int retPosMenor(int *pesos, int tam,int *verifica){
	int i,menor,pos;
	menor = pesos[0];
	pos = 0;
	for( i = 0; i < tam; i++ ){
		if( (menor == -1) || (menor > pesos[i]) && (pesos[i] != -1) && (verifica[i] == 1) ){
			menor = pesos[i];
			pos = i;
		}
	}
	return pos;
}

// acho que ta funfando, espero profundamente que sim, se sim, sou foda!
void FunfDijkstra(vertice *G,char v,int tam,char *caminho,int *verifica,int *pesos){
	int posA,posVer,i,contV;
	int menor,j;
	vertice *auxV;
	aresta *auxA;
	contV = 1;
	if(G != NULL){
		auxV = G;
		while( (auxV->proxV != NULL) && (auxV->l != v) ){
			auxV = auxV->proxV;
			
		}	
		if(auxV->l == v){
			auxA = auxV->proxA;
			posVer = posV(G,auxV->l);
			while(auxA != NULL){
				posA = posV(G,auxA->l);
				pesos[posA] = auxA->p;

				caminho[posA] = auxV->l;
				auxA = auxA->prox;
			}
		}
		verifica[posVer] = 1;
		while( contV < tam-1 ){
			menor = pesos[0];
			posVer = retPosMenor(pesos,tam,verifica);
			auxV = G;
			j = 0;
			//posV é o "indice" do vertice na estrutura
			while( (auxV->proxV != NULL) && (j < posVer) ){
				auxV = auxV->proxV;
				j++;
			}
			if(j == posVer){
				auxA = auxV->proxA;
				while(auxA != NULL){
					posA = posV(G,auxA->l);
					if( verifica[posA] == -1 ){
						if( ( (pesos[posVer] + auxA->p) < pesos[posA]) && (pesos[posA] != -1) ){

						}
					}
					auxA = auxA->prox;
				}
				verifica[posVer] = 1;
			}

			contV++;
		}

	}
	
}

void Dijkstra(vertice *G,char v){
	int tam,*verifica,*pesos,i,pos;
	char *caminho;

	tam = contV(G);

	caminho = (char*) malloc( tam * sizeof(char) );
	verifica = (int*) malloc(tam * sizeof(int) );
	pesos = (int*) malloc(tam * sizeof(int) );

	for(i = 0; i < tam; i++) {
		verifica[i] = -1;
		pesos[i] = -1;
	}
	pos = posV(G,v);
	FunfDijkstra(G,v,tam,caminho,verifica,pesos);

	for(i = 0; i < tam;i++){
		printf("[%d]",pesos[i] );
	}
	puts("");
}


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
	veGrafo(G);
	//percursoP(G,*v1);
	Dijkstra(G,*v1);
	//Vizinhanca(G,*v2);
	// grau = GrauVertice(G,*v2);
	// printf("Vertice:%c Grau:%d\n",*v2,grau);
	return 0;
}	