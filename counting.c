#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void print_array(int *v, int size_v);
int *counting_sort(int *v, int size_v, int maior);

int main(int argc, char **argv){
    int n;
    scanf("%d", &n);
    int v[n];
    int maior = 0;

    srand(time(NULL));

    for(int i = 0; i < n; i++){
       
        v[i] = rand()%200;
        if(v[i] > maior) maior = v[i];
    }

    print_array(v, n);
    printf("\n\n");

    int *k = counting_sort(v, n, maior+1);

    print_array(k, n);

    free(k);

    return 0;
    
}

int *counting_sort(int *v, int size_v, int maior){

    int *count_array = calloc(maior, sizeof(int));
    //o vetor count_array armazena na posição i a quantidade de elementos menores ou iguais
    //à i (um elemento do vetor original), assim i deve ser igual ao maior elemento
    //do vetor original, ou seja, todos os elementos do vetor a ser ordenados devem 
    //ser menores que um dado limite k.

    int *ordered_array = calloc(size_v, sizeof(int));
    //o vetor ordered_array será o vetor ordenado.

    for(int j = 0; j < size_v; j++){

        count_array[v[j]] += 1;
        //a posição count_array[i] contém o número de elementos iguais a i no vetor v.
    }

    //print_array(count_array, maior);

    for(int j = 1; j < maior; j++){

        count_array[j] += count_array[j-1];
        //agora a posição i de count_array tem o número de elementos menores ou iguais a i.
    }

    for(int j = size_v-1; j >= 0; j--){

        ordered_array[count_array[v[j]]-1] = v[j];
        count_array[v[j]] -= 1;
        
        //para um elemento dado do vetor v, v[j], qualuqer, sabemos que existem 
        //count_array[v[j]] elementos menores ou iguais que ele, assim no vetor ordenado
        //arr o elemento v[j] ocupa a posição arr[count_array[v[j]]-1].
   
    }

    free(count_array);
    return ordered_array;

}

void print_array(int *v, int size_v){
    for(int i = 0; i < size_v; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}