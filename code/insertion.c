#include<stdio.h>
#include<stdlib.h>
#define ARR_SIZE 100

void print_array(int *vetor);
void insertion_sort(int *vetor);

int main(int argc, char **argv){

    int vetor_para_ordenar[100];
    for(int i = 0; i < ARR_SIZE; i++){
        vetor_para_ordenar[i] = i;
    }
    print_array(vetor_para_ordenar);
    insertion_sort(vetor_para_ordenar);
    printf("\n");
    print_array(vetor_para_ordenar);

    return 0;
}

void print_array(int *vetor){
    for(int i = 0; i < ARR_SIZE; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void insertion_sort(int *vetor){

    for(int j = 1; j < ARR_SIZE; j++){
        int key = vetor[j];
        int i = j-1;

        while(i >= 0 && vetor[i] < key){
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = key;
    }
}