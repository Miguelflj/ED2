#include <stdio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include <time.h>//necessário p/ função time()
 
//MAX receberá a quantidade de valores a serem gerados
#define MAX 200000

typedef struct tipoLista{
    int lista[MAX];
    int vetor[MAX];
    
    
}tipoLista;

int main()
{
    int i,k;
    int controle,flag=1;
    int cont = 0;
    int as;
    tipoLista vet;
    FILE *arqv;
    //nome do arquivo de saida com numeros aleatorios que nao se repetem
    arqv = fopen("lInput100k.txt","w");
    srand(time(NULL));

    if(arqv == NULL){
        printf("Erro na abertura do arquivo.\n");
    }
    
    for(i=0; i < MAX; i++){
        do{
            flag = 1;
            //gera valores no intervalo de 1 a 999999
            controle = (1+rand() % 9999);
            as = (1+rand() % 10000);
            //verifica valores repetidos na vetor
            for(k=0; k < cont; k++){
                //if(controle == vet.lista[k]){
                // se encontrado, repete  o processo de gerar.
                    //flag = 0;
                    k = cont;
                
            }
    
        }while(flag == 0);
        vet.lista[i] = controle;
        vet.vetor[i] = as;
        cont++;
    }
    // grava todos os valores num arquivo
    for(i=0; i<MAX-100000; i++){
        fprintf(arqv,"%d-%d livro%d\n", vet.lista[i],vet.lista[i+100000],i);
    }

     return 0;
}