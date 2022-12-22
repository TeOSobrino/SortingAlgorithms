#include<stdio.h>
#include<stdlib.h>

void print_array(int *vetor, int n);
void insertion_sort(int *vetor, int n);

int main(int argc, char **argv){

    int n = 1000;
    int vetor_para_ordenar[100];
    for(int i = 0; i < n; i++){
        vetor_para_ordenar[i] = i;
    }
    print_array(vetor_para_ordenar, n);
    insertion_sort(vetor_para_ordenar, n);
    printf("\n");
    print_array(vetor_para_ordenar, n);

    return 0;
}

void print_array(int *vetor, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void insertion_sort(int *vetor, int n){

    for(int j = 1; j < n; j++){
        int key = vetor[j];
        int i = j-1;

        while(i >= 0 && vetor[i] < key){
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = key;
    }
}