#include <stdio.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include <time.h>//necessário p/ função time()
 
//MAX receberá a quantidade de valores a serem gerados
#define MAX 20000

typedef struct tipoLista{
    int lista[MAX];
    
    
}tipoLista;

int main()
{
    int i,k;
    int controle,flag=1;
    int cont = 0;
    tipoLista vet;
    FILE *arqv;
    //nome do arquivo de saida com numeros aleatorios que nao se repetem
    arqv = fopen("inputT20k-3.txt","w");
    srand(time(NULL));
    if(arqv == NULL){
        printf("Erro na abertura do arquivo.\n");
    }
    
    for(i=0; i < MAX; i++){
        do{
            flag = 1;
            //gera valores no intervalo de 1 a 999999
            controle = (1+rand() % 100000);
            //verifica valores repetidos na vetor
            for(k=0; k < cont; k++){
                //if(controle == vet.lista[k]){
                // se encontrado, repete  o processo de gerar.
                    //flag = 0;
                    k = cont;
                
            }
    
        }while(flag == 0);
        vet.lista[i] = controle;
        cont++;
    }
    // grava todos os valores num arquivo
    for(i=0; i<MAX; i++){
        fprintf(arqv,"%d\n", vet.lista[i]);
    }

     return 0;
}
