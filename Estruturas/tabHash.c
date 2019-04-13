#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM 15

typedef struct Aluno{
	char nome[20];
	long int ra;
	int chave;
	struct Aluno *prox;
}Aluno;

typedef struct tabHash{
	Aluno *inicio; 
}tabHash;


int fHash(long int ra){
	int aux;
	//aux = floor(TAM/ra);
	//return ( (TAM - ra)*(aux) );
	return ra%TAM;
}

// prototipos das funções utilizadas
void InicializaTab(tabHash *tab);
void InsereAluno(tabHash *tab,long int ra,char nome[]);
Aluno *BuscaTab(tabHash *tab);




void InicializaTab(tabHash *tab){
	int i;

	for(i = 0; i < TAM; i++){
		tab[i].inicio = NULL;
	}
}

void InsereAluno(tabHash *tab,long int ra,char nome[]){
	
	Aluno *aux,*novo;
	int i,pos;

   

	pos = fHash(ra);
	printf("pos: %d\n",pos);
	novo = (Aluno*) malloc( sizeof(Aluno) );
	
	strcpy(novo->nome,nome);
	novo->chave = pos;
	novo->prox = NULL;
	novo->ra = ra;

	aux = tab[pos].inicio;

	if(aux == NULL){
		tab[pos].inicio = novo;
	} else {
		while ( aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = novo;
	}

};




Aluno *BuscaTab(tabHash *tab){
	
	int pos;
	long int ra;
	Aluno *aux;
	puts("Digite o RA que deseja buscar");
	scanf("%ld",&ra);
	scanf("%*c");
	pos = fHash(ra);
	//printf("%d\n",pos);
	aux = tab[pos].inicio;
	//printf("ra: %ld\n",aux->ra);

	while( aux != NULL){
		if( aux->ra == ra){
			//puts("Encontrou");
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
		
}	

void imprimeTab(tabHash *tab){
	Aluno *aux;
	int i;
	for(i = 0; i < TAM; i++){
		aux = tab[i].inicio;
		while(aux != NULL){
			printf("Aluno: %s\n",aux->nome);
			printf("RA: %ld\n",aux->ra);
			//printf("Pos: %d\n",aux->chave);

			aux = aux->prox;
		}
	}
}


void Menuzin(int op,tabHash *tab){
	Aluno *aux;
	FILE *arqv;
	long int ra;
	char nome[20];
    system("clear");
    switch(op){
        case 1:
       		arqv = fopen("Alunos.txt","r");
   		 	if( arqv == NULL){
        		puts("Erro na abertura do arquivo.\n");
    		}
    		while(fscanf(arqv,"%ld %s",&ra,nome) != EOF){
                InsereAluno(tab,ra,nome);
            }
            fclose(arqv);
            puts("Carregado com sucesso");
            break;
        case 2:
            aux = BuscaTab(tab);
            if(aux == NULL){
                puts("Nao cadastrado");
            }else{
               	printf("Aluno: %s\n",aux->nome);
				printf("RA: %ld\n",aux->ra);
				printf("Pos: %d\n",aux->chave);
                
            }
            break;
        case 3:
        	imprimeTab(tab);
        	break;
        default:
            break;
    
    }


};




int main(){
	Aluno *aux;
	tabHash *tabP;

	tabP = (tabHash*) malloc( sizeof(tabHash) * TAM);
	
	int op;
	InicializaTab(tabP);
	do{
		puts("Digite a opção:\n 1-Carrega tabela\n 2-Buscar\n 0-Sair");

	    scanf("%d", &op);
	   
	    Menuzin(op,tabP);

	}while(op != 0);

	return 0;
}