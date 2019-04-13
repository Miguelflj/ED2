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
vertice *CarregaGrafo(char *arquivo);
void veGrafo(vertice *G);
void VizinhoVertice(vertice *G,int ind); // funcao (e)
int GrauVertice(vertice *G,int ind); // funcao (f)
vertice *RemoveAresta(vertice *G,int v1,int v2);
vertice *RemoveA(vertice *G,int v1,int v2);
void RemoveVertice(vertice *G,vertice *vertice,aresta *vizinho);
vertice *RemoveV(vertice *G,int v); // funcao (c)
int posV(vertice *G,int v);
int VeVisita(vertice *G,int *visita,int v,int tam);
int posCor(vertice *G,vertice *vetCor,int n);
void Merge(vertice vet[],int inicio, int meio, int fim);
void Sort(vertice vet[],int inicio, int fim);

//prototipos das funcoes que controlam a coloracao
int coloreGrafo(vertice *G,int *cors,int qtdCor,int ind,vertice *vtVertice);
void Coloracao(vertice *G);





int main(int argc,char *argv[]){

	if(argc <= 1){
		puts("Entre com o nome do arquivo: \nEx.: ./exec test.txt ");
		return 0;
	}
	int tam, pos;
	//Declara grafo G 
	vertice *G,*aux;
	G = NULL;
	int maior,indV;
	G = CarregaGrafo(argv[1]);

	//veGrafo(G);
	Coloracao(G);
	

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
vertice *CarregaGrafo(char *arquivo){
	FILE *arq;
	vertice *G;
	G = NULL;
	char entrada[50],c,lixo[10];

	int qtdnos,arcs,n1,n2,peso,i,j;

	arq = fopen(arquivo,"r");
	if( arq == NULL){
		puts("Deu ruim");
		return 0;
	}
	j = 0;
	while(fscanf(arq,"%c",&c) != EOF){
		if( c == 'c'){

			fscanf(arq, "%[^\n]",entrada);

		} else if( c == 'p'){
			fscanf(arq, " %s %d %d",lixo,&qtdnos,&arcs);
			puts("#vertices#...");
			//printf("%c\n",c );
			printf("%d\n",qtdnos);

			for(i = 1; i <= qtdnos; i++){
				//printf("v-%d\n",i);
				G = insereVertice(G,i);
			}
			puts("Vertices carregados...");
			puts("#arestas#...");
		} else if( c == 'e'){
			fscanf(arq, " %d %d",&n1,&n2);
			
			//printf("a-%d\n",j++);

			G = insereAresta(G,n1,n2,1);
			
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



int posCor(vertice *G,vertice *vetCor,int n){
	int i,tam;
	tam = contV(G);
	for( i = 0; i < tam; i++){
		if(vetCor[i].ind == n){
			
			return i;
		}
	}
	return -1;
}

int coloreGrafo(vertice *G,int *cors,int qtdCor,int ind,vertice *vtVertice){

	vertice *naveVertice;
	aresta *naveAresta;

	int *rangeCor,cor,i,pos,corRef;

	naveVertice = G;
	// vetor para controle das flags das corres ja aplicadas nos vizinhos
	rangeCor = (int*) malloc( qtdCor *sizeof(int) );

	for( i = 0; i < qtdCor; i++){
		rangeCor[i] = 0;
	}
	//Acessa o vertice de partida
	while( (naveVertice->nxVertice != NULL) && (naveVertice->ind != ind) ){
		naveVertice = naveVertice->nxVertice;
	}
	if( naveVertice->ind == ind){
		//acessa ao inicio dos vertices adjacentes ao de referencia
		naveAresta = naveVertice->nxAresta;

		while( naveAresta != NULL){
			//olha pra cada vertice adjacente ao de referencia e vê se ele ja tem cor e qual
			pos = posCor(G,vtVertice,naveAresta->ind);
			if( cors[pos] != -1  ){
				corRef = cors[pos] - 1;
				rangeCor[corRef] = 1;
			}
			naveAresta = naveAresta->nxAresta;
		}
		cor = -1; 
		for( i = 0; i < qtdCor; i++){
			if( cor == -1){
				if(rangeCor[i] == 0){
					cor = i+1;
				}
			}
		}

		pos = posCor(G,vtVertice,naveVertice->ind);
		//pinta o vertice com a nova cor ou com uma cor ja existente no range se possivel
		//etapa 4
		if( cor == -1){
				
			qtdCor++;
			cors[pos] = qtdCor;

		} else {
			
			cors[pos] = cor;
		}


		return qtdCor;	
	}

}

void Merge(vertice vet[],int inicio, int meio, int fim){
        int i,j,k,tam;
        vertice *vetAux;
        tam = (fim - inicio) + 1;
        vetAux = (vertice*) malloc(sizeof(vertice)*tam);
        // i com o inicio do subvetor a esquerda
        i=inicio;
        // j com o inicio do subvetor a direita
        j=meio+1;
        // tamanho do vetor inicial
        for(k=0; k < tam; k++){
            // verifica se os lados dos meus subvetores ainda tem valores a direita
            if(i < (meio+1) && j <= fim){
                // faz a ordenacao crescente
                if(vet[i].contVz > vet[j].contVz){
                    
                    vetAux[k] = vet[i++];
                    
                }else{
                    
                    vetAux[k] = vet[j++];
                    
                }
                
            // se um dos subvetores chegou ao fim completa com o outro
            }else if(i < (meio+1) && j > fim){
                
                vetAux[k] = vet[i++];
                
            }else{
                
                vetAux[k] = vet[j++];
                
            }
                
        }
        i = 0;
        for(k=inicio; k <= fim; k++){
            vet[k] = vetAux[i++];
            
        }
        free(vetAux);
            
}

void Sort(vertice vet[],int inicio, int fim){
    int meio;
    if( inicio < fim){
        meio = ( (inicio + fim)/ 2);
        // quebra pro lado esquerdo
        Sort(vet, inicio, meio);
        // quebra pro lado direito
        Sort(vet, meio+1, fim);
        // faz o merge
        Merge(vet,inicio, meio, fim);
    }
    
}





void Coloracao(vertice *G){
	int qtdCor,*cors;
	vertice *vtVertice;
	vertice aux;
	vertice *auxV;
	int tam,i,j,pos;
	if( G != NULL){

		tam = contV(G);

		vtVertice = (vertice*) malloc( tam * sizeof(vertice) );
		cors = (int*) malloc( tam* sizeof(int) );
		auxV = G;

		for(i = 0; i < tam; i++){
			//copia grafo para vetor
			cors[i] = -1;
			vtVertice[i] = *auxV;

			auxV = auxV->nxVertice;
		}

		// chama a funcao de ordenacao
		// etapa 1
		Sort(vtVertice,0,tam-1);
		
		/*
		for(i = 0; i < tam; i++){
			//verifica se esta ordenado corretamente utilizando a quantia de vizinhos
			printf("vet[%d,%d)->",vtVertice[i].ind,vtVertice[i].contVz);
		}
		*/	
		
		
		//etapa 2
		qtdCor = 1;
		cors[0] = qtdCor;

		for(i = 1; i < tam; i++){
			//etapa 3
			qtdCor = coloreGrafo(G,cors,qtdCor,vtVertice[i].ind,vtVertice);
			//etapa 5
			
		}

		int maiorC = 1;
		//imprime o indice e a cor dele
		
		for(i = 0; i < tam; i++){
			printf("vet[%d,%d)->",vtVertice[i].ind,cors[i]);
			if( maiorC < cors[i]){
				maiorC = cors[i];
			}
		}
		puts("NULL");
		
		printf("Numero Cromatico: %d\n",maiorC);
		
	}

}