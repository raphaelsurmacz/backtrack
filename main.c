/*==================================\\
||									||
||	Aluno: Raphael Augusto Surmacz	||
||	GRR20213405						||	
||									||
\\==================================*/

#include <stdio.h>
#include <stdlib.h>

int backtracking(int presAtual, int n_presentes, int peso_max, int removePeso, int valorAtual,
				 int pesoAtual, int *melhorValor,int *melhorIdx, int *presIdx, int *v_valor, int *v_peso){

	if ( presAtual >= n_presentes ){
		if(valorAtual > *melhorValor){
			*melhorValor = valorAtual;

			for (int i = 0; i < n_presentes; ++i)
				*(melhorIdx+i) = *(presIdx+i);
		}

		return *melhorValor;
	}

	*(presIdx+presAtual) = 0;
	backtracking(presAtual + 1, n_presentes, peso_max, removePeso, valorAtual, pesoAtual, melhorValor, melhorIdx, presIdx, v_valor, v_peso);

	if ( pesoAtual + *(v_peso+presAtual) <= peso_max ){

		pesoAtual = pesoAtual + *(v_peso+presAtual);
		valorAtual = valorAtual + *(v_valor+presAtual);
		removePeso = removePeso - *(v_peso+presAtual);
		*(presIdx+presAtual) = 1;


		if ( valorAtual + (removePeso * (*(v_valor+presAtual+1))) > *melhorValor )
			backtracking(presAtual + 1, n_presentes, peso_max, removePeso, valorAtual, pesoAtual, melhorValor, melhorIdx, presIdx, v_valor, v_peso);

		pesoAtual = pesoAtual - *(v_peso+presAtual);
		valorAtual = valorAtual - *(v_valor+presAtual);
		removePeso = removePeso + *(v_peso+presAtual);
		*(presIdx+presAtual) = 0;

	}

	return *melhorValor;
}

int main(){
	int n_presentes, peso_max, presAtual, removePeso, melhorValor, valorAtual, pesoAtual;
	int *v_valor, *v_peso, *melhorIdx, *presIdx;


	scanf("%d %d", &n_presentes, &peso_max);

	v_valor = malloc(n_presentes * sizeof(int));
	v_peso = malloc(n_presentes * sizeof(int));
	melhorIdx = malloc(n_presentes * sizeof(int));
	presIdx = malloc(n_presentes * sizeof(int));

	valorAtual = 0; pesoAtual = 0;
	removePeso = 0; melhorValor = 0;
	presAtual = 0;

	for (int i = 0; i < n_presentes; ++i)
		scanf("%d %d", (v_valor+i), (v_peso+i));


	for (int i = 0; i < n_presentes; ++i)
		removePeso = removePeso + *(v_peso+i);


	backtracking(presAtual, n_presentes, peso_max, removePeso, valorAtual, pesoAtual, &melhorValor, melhorIdx, presIdx, v_valor, v_peso);

	for (int i = 0; i < n_presentes; ++i)
		if(*(melhorIdx+i) == 1)
			printf("%d ", i);
	

	printf("\n%d\n", melhorValor);

	free(v_valor);
	free(v_peso);
	free(melhorIdx);
	free(presIdx);

	return 0;
}