/*

	UFMT - Ciência da Computação
	Trabalho 1 - ED 2 - Professor: Ivairton
	Miguel Freitas

*/

#include <stdio.h>
#include <stdlib.h>

// CONTÉM AS FUNÇÕES QUE LIDAM COM A MTZ ESPARSA E A CAPTURA DE TECLA
#include "funcMtzEspa(trab1).h"


#ifndef _TIPO_MTZ_
#define _TIPO_MTZ_

typedef struct Cel{
	int valor;
	int idxC;
	int idxL;
	// proxL é o de andar na linha(horizontal)
	struct Cel *proxL;
	// proxC é o de andar nas colunas(vertical)
	struct Cel *proxC;
	// sim, ta trocado, seu zé.

}Cel;


typedef struct Cabe{
	int idx;
	struct Cabe *proxCabe;
	struct Cel *proxCel;

}Cabe;

typedef struct mtzEspaca{
	struct Cabe *Linha;
	struct Cabe *Coluna;

}mtzEspaca;
#endif

/*
//Protótipos das funções
void InicializaCorner(mtzEspaca **corner);
Cabe *novoCabecalho(int pos);
void Cabecalho(mtzEspaca **corner,int posLinha,int PosColuna);
Cel *novaCelula(int valor,int posL,int posC);
void InsereCelula(mtzEspaca **corner,int linha,int coluna,int valor);
int VerificaCelula(Cel *navega,int posl,int posc,int valor);
void caminhaEguarda(mtzEspaca *corner);
*/


int main(){
	mtzEspaca *corner;

	InicializaCorner(&corner);
	puts("Ande com cuidado... \n");
	caminhaEguarda(corner);
	
	return 0;
}
