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
        arr[i] = rand()%100;
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

    //para visualizar o funcionamento do algoritmo podemos descomentar os prints
    //a seguir, para perceber como será o encadeamento das chamadas:
    //a ideia é que o array será dividido em subarrays até chegar em um único elemento
    //depois disso ordenaremos os elmentos da seguinte forma, que pode ser ilustrada como
    //duas pilhas de baralho, na n-ésima resolução da chamada, teremos duas pilhas de tamanho (n/2)+1
    //ordenadas internamente, assim para construir uma única pilha ordenada (que posteriormente será
    // uma das duas pilhas no processo de ordenação) devemos olhar as cartas do topo e escolher a menor
    //até chegarmos ao fim das pilhas. Para isso inserimos cartas sentinelas, é conveniente usar (RAND_MAX) 
    //por ser o maior valor inteiro, e supomos que nosso vetor de entrada terá apenas numeros < rand_max


    printf("chamada beg: %d, end: %d\n", beg, end);
    if(beg < end){
        int mid = floor((beg+end)/2);

        merge_sort(arr, beg, mid);
        merge_sort(arr, mid+1, end);
        merge(arr, beg, mid, end);
    }
    printf("resolução da chamada beg: %d, end: %d\n", beg, end);
    
    return;
}

void merge(int arr[], int beg, int mid, int end){

    int n1 = mid - beg + 1; //aqui temos o numero de elementos do vetor da esquerda.
    int n2 = end - mid; //aqui temos o numero de elementos do vetor da direita.
    
    int l[n1+1]; //adicionamos um termo para a carta sentinela que representa o fim (rand_max)
    int r[n2+1];

    for(int i = 0; i < n1; i++){
        l[i] = arr[beg + i]; //o subarray da esquerda recebe metade do array incial.
    }
    for(int j = 0; j < n2; j++){
        r[j] = arr[mid + 1 + j]; //o subarray da direita recebe a segunda metade
    }
    l[n1] = RAND_MAX;
    r[n2] = RAND_MAX;
    
    int i = 0;
    int j = 0;
    int k = beg;

    for(k = beg; k <= end; k++){
        
        //aqui é feita a comparação entre as pilhas, a pilha parcialmente ordenada 
        //(arr[]) recebe a menor, sempre. A primeira vez que essa função recebe os subarrays
        //serão de elemento único (assim a ordenação se manterá correta, pois as pilhas estão ordenadas)
        //assim, na segunda chamada, novamente haverá um elemento em cada subarray, pois, iremos analisar
        //os subarrays 0->0 e 1->1, que são subarrays do subarray 0->3, ao resolver a chamada de 0->1 
        //então será chamado 2->3, então será analisado os subarrays 2->2 e 3->3, e aí então será
        //resolvida a chamada 0->3, usando os subarrays de tamanho 2 já ordenados 0->1 e 2->3,
        //essa lógica segue subindo pela "árvore de recursão" do nosso array.

        if(l[i] < r[j] && l[i] != RAND_MAX){
            arr[k] = l[i];
            ++i;
        }
        else{
            arr[k] = r[j];
            ++j;
        }
    }
}

void print_arr(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}