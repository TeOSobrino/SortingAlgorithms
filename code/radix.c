#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//comments here are in portuguese, radix_any_base contians english comments.

void print_array(int *v, int size_v);
void counting_sort(int *v, int size_v, int maior, int exp);
int *radix_sort(int *v, int size_v, int maior);
int get_max(int *v, int size_v, int i);


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

    int *k = radix_sort(v, n, maior+1);
    print_array(k, n);

    return 0;
    
}

int get_max(int *v, int size_v, int i){

    int m = (v[0]/i)%10;

    for(int j = 1; j < size_v; j++){
        
        if((v[j]/i)%10 > m) m = (v[j]/i)%10;
    }

    return m;
}

int *radix_sort(int *v, int size_v, int maior){


    for(int i = 1; maior/i > 0; i*=10){
        int m = get_max(v, size_v, i);
        counting_sort(v, size_v, m+1, i);
    }

    return v;
}

//aqui é feito um counting sort normal, porém como a execução
//deve ser apenas no dígito atual, o vetor de contagem terá
//no máximo tamanho 11 e a posição a ser incrementada é
//(v[j]/exp)%10, exp = 1, 10, 100, ... até max(v)/exp = 0.

void counting_sort(int *v, int size_v, int maior, int exp){

    int *count_array = calloc(maior, sizeof(int));

    int *ordered_array = calloc(size_v, sizeof(int));

    for(int j = 0; j < size_v; j++){

        short index = (v[j]/exp)%10;
        count_array[index] += 1;
    }


    for(int j = 1; j < maior; j++){

        count_array[j] += count_array[j-1];
    }

    for(int j = size_v-1; j >= 0; j--){

        short index = (v[j]/exp)%10;
        ordered_array[count_array[index]-1] = v[j];
        count_array[index] -= 1;
    }

    free(count_array);
    for(int j = 0; j < size_v; j++){
        v[j] = ordered_array[j];
    }
    free(ordered_array);
    return;

}

void print_array(int *v, int size_v){
    for(int i = 0; i < size_v; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}