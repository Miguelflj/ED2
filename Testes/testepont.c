





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Test
{
	int cod;
	char name[100];

}Test;
typedef struct TestVet{

	struct Test *vet[3];

}TestVet;

Test *insere(int cod, char nome[]){
	Test *var;

	var = (Test*) malloc(sizeof(Test*));

	var->cod = cod;
	strcpy(var->name,nome);

	return var;
}	

void paulo(TestVet *a,int v,char bla[],int i){
	

	//a = NULL;
	
	Test *var = insere(v,bla);

	a->vet[i] = var;
	
}

void b(TestVet *a){
	printf("%d %s\n",a->vet[0]->cod,a->vet[0]->name);
	printf("%d %s\n",a->vet[1]->cod,a->vet[1]->name);
	printf("%d %s\n",a->vet[0]->cod,a->vet[0]->name);
}

int main(){
	TestVet *a;
	a = NULL;
	//a = (TestVet*) malloc(sizeof(TestVet*));
	//paulo(a,123,"luan",0);
	//paulo(a,124,"luam",1);
	int cod;
	cod = 4321;
	printf("%d\n",cod );

	//b(a);
	return 0;
}