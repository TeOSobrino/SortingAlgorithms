#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void counting_sort_base_x(int *arr, int arr_size, int shift, int base);
void radix_sort(int *arr, int arr_size, int base);
int get_max_base_x(int *arr, int arr_size, int shift, int base);
void print_arr(int *arr, int size_arr);
char is_ordered(int *arr, int size_arr);

int main(int argc, char **argv){

    srand(time(0));

    int arr_size = 0;
    printf("Insira o número de elementos no vetor:\n");
    scanf("%d", &arr_size);
    int *arr = malloc(arr_size*sizeof(int));
    //int arr[arr_size];

    int limiter;
    printf("Insira um limitante para os elementos, ou 0 para não limitar:\n");
    scanf("%d", &limiter);
    if(limiter == 0) limiter = RAND_MAX;
    
    for(int i = 0; i < arr_size; i++){
        arr[i] = rand()%limiter;
    }

    printf("Insira a base (potência de 2) para realizar o radix sort:\n");
    int base;
    scanf("%d", &base);
    if(base < 2) base = 256;
    //else base = (int)floor(log2(pow(2, base))); //tornamos base a potência de 2 mais próxima.

    print_arr(arr, arr_size);
    radix_sort(arr, arr_size, base);
    
    if(is_ordered(arr, arr_size)){
        print_arr(arr, arr_size);
        printf("EXIT_SUCCESS\n");
    }
    else printf("Erro de ordenação\n");
    
    return 0;
}

int get_max_base_x(int *arr, int arr_size, int shift, int base){

    if(base == 0) base = RAND_MAX;

    int max = ((arr[0]>>shift)%base);
    for(int i = 1; i < arr_size; i++){

        if((arr[i]>>shift)%base > max) max =  ((arr[i]>>shift)%base);
    }

    return max;
}

void counting_sort_base_x(int *arr, int arr_size, int shift, int base){

    int curr_max = get_max_base_x(arr, arr_size, shift, base);

    int *count_arr = calloc(curr_max+1, sizeof(int)); //inicializa com 0.
    int *ordered_arr = calloc((arr_size), sizeof(int));

    //a posição i tem o número de elementos = i;
    for(int i = 0; i < arr_size; i++){

        int index = (arr[i]>>shift)%base;
        count_arr[index] += 1;
    }

    //a posição i tem o número de elementos <= i;
    for(int i = 1; i <= curr_max; i++){

        count_arr[i] += count_arr[i-1];
    }

    //para a estabilidade do counting (e corretude do radix) é necessário começar do fim.
    for(int i = arr_size-1; i >= 0; i--){ 

        int index = (arr[i]>>shift)%base;
        ordered_arr[count_arr[index]-1] = arr[i];
        count_arr[index] -= 1;
    }
    
    for(int i = 0; i < arr_size; i++){

        arr[i] = ordered_arr[i];
    }

    free(count_arr);
    free(ordered_arr);

}

void radix_sort(int *arr, int arr_size, int base){

    int max = get_max_base_x(arr, arr_size, 0, 0); //sem shift e base achamos o máximo global do vetor.
    int shift_increase = (int)floor(log2(base));
    

    for(int shift = 0; ; shift+= shift_increase){
        printf("shift = %d\n", shift);
        printf("n>>shitf = %d\n", max>>shift);
        
        counting_sort_base_x(arr, arr_size, shift, base);
        
        if(max>>shift < base) break; 
    }
    
}

void print_arr(int *arr, int size_arr){

    for(int i = 0; i < size_arr; i++){

        printf("%d ", arr[i]);
    }
    printf("\n");
}

char is_ordered(int *arr, int arr_size){

    int x = arr[0];

    for(int i = 1; i < arr_size; i++){

        if(arr[i] < x) return 0;
        
        x = arr[i];
    }

    return 1;
}