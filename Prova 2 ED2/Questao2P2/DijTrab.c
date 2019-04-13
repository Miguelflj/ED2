/* UFMT - ED2 - TRABALHO 6 - GRAFOS (DIJKSTRA)
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
int contV(vertice *G);
int retPosMenor(int *pesos, int tam,int *verifica);

//funcoes utilizadas no trabalho
void RelaxDijkstra(vertice *G,int *dist,int *abertos,int *cam);
void Dijkstra(vertice *G,int ind);





int main(){

	int tam, pos;
	//Declara grafo G 
	vertice *G,*aux;
	G = NULL;
	int maior,indV;
	G = CarregaGrafo();
	
	veGrafo(G);
	Dijkstra(G,1);

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
/*
vertice *insereVertice(vertice *G,int ind){
	vertice *novo;
	if( G != NULL){
		novo = novoVertice(ind);
		novo->nxVertice = G;
		G = novo;
	} else {
		G = novoVertice(ind);
	}
	return G;
}
*/

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
	FILE *arq;
	vertice *G;
	G = NULL;
	char entrada[50],c;

	int qtdnos,arcs,n1,n2,peso,i,j;

	arq = fopen("entradaQ2.txt","r");
	if( arq == NULL){
		puts("Deu ruim");
		return 0;
	}
	j = 0;
	while(fscanf(arq,"%c",&c) != EOF){
		if( c == 'c'){

			fscanf(arq, "%[^\n]",entrada);

		} else if( c == 'p'){
			fscanf(arq, " %d %d",&qtdnos,&arcs);
			puts("#vertices#...");
			//printf("%c\n",c );
			printf("%d\n",qtdnos);

			for(i = 1; i <= qtdnos; i++){
				//printf("v-%d\n",i);
				G = insereVertice(G,i);
			}
			puts("Vertices carregados...");
			puts("#arestas#...");
		} else if( c == 'a'){
			fscanf(arq, " %d %d %d",&n1,&n2,&peso);
			
			//printf("a-%d\n",j++);

			G = insereAresta(G,n1,n2,peso);
			
		}
	}
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

int contV(vertice *G){
	int tam;
	vertice *aux;
	tam = 0;
	aux = G;

	while(aux != NULL){
		aux = aux->nxVertice;
		tam++;
	}
	return tam;
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

int retVertice(vertice *G, int pos){
	vertice *aux;
	aux = G;
	int cont = 0;
	while( aux != NULL && cont < pos){
		aux = aux->nxVertice;
	}
	return aux->ind;
}

void ConstroiCaminho(int *cam,int pos){
	int i;
	if( cam[pos] == pos){
		printf("[%d]partida\n",cam[pos]+1);
	}else {
		printf("[%d]",pos+1);
		ConstroiCaminho(cam,cam[pos]);
	}

}

void RelaxDijkstra(vertice *G,int *dist,int *abertos,int *cam){
	int pos,tam,i, qtdAB,posMenor;
	qtdAB = 0;
	int ind;
	vertice *naveVertice;
	aresta *naveAresta;
	tam = contV(G);
	//printf("%d\n",tam);
	while(qtdAB  < tam ){
		posMenor = -1;
		for(i = 0; i < tam; i++){
			//printf("%d\n",i );
			if( abertos[i] == 1 && ( dist[i] < posMenor || posMenor == -1) && (dist[i] != -1) ){

				posMenor = i;
				//printf("posMenor: %d\n",posMenor);

			}
		}
		//printf("pos:%d\n",posMenor);
		abertos[posMenor] = 0;
		qtdAB++;
		naveVertice = G;
	
		// acha o vertice
		int controlePos = 0;
		while( naveVertice != NULL &&  controlePos != posMenor ){
			naveVertice = naveVertice->nxVertice;
			controlePos++;
		}
		//printf("tst:%d\n",naveVertice->ind);

		// olha os vertices adjacentes
		naveAresta = naveVertice->nxAresta;
		//relaxamento em todos os vertices adjacentes
		while( naveAresta != NULL){
			//printf("tst:%d\n",naveAresta->ind);
			pos = posV(G,naveAresta->ind);
			if( (dist[pos] == -1) || dist[pos] > (dist[posMenor] + naveAresta->peso ) ){
				//printf("%d\n",pos);
				dist[pos] = dist[posMenor] + naveAresta->peso;
				cam[pos] = posMenor;
				
			}
			
			naveAresta = naveAresta->nxAresta;
		}
		
	}
	
	puts("Distancia:");
	for( i = 0; i < tam; i++){
		printf("[%d]",dist[i]);

	}
	
	
	puts("\nCaminho:");
	//int controle = tam;
	for( i = 0; i < tam; i++){
		//ind = retVertice(G,cam[i]);
		printf("%d:[%d]",i+1,cam[i]+1);
		
	}
	
	puts("");
	// Trocar os 3 vertices que deseja averiguar a distancia e caminho
	/* Como os vertices sao crescentes, a posicao referente a cada vertice é vertice-1
	 se deseja averiguara a distancia ou caminho pra acessar cada vertice utilize vertice-1

	*/
	/*
	printf("Custo(%d)\n",dist[16424]);
	ConstroiCaminho(cam,16424);
	printf("Custo(%d)\n",dist[142386]);
	ConstroiCaminho(cam,142386);
	printf("Custo(%d)\n",dist[233962]);
	ConstroiCaminho(cam,233962);
	*/
	
}


void Dijkstra(vertice *G,int ind){
	int pos,tam,i;
	int *dist,*cam,*abertos;
	if( G != NULL){
		pos = posV(G,ind);
		if( pos != -1){
			tam = contV(G);
			dist = (int*) malloc( tam * sizeof(int) );
			abertos = (int*) malloc( tam * sizeof(int) ); 
			cam =  (int*) malloc( tam * sizeof(int) );

			for( i = 0; i < tam; i++){
				abertos[i] = 1;
				dist[i] = -1;
				cam[i] = -1;
			}
			
			dist[pos] = 0;
			cam[pos] = pos;
			RelaxDijkstra(G,dist,abertos,cam);

		} else {
			// vertice s(inicial) nao existe no grafo
		}

	} else {
		// nao existe grafo
	}
}
