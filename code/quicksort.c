#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quicksort(int *vetor, int beg, int end);
int partition(int *vetor, int beg, int end);
int choose_pivot(int *v, int beg, int end);
void swap(int *a, int *b);
void print_vetor(int *v, int tam);

int main(int argc, char **argv){

	printf("Insert the number of elements in the array:\n");
	int n;
	scanf("%d", &n);

	int *v = malloc(n*sizeof(int));
	
	srand(time(NULL));
	for(int i = 0; i < n; i++){
		v[i] = rand( )%(6*n);
	}
	
	quicksort(v, 0, n);
	print_vetor(v, n);
	free(v);

	return 0;
}

//chooses pivot using 3-median
int choose_pivot(int *v, int beg, int end){
	
	int pivot;

	if( beg >= end-1){
		return v[beg];
	}

	int mid = ((end + beg)/2);

	if(v[beg] < v[end]){

		if(v[mid] > v[end]) pivot = end;
		else pivot = mid;
	}

	else{

		if(v[mid] > v[beg]) pivot = beg;
		else pivot = mid; 
	}
	
	swap((v+beg), (v+pivot));
	return v[beg];
}

//partitions the array in two parts using the pivot as divisor
//(smaller on the left, bigger on the right). Notice that, best
//case scenario, this will wind up as a merge sort, without auxiliar memory.
int partition(int *v, int beg, int end){
	
	int pivot = choose_pivot(v, beg, end);
	
	int i = beg+1;
	int j = end;
	
	while(i <= j){

		while(i<=end && v[i] <= pivot){
			i++;
		}

		while(j>=beg && v[j] > pivot){
			j--;	
		}

		if(i < j) swap((v+i), (v+j));
	}
	
	swap((v+beg), (v+j));		
	return j;
}

//quicksort will be partitioning the array, until the last partition occurs
//when we obtain the sorted array.
void quicksort(int *v, int beg, int end){
	
	//base condition
	if(beg >= end) return;
	
	int pivot_position = partition(v, beg, end);
	quicksort(v, beg, pivot_position-1);
	quicksort(v, pivot_position+1, end);
}

void swap(int *a, int *b){
	
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void print_vetor(int *v, int tam){
	
	for(int i = 0; i < tam; i++)
		printf("%d ", v[i]);
	
	printf("\n");
}
