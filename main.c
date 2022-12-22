#include<sorts.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main(void){

    int n = 10000;
    int v[n];

    for(int i = 0; i < n; i++){
        v[i] = rand();
    }

    printf("eba\n");
    radix_sort(v, n, 256);
    print_array(v, n);
    if( is_ordered(v, n)) printf("Ordered successfully\n");
    return 0;
}