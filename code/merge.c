#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void merge(int *arr, int beg, int mid, int end);
void merge_sort(int* arr, int beg, int end);
void print_arr(int arr[], int size);

int main(int argc, char **argv){
    int n;
    scanf("%d", &n);
    int arr[n];

    srand(time(0));
    for(int i = 0; i < n; i++){
        arr[i] = rand()%1000;
        printf("%d ", arr[i]);
    }
    printf("\n");

    merge_sort(arr, 0, n-1); 

    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
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

void print_arr(int arr[], int size){
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}