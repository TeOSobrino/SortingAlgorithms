
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"sorts.h"



int escolhe_pivo(int *v, int ini, int fim){
	
	int pivo;

	if( ini >= fim-1){
		return v[ini];
	}

	int meio = ((fim + ini)/2);

	if(v[ini] < v[fim]){

		if(v[meio] > v[fim]) pivo = fim;
		else pivo = meio;
	}

	else{

		if(v[meio] > v[ini]) pivo = ini;
		else pivo = meio; 
	}
	
	return v[pivo];
}

void quicksort(int *v, int ini, int fim){
	
	//parada
	if(ini >= fim) return;
	
	int pos_pivo = particao(v, ini, fim);
	quicksort(v, ini, pos_pivo-1);
	quicksort(v, pos_pivo+1, fim);
}


int particao(int *v, int ini, int fim){
	
	int pivo = escolhe_pivo(v, ini, fim);
	
	int i = ini+1;
	int j = fim;
	
	while(i <= j){

		while(i<=fim && v[i] <= pivo){
			i++;
		}

		while(j>=ini && v[j] > pivo){
			j--;	
		}

		if(i < j) swap((v+i), (v+j));
	}
	
	swap((v+ini), (v+j));		
	return j;
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

void insertion_sort(int *vetor, int v_size){

    for(int j = 1; j < v_size; j++){
        int key = vetor[j];
        int i = j-1;

        while(i >= 0 && vetor[i] < key){
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = key;
    }
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

void swap(int *a, int *b){

    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int *counting_sort(int *v, int size_v, int maior){

    int *count_array = calloc(maior, sizeof(int));
    //o vetor count_array armazena na posição i a quantidade de elementos menores ou iguais
    //à i (um elemento do vetor original), assim i deve ser igual ao maior elemento
    //do vetor original, ou seja, todos os elementos do vetor a ser ordenados devem 
    //ser menores que um dado limite k.

    int *ordered_array = calloc(size_v, sizeof(int));
    //o vetor ordered_array será o vetor ordenado.

    for(int j = 0; j < size_v; j++){

        count_array[v[j]] += 1;
        //a posição count_array[i] contém o número de elementos iguais a i no vetor v.
    }

    //print_array(count_array, maior);

    for(int j = 1; j < maior; j++){

        count_array[j] += count_array[j-1];
        //agora a posição i de count_array tem o número de elementos menores ou iguais a i.
    }

    for(int j = size_v-1; j >= 0; j--){

        ordered_array[count_array[v[j]]-1] = v[j];
        count_array[v[j]] -= 1;
        
        //para um elemento dado do vetor v, v[j], qualuqer, sabemos que existem 
        //count_array[v[j]] elementos menores ou iguais que ele, assim no vetor ordenado
        //arr o elemento v[j] ocupa a posição arr[count_array[v[j]]-1].
   
    }

    free(count_array);
    return ordered_array;

}

void print_array(int *v, int size_v){
    for(int i = 0; i < size_v; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}