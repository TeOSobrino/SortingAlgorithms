
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void insertion_sort(int *vetor, int v_size);

void merge(int *arr, int beg, int mid, int end);
void merge_sort(int* arr, int beg, int end);

void max_heapify(int *v, int size_v, int index);
void build_max_heap(int *v, int size_v);
void heap_sort(int *v, int size_v);

void quicksort(int *vetor, int ini, int fim);
int particao(int *vetor, int ini, int fim);
int escolhe_pivo(int *v, int ini, int fim);

int *counting_sort(int *v, int size_v, int maior);

void print_array(int *v, int size_v);
void swap(int *a, int *b);