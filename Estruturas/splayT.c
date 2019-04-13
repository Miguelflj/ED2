/* 

	UFMT - CCOMP
	ED2 - IVAIRTON
	MIGUEL FREITAS

	SPLAY TREE

	*/

#include <stdio.h>
#include <stdlib.h>


typedef struct splayT{

	int valor;
	struct splayT *esq, *dir;

}splayT;



// Protótipos de funções

//aloca novo nó
splayT *novoNo(int valor);
//rotações
splayT *ZigDir(splayT *v,splayT *u);
splayT *ZigEsq(splayT *v, splayT *u);
splayT *ZigZigDir(splayT *v, splayT *u, splayT *w);
splayT *ZigZigEsq(splayT *v,splayT *u, splayT *w);
splayT *ZigZagDir(splayT *v,splayT *u, splayT *w);
splayT *ZigZagEsq(splayT *v,splayT *u, splayT *w);

//controle de inserção e a função splay
int FuncSplay(splayT *no, int valor,splayT **pai,splayT **raiz);
splayT *insereSplay(splayT *no,int valor);
splayT *ChamaIns(splayT *T, int valor);
//impressao em ordem (arvore lateral)
void Impressao(splayT *raiz,int n);




int main(){
	splayT *T;
	int op, vlr;
	T = NULL;
	puts("SPLAY TREE")
;	do{

		puts("1 - Inserção\n2 - Impressão \n0 - Sair");
		printf("Opção: ");
		scanf("%d",&op);
		system("clear");
		switch(op){
			case 1:
				puts("Digite o valor que deseja inserir");
				scanf("%d",&vlr);
				T =	ChamaIns(T,vlr);
				system("clear");
				break;
			case 2:
				Impressao(T,0);
				break;
			case 0:
				break;
			default:
				break;
		}

	}while( op != 0);
	
	/*

	T =	ChamaIns(T,10);
	T =	ChamaIns(T,8);
	T =	ChamaIns(T,1);
	T =	ChamaIns(T,466);
	T =	ChamaIns(T,70);
	Impressao(T,0);
	*/
	return 0;
}



splayT *novoNo(int valor){
	splayT *no;

	no = (splayT*) malloc(sizeof(splayT));
	no->valor = valor;
	no->esq = NULL;
	no->dir = NULL;

	return no;
}


splayT *ZigDir(splayT *v,splayT *u){

	u->esq = v->dir;
	v->dir = u;

	return v;
}

splayT *ZigEsq(splayT *v, splayT *u){

	u->dir = v->esq;
	v->esq = u;

	return v;
}

splayT *ZigZigDir(splayT *v, splayT *u, splayT *w){

	w->esq = u->dir;
	u->esq = v->dir;

	u->dir = w;
	v->dir = u;
	
	return v;

}

splayT *ZigZigEsq(splayT *v,splayT *u, splayT *w){

	w->dir = u->esq;
	u->dir = v->esq;

	u->esq = w;
	v->esq = u;
	
	return v;
}


splayT *ZigZagDir(splayT *v,splayT *u, splayT *w){
	
	w->esq = v->dir;
	u->dir = v->esq;

	v->esq = u;
	v->dir = w;

	return v;
}


splayT *ZigZagEsq(splayT *v,splayT *u, splayT *w){

	w->dir = v->esq;
	u->esq = v->dir;

	v->dir = u;
	v->esq = w;

	return v;

}



int FuncSplay(splayT *no, int valor,splayT **pai,splayT **raiz){
	int flag;
	splayT *u, *v;
	if(no != NULL){
		if( no->valor == valor) {
			return 1;
		} else {
			if(valor < no->valor){
				flag = FuncSplay(no->esq, valor,&no,raiz);

				if(flag == 1 ){
					if( no == (*raiz) ){
						(*raiz) = ZigDir(no->esq,no);

						return 1;
				} else {
					return 2;
				}

				}else if(flag == 2){
					u = no->esq;

					if(valor < u->valor){
						v = u->esq;
						// zig zig
						if(no == (*raiz)){
							(*raiz) = ZigZigDir(v,u,no);
						} else { 
							if( (*pai)->valor < no->valor ){
								(*pai)->dir = ZigZigDir(v,u,no);
							} else {
								(*pai)->esq = ZigZigDir(v,u,no);	
							}

							
						}


					} else {
						//zig zag
						v = u->dir;

						if(no == (*raiz)){
							(*raiz) =ZigZagDir(v,u,no);
						} else { 

							if( (*pai)->valor < no->valor ){
								(*pai)->dir = ZigZagDir(v,u,no);
							} else {
								(*pai)->esq = ZigZagDir(v,u,no);	
							}
							
						}
					}

					return 1;
					
				} else {

					// flag == 0 não faz nada

					return 0;
				}

				} else {
					flag = FuncSplay(no->dir, valor,&no,raiz);

					if(flag == 1 ){
						if( no == (*raiz) ){

							(*raiz) = ZigEsq(no->dir,no);
							return 1;

						} else {
							return 2;
						}

					}else if(flag == 2){
						u = no->dir;
						
						if(valor < u->valor){
							v = u->esq;
							// zig zag
							if(no == (*raiz)){
								(*raiz) = ZigZagEsq(v,u,no);
							} else { 

								if( (*pai)->valor < no->valor ){
									(*pai)->dir = ZigZagEsq(v,u,no);
								} else {
									(*pai)->esq = ZigZagEsq(v,u,no);
								}
								
							}

						} else {

							// zig zig
							v = u->dir;
							if(no == (*raiz)){
								(*raiz) = ZigZigEsq(v,u,no);
							} else { 
								if( (*pai)->valor < no->valor ){
									(*pai)->dir = ZigZigEsq(v,u,no);;
								} else {
									(*pai)->esq = ZigZigEsq(v,u,no);
								}

								
							}
						}

						return 1;
						
					} else {

						// flag == 0 não faz nada

						return 0;
					}

					}






		}
	} else {
		// valor inexistente na arvore ou arvore nula
		return 0;
	}

}


splayT *insereSplay(splayT *no,int valor){
	if(no == NULL){
		no = novoNo(valor);
		//inserção concluida
	} else {

		if(valor < no->valor ){
			no->esq = insereSplay(no->esq,valor);



		} else {
			no->dir = insereSplay(no->dir,valor);
		}

	}

	return no;
}


splayT *ChamaIns(splayT *T, int valor){
	
	splayT *raiz;

	T = insereSplay(T,valor);
	raiz = T;
	FuncSplay(T,valor,NULL,&raiz);  // no,valor,pai,raiz 

	return raiz;
}




void Impressao(splayT *raiz,int n){
    splayT *no;
    int i;
    no = (raiz);
    if(no != NULL){
        Impressao(no->dir,n+1);
        
        for(i = 0; i < n;i++){
            printf("\t");
        }
     	printf("(%d)\n",no->valor);
        
        Impressao(no->esq,n+1);
        
    }
}