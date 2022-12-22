
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void insertion_sort(int *vetor, int n);

void merge_sort(int* arr, int beg, int end);

void heap_sort(int *v, int size_v);

void quicksort(int *vetor, int ini, int fim);

int *counting_sort(int *v, int size_v, int maior);

void radix_sort(int *arr, int arr_size, int base);

void print_array(int *v, int size_v);
void swap(int *a, int *b);
char is_ordered(int *arr, int arr_size);