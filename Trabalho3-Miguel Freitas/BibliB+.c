/*
	UFMT - CCOMP
	ESTRUTURA DE DADOS 2 - IVAIRTON
	MIGUEL FREITAS
	TRABALHO 3 ARVORE B+

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>




// estrutura do livro codigo 8 digitos e nome
typedef struct TipoLivro{

	int codp1,codp2;
	char nome[100];

}TipoLivro;

// chamarei de "pagina" os nós da arvore b+

// estrutura das paginas da arvore b

typedef struct Pagina{

	TipoLivro **vet;
	struct Pagina **filhos;
	int contL;
	int folha;
	struct Pagina *prox;

}Pagina;



// funçao para alocar uma pagina sempre qu enecessario utilizando o T dado pelo arquivo de entrada
//setando todos os ponteiros de filhos e livros para nulo
Pagina *alocaPagina(int T){
	Pagina *Pag;
	int i;


	Pag = (Pagina*) malloc(sizeof(Pagina));
	
	int n_livros = T*2-1;
	int n_filhos = T*2;
	
	// printf("livros: %d, filhos: %d\n", n_livros, n_filhos);
	
	Pag->vet = (TipoLivro**) malloc(n_livros * sizeof(TipoLivro*));
	Pag->filhos = (Pagina**) malloc(n_filhos * sizeof(Pagina*));

	Pag->contL = 0;
	Pag->folha = 1;
	Pag->prox = NULL;
	i = 0;

	while(i < n_filhos ) {

		Pag->filhos[i] = NULL;
		if(i < n_livros)
			Pag->vet[i] = NULL;
		i++;
	}

	return Pag;
}

// aloca o novo livro já armazenando suas informações devidamente
TipoLivro *alocaLivro(int codp1,int codp2,char name[]){

	TipoLivro *livro;
	livro = (TipoLivro*) malloc(sizeof(TipoLivro));
	livro->codp1 = codp1;
	livro->codp2 = codp2;
	strcpy(livro->nome,name);

	return livro;
}


// imprime toda a pagina
void imprimePag(Pagina *Pag){
	int i;
	i = 0;
	if(Pag != NULL){
		while(i < Pag->contL ){
			printf("[%.4d-%.4d %s] ",Pag->vet[i]->codp1,Pag->vet[i]->codp2,Pag->vet[i]->nome);
			i++;
		}



	}
}

// percorre a arvore
void Percorre(Pagina *Pag){
	int i;
	if(Pag != NULL){
		imprimePag(Pag);
		puts("");

		for(i = 0; i < Pag->contL + 1; i++){
			Percorre(Pag->filhos[i]);

		}

	}
	
}

//posiciona o livro no vetor utilizando o codigo total 
void posicionaLivro(Pagina *Pag,TipoLivro *livroRet,Pagina *filhoDir){
	int i;

	i = Pag->contL;
	while( (i > 0) && ( (livroRet->codp1*10*10*10*10 + livroRet->codp2) < (Pag->vet[i-1]->codp1*10*10*10*10 + Pag->vet[i-1]->codp2) ) ){
		Pag->vet[i] = Pag->vet[i-1];
		Pag->filhos[i+1] = Pag->filhos[i];
		i--;
	}
	Pag->vet[i] = livroRet;
	Pag->filhos[i+1] = filhoDir;
	Pag->contL++;
}

//realiza a busca binaria encontrando a posição valida para se inserior ou a posição valida para se descer de acordo com o codigo
int BuscaBin(Pagina *Pag,int cod){
	int pos;
	pos = Pag->contL;
	while( (pos > 0 ) && (cod < ( Pag->vet[pos-1]->codp1*10*10*10*10 + Pag->vet[pos-1]->codp2 ) ) ){
		pos--;
	}

	return pos;
}

// possibilita a quebra, a criação do filho direito/ a copia para a nova raiz do sistema e o limpa da antiga raiz
Pagina *insereArv(Pagina *Pag,int codp1,int codp2,char name[],int *flag,TipoLivro **livroRet,int T){
	int pos,i;
	long int cod, No_code;
	Pagina *filhoDir, *noAux;
	TipoLivro *meio;



	cod = ( (codp1*10*10*10*10) + codp2);

	if(Pag == NULL){
		*flag = 1;
		*livroRet = alocaLivro(codp1,codp2,name);
		return NULL;
	}


	pos = BuscaBin(Pag,cod );

	if(pos < Pag->contL){

		No_code = (Pag->vet[pos]->codp1*10*10*10*10 + Pag->vet[pos]->codp2);

	} else {
		No_code = 0;
	}

	if( (pos < Pag->contL) && ( No_code == cod ) ){
		*flag = 0;
		return 0;
	} else {

		if( (No_code  < cod ) && ( No_code != 0 ) ){
			pos++;
		}

		filhoDir = insereArv(Pag->filhos[pos],codp1,codp2,name,flag,livroRet,T);
		

		if(*flag){
			
			if(Pag->contL < (T * 2 - 1) ){
				
				posicionaLivro(Pag,*livroRet,filhoDir);
				*flag = 0;
				
			} else {
				noAux =  alocaPagina(T);

				
				meio = Pag->vet[T-1];
				noAux->filhos[0] = Pag->filhos[T];
				
				for(i = T; i < (T*2-1); i++ ){
					//posiciona os livros no novo filho direito
					posicionaLivro(noAux,Pag->vet[i],Pag->filhos[i+1]);
							
				}
				for(i = T; i < (T*2-1); i++){
					// limpa a antiga raiz do sistema apontando os ponteiros para nulo para utiliza-la como filho esquerdo de T-1 até T*2-2
			 		Pag->vet[i] = NULL;
			 		Pag->filhos[i] = NULL;
			 		Pag->filhos[i+1] = NULL;
					Pag->contL--;	
				}
				//cuida das paginas de indexação para que elas não sejam confundidas com folha
				if( Pag->folha == 0 ){
					noAux->folha = 0;

				}
				//reposiciona as paginas folhas organizando o ponteiro que apontam para a proxima pagina folha
				if( ( Pag->folha == 1 ) && ( noAux->folha ==  1 ) ){
					noAux->prox = Pag->prox;
					Pag->prox = noAux;
				}


				//decide onde posicior o novo livro.
				if(pos <= (T-1) ){
					posicionaLivro(Pag,*livroRet,filhoDir);
				} else {
					posicionaLivro(noAux,*livroRet,filhoDir);
				}

				*flag = 1;
				*livroRet = meio;
				return (noAux);
				
			}
			
		}
	}
}


// organiza os novos filhos adequadamente
Pagina *funcArvB(Pagina *raiz,int codp1,int codp2,char name[],int T){
	
	Pagina *filhoDir, *novaRaiz;
	int flag;
	flag = 0;
	TipoLivro *livroRet;

	filhoDir = insereArv(raiz,codp1,codp2,name,&flag,&livroRet,T);
	
	// printf("Livro ret- codp1: %d codp2: %d nome: %s\n", livroRet->codp1, livroRet->codp2, livroRet->nome);
	

	if(flag){

		novaRaiz = alocaPagina(T);
		
		novaRaiz->vet[0] = livroRet;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->contL++;

		if(raiz != NULL){
			novaRaiz->folha = 0;
		} else {
			novaRaiz->folha = 1;
		}
		novaRaiz->prox = NULL;

		return novaRaiz;
	}

	return raiz;
}


// controla a leitura do arquivo e gera a arvore com o arquivo de entrada organizado no modelo ex: ( 0000-0000 "nome livro")
Pagina *geraArvore(){

	Pagina *PagR;
	int codp1,codp2,i,T;
	char name[100];

	PagR = NULL;

	FILE *arqv;

	arqv = fopen("teste.txt","r");
	if(arqv == NULL){
		puts("Erro na abertura do arquivo, verifique se o arquivo de entrada utilizado está no repositório adequado");
		return 0;
	}
	// t é o tamanho relativo decidido pelo arquivo de entrada
	// t * 2 -1 é o calculo para a quantidade de livros por pagina
	// t * 2 é o calculo para obter a quantidade de filhos da pagina
	// este calculo é utilizado para garantir que a pagina tenha um vetor de quantidade impar para facilitar o manuseio
	fscanf(arqv,"%d",&T);
	

	while( fscanf(arqv,"%d-%d %[^\n]",&codp1,&codp2,name) != EOF){
		// utilizado para ler o \n no fim de cada nome de livro, problema causado por utilizar o [^\n]
		fscanf(arqv,"%*c");

		PagR = funcArvB(PagR,codp1,codp2,name,T);
			

	}

	fclose(arqv);

	return PagR;
}

void buscaFolhas(Pagina *no){
	int i;
	//FILE *outS;

	//outS = fopen("Saida.txt","a");
	if(no->filhos[0] != NULL){
		buscaFolhas(no->filhos[0]);
	} else{
		while(no != NULL){
			for(i = 0; i < no->contL; i++){
				printf("[%.4d-%.4d %s]",no->vet[i]->codp1,no->vet[i]->codp2,no->vet[i]->nome);
			}	
			printf("->");
			no = no->prox;
		}
		printf("NULL\n");

		
	}	
	//fclose(outS);
}

void Ordem(Pagina *Pag){
    int i;
    i = 0;
    if( Pag != NULL ){
        while ( ( i < Pag->contL )){
            printf("[%.4d-%.4d %s]\n",Pag->vet[i]->codp1,Pag->vet[i]->codp2,Pag->vet[i]->nome);
            Ordem( (Pag)->filhos[i]);
            i++;
        }
    Ordem( (Pag)->filhos[i]);
        
    }
}



int main(){

	clock_t Ticks[2];
	
	Pagina *Pag;
	// chama a função de gerar a arvore adequadamente
	Pag = geraArvore();
	// ja se tem a arvore gerada possibilitando a impressao
	//Percorre(Pag);
	buscaFolhas(Pag);
	Ticks[0] = clock();
	//Ordem(Pag);
	Ticks[1] = clock();
	double Tempo =( (Ticks[1] - Ticks[0]) * 1000.0 );
	printf("\n\nTempo Gasto: %g\n",Tempo);

	return 0;
}