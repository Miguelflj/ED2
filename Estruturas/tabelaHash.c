/*
 Tabela Hash - 27/03

*/
/*funões hash


s = Nulo;
Para k de 1 até m faça
	S = F(S,b[k])
return H(S,n)



Ha(x) = arredonda para baixo ( (a.x mod W) / (W/M)) -1
floor

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM 15

typedef struct tipoAluno {
	char nome[20];
	int ra;

}tipoAluno;

typedef struct tipoTabHash{
    tipoAluno aluno;
    struct tipoTabHash *prox;
    int chave;

}tipoTabHash;




int fHash(int ra){
	int aux;
	aux = floor(ra/TAM);
	return ( (ra - TAM)* aux );
	//return ra%TAM;
};

void inicializaTab(tipoTabHash *tab){
	int i;
	for(i = 0; i < TAM; i++){
		tab[i].chave = -1;
		tab[i].prox = NULL;
	}

}

aluno novoAluno(char nome[],int ra){
	tipoAluno *novo;
	novo = (tipoAluno*) malloc( sizeof(tipoAluno) );
	strcpy(novo->nome,nome);
	novo->ra = ra;
	return novo;
}


void InsereTab(tipoTabHash *tab,int cod,char nome[]){
	tipoTabHash aux;
	int pos;
	pos = fHash(cod);
	printf("pos: %d\n",pos);
	aux = tab[pos]
	while( aux->prox != NULL){
		aux = aux->prox;
	}
	aux->prox = (tipoTabHash*) malloc( sizeof(tipoTabHash) );
	aux->prox.aluno = novoAluno(nome,cod);
	aux->prox.chave = pos;
};

aluno BuscaAluno(int cod){
	aluno aux;

	aux = fHash(cod);

	while(aux->prox != NUll){
		if(aux->chave == cod){
			return aux;
		}
	}
	return NULL;
}

int Menuzin(int op,tipoTabHash *tab){
	char nome[20];
	int ra;
    system("clear");
    switch(op){
        case 1:
            scanf("%s",nome);
            scanf("%d",&ra);
            InsereNaTab(tabela,ra);
            break;
        case 2:
            puts("Digite o ra do aluno");
            scanf("%d",&ra);
            aluno = Busca(&tabela,ra);
            if(aluno == NULL){
                puts("Nao cadastrado");
            }else{
                printf("%s",aluno.nome);
                printf("%d",aluno.ra);
                
            }
            break;
        default:
            break;
    
    }


};



int main(){
	tipoTabHash Tab[TAM];
	int op;
	inicializaTab(Tab);

	do{
	puts("Digite a opção:\n 1-Guardar\n 2-Buscar\n 0-Sair");
    scanf("%d", &op);
    Menuzin(op,Tab);

	}while(op != 0);


	return 0;
}