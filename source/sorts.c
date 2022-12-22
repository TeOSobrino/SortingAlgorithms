#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<sorts.h>

void swap(int *a, int *b){
	
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void print_array(int *arr, int size_v){

    for(int i = 0; i < size_v; i++){

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

void merge(int arr[], int beg, int mid, int end){

    int n1 = mid - beg + 1; //number of elements in left array.
    int n2 = end - mid; //number of elements in right array.
    
    int l[n1+1]; //we add one more element for the sentinel element
    int r[n2+1];

    for(int i = 0; i < n1; i++)
        l[i] = arr[beg + i]; //the first half of the array is put into the left subarray
    
    for(int j = 0; j < n2; j++)
        r[j] = arr[mid + 1 + j]; //the second half is punt into the right subarray
    
    l[n1] = RAND_MAX; //sentinel element, in order to use for loops
    r[n2] = RAND_MAX;
    
    int i = 0;
    int j = 0;
    int k = beg;

    for(k = beg; k <= end; k++){
    
        //comparison between the left and right subarrays
        if(l[i] < r[j]){
            arr[k] = l[i];
            i++;
        }
        else{
            arr[k] = r[j];
            j++;
        }
    }
}

void merge_sort(int arr[], int beg, int end){

    //merge sort will divide the array into two sub-arrays, each with half the original
    //array size, until we reach a 1-element array (this array is always ordered). Then we
    //proceed to the merge procedure, in which we compare the first element in each array, insert 
    //the smaller into the ordered array, repeat until one of the arrays is empty. The ordered merged 
    //array will be submitted to another merge procedure, until it reaches the original array size.  

    //as this was my first non-trivial recursive algorithm, the following prints helped me
    //visualize the recursion tree and how it works

    //printf("function call: beg: %d, end: %d\n", beg, end);
    if(beg < end){
        int mid = floor((beg+end)/2);

        merge_sort(arr, beg, mid);
        merge_sort(arr, mid+1, end);
        merge(arr, beg, mid, end);
    }
    //printf("function resolution: beg: %d, end: %d\n", beg, end);
    
    return;
}

void max_heapify(int *v, int size_v, int index){

    int left, right, greater;
    greater = index;
    left = 2*index;
    right = 2*index+1;

    if(left <= size_v && v[left] > v[greater]) greater = left;
    if(right <= size_v && v[right] > v[greater]) greater = right;
    
    if(greater != index){
        swap(&v[greater], &v[index]);
        max_heapify(v, size_v, greater);
    }
}

void build_max_heap(int *v, int size_v){

    for(int i = size_v/2; i > 0; i--){
        max_heapify(v, size_v, i);
    }
}

void heap_sort(int *v, int size_v){

    build_max_heap(v, size_v);

    for(int i = size_v; i > 0; i--){
        swap(&v[1], &v[i]);
        size_v--;
        max_heapify(v, size_v, 1);
    }

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