
#include <stdio.h>
#include <stdlib.h>



int main(){
	FILE *arq;
	char entrada[50],c,lix[5];

	int flag,nos,arcs,n1,n2,peso;

	arq = fopen("USA-road-d.CAL.gr","r");
	if( arq == NULL){
		puts("Deu ruim");
		return 0;
	}
	flag = 0;
	while(fscanf(arq,"%c",&c) != EOF){
		if( c == 'c'){
			fscanf(arq, "%[^\n]",entrada);
		} else if( c == 'p'){
			fscanf(arq, " sp %d %d",&nos,&arcs);
			printf("%c\n",c );
			printf("%d %d\n",nos,arcs);

			//printf("nos:%d arcs:%d\n",nos,arcs );

		} else if( c == 'a'){
			fscanf(arq, " %d %d %d",&n1,&n2,&peso);
			printf("n1:%d n2:%d peso:%d\n",n1,n2,peso);
			if(n1 == 1890815 || n2 == 1890815){
				flag++;
			}
			

		}


	}
	if( flag != 0){
		printf("ACHOUUU %d\n",flag);
	}
	return 0;
}