#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quicksort(int *vetor, int ini, int fim);
int particao(int *vetor, int ini, int fim);
int escolhe_pivo(int *v, int ini, int fim);
void swap(int *a, int *b);
void print_vetor(int *v, int tam);

int main(int argc, char **argv){
	int n = 1000000;
	int *v = malloc(n*sizeof(int));
	
	srand(time(NULL));

	for(int i = 0; i < n; i++){
		v[i] = rand( )%(6*n);
	}
	
	quicksort(v, 0, n);
	
	//print_vetor(v, n);

	free(v);
	return 0;
}

int escolhe_pivo(int *v, int ini, int fim){
	
	int pivo;

	if( ini >= fim-1){
		return v[ini];
	}

	int meio = ((fim + ini)/2);

	if(v[ini] < v[fim]){

		if(v[meio] > v[fim]) pivo = fim;
		else pivo = meio;
	}

	else{

		if(v[meio] > v[ini]) pivo = ini;
		else pivo = meio; 
	}
	
	return v[pivo];
}

void quicksort(int *v, int ini, int fim){
	
	//parada
	if(ini >= fim) return;
	
	int pos_pivo = particao(v, ini, fim);
	quicksort(v, ini, pos_pivo-1);
	quicksort(v, pos_pivo+1, fim);
}


int particao(int *v, int ini, int fim){
	
	int pivo = escolhe_pivo(v, ini, fim);
	
	int i = ini+1;
	int j = fim;
	
	while(i <= j){

		while(i<=fim && v[i] <= pivo){
			i++;
		}

		while(j>=ini && v[j] > pivo){
			j--;	
		}

		if(i < j) swap((v+i), (v+j));
	}
	
	swap((v+ini), (v+j));		
	return j;
}

void swap(int *a, int *b){
	
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void print_vetor(int *v, int tam){
	
	for(int i = 0; i < tam; i++){
		printf("%d ", v[i]);
	}
	printf("\n");
}
