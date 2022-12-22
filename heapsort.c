#include<stdio.h>
#include<stdlib.h>

void max_heapify(int *v, int size_v, int index);
void build_max_heap(int *v, int size_v);
void heap_sort(int *v, int size_v);
void print_array(int *v, int size_v);
void swap(int *a, int *b);

int main(){

    int size_v = 7;
    int *v = malloc(size_v*sizeof(int));
    
    for(int i = 1; i < size_v; i++){
        v[i] = rand()%100;
    }

    print_array(v, size_v);
    heap_sort(v, size_v-1);
    print_array(v, size_v);

    return 0;
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

void print_array(int *v, int size_v){
    for(int i = 0; i < size_v; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){

    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}