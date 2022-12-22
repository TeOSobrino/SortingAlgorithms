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
    printf("Insert the number of elements in array\n");
    scanf("%d", &arr_size);
    int *arr = malloc(arr_size*sizeof(int));

    int limiter;
    printf("Insert the maximum value of array elements, or 0 to not limit:\n");
    scanf("%d", &limiter);
    if(limiter == 0) limiter = RAND_MAX;
    
    for(int i = 0; i < arr_size; i++){
        arr[i] = rand()%limiter;
    }

    printf("Insert the base in which radix sort will be performed:\n");
    int base;
    scanf("%d", &base);
    if(base < 2) base = 256;
    else base = (int)(pow(2, ((int)log2(base)))); //Guarantee that base is a power of 2

    print_arr(arr, arr_size);
    radix_sort(arr, arr_size, base);
    
    if(is_ordered(arr, arr_size)){
        print_arr(arr, arr_size);
        printf("EXIT_SUCCESS\n");
    }
    else printf("Error in sorting\n");
    
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

//a counting sort that limits itself by the shift.
void counting_sort_base_x(int *arr, int arr_size, int shift, int base){

    int curr_max = get_max_base_x(arr, arr_size, shift, base);

    int *count_arr = calloc(curr_max+1, sizeof(int));
    int *ordered_arr = calloc((arr_size), sizeof(int));

    //the ith position has the number of elements equal to i.
    for(int i = 0; i < arr_size; i++){

        int index = (arr[i]>>shift)%base;
        count_arr[index] += 1;
    }

    //the ith position has the number of elements <= i;
    for(int i = 1; i <= curr_max; i++){

        count_arr[i] += count_arr[i-1];
    }

    //this loop must be performed carefully, in order to maintain sorting stability,
    //in our case, we begin by the end of the counting array, but other conditions can
    //be applied succesfully
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

    int max = get_max_base_x(arr, arr_size, 0, 0); //find the array's global maximum 
    int shift_increase = (int)floor(log2(base));
    
    int shift = 0;
    do{
        //prints to better understand each procedure step:

        //printf("shift = %d\n", shift);
        //printf("max>>shitf = %d\n", max>>shift);

        counting_sort_base_x(arr, arr_size, shift, base);
        shift += shift_increase;
    }while (max>>shift > base); //while the array maximum is less than the base, we
    //need to keep repeating the counting sort procedure
    
    counting_sort_base_x(arr, arr_size, shift, base); //when the condition is met, we perform the
    //final counting sort procedure, that sorts all the numbers that are lesser than the base, shifted
    //by a certain amount (that depends on the global array maximum).
    
}

void print_arr(int *arr, int size_arr){

    for(int i = 0; i < size_arr; i++){

        printf("%d ", arr[i]);
    }
    printf("\n");
}

//function to verify if the array is ordered
char is_ordered(int *arr, int arr_size){

    for(int i = 1; i < arr_size; i++) 
        if(arr[i] < arr[i-1]) return 0;
        
    return 1;
}