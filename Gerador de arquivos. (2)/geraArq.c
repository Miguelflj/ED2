/* Gerador arquivos contendo vertices e arestas com peso 1
 * Entre 50 e 100 graus 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_arquivo(int quantidade,int valor);
int Menorvetor(int *vetor,int valor);

int Menorvetor(int *vetor,int valor){
	int i=0,menor=0,vertice;
	menor=vetor[i];
	for(i=0;i<valor;i++){
		if(vetor[i] < menor){
			menor=vetor[i];
		}
	}
	printf("[x]Menor grau -> [%d]\n",menor);
}
void gera_arquivo(int quantidade,int valor){
	int i=0,j=0,numero=0,flag=0,b=0,grau=0,controle=0,k=0;
	int vetor[valor];
	srand(time(NULL));
	
	system("mkdir arquivos-INT");
	for (k = 0; k < quantidade; k++){

		FILE *file;
		char nomearq[1000];

		sprintf(nomearq, "arquivos-INT/Arq[%d][%d].txt",k,valor);
		file = fopen(nomearq, "w");
		if(file == NULL){
			printf("Erro na abertura do arquivo!\n");
		}
		fprintf(file,"&vertices\n");
		for (b=0; b < valor; b++){			   
			fprintf(file,"%d\n",b);		 
		}
		fprintf(file,"&arestas\n");
		for(i=0; i < valor; i++){
			vetor[i]=0;
		}
		for(i=0; i < valor; i++){
			grau=(rand()%50)+50;
			if((vetor[i]+grau >= 100) && ((vetor[i]<=50))){
				grau = grau-vetor[i];
				printf("[x]Grau->%d\n",grau+vetor[i]);
				while(vetor[i]+grau < 50){
					grau=grau+1;
				}			
			}
			if((vetor[i] < 100) && (vetor[i]+grau <= 100)){
				for(b=0; b < grau; b++){
					flag=0;
					while(flag != 1){
						controle=(rand()%valor);
						if(vetor[controle]<100){
							vetor[controle]++;
							fprintf(file,"%d %d 1\n",i,controle);
							vetor[i]++;
							flag = 1;
						}
					}
				}
			}
		}
		fclose(file);
		Menorvetor(vetor,valor);
		printf("[%d]Arquivo gerado\n",k+1);
	}

}
int main(int argc, char *argv[ ]){

	if(argc==3){
		int quantidade=atoi(argv[1]);
		int valor=atoi(argv[2]);
		system("clear");
		gera_arquivo(quantidade,valor);
	}
	else{
		system("clear");
		printf("\n\t[x]Utilize %s 'quantidade de arquivos' 'quantidade de valores'\n\t[EX]%s 3 20000\n",argv[0],argv[0]);
		return 0;
	}
}