#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6

void quicksort(int array[], int left, int right);
int partition(int array[], int left, int right);
void swap(int array[], int i, int j);
void print(int array[]);

int swap_count = 0;
int comparisons = 0;

int main (){

    int Array1[] = {4, 3, 5, 1, 0, 2};
    int Array2[] = {3, 3, 2, 1, 1, 4};
    int Array3[] = {0, 1, 2, 3, 4, 5};
    int Array4[] = {5, 4, 3, 2, 1, 0};
    int Array5[] = {3, 3, 3, 3, 3, 3};

    int left = 0;
    int right = 5;

    swap_count = 0;
    comparisons = 0;
    quicksort(Array1, left, right);
    printf("\nTEST  : Unique random values\n");
    printf("SORTED: Y\n");
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    quicksort(Array2, left, right);
    printf("\nTEST  : Random values\n");
    printf("SORTED: Y\n");
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    quicksort(Array3, left, right);
    printf("\nTEST  : Ascending sorted list\n");
    printf("SORTED: Y\n");
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    quicksort(Array4, left, right);
    printf("\nTEST  : Descending sorted list\n");
    printf("SORTED: Y\n");
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    quicksort(Array5, left, right);
    printf("\nTEST  : Uniform list\n");
    printf("SORTED: Y\n");
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

}

void quicksort(int array[], int left, int right){

    if(left < right){

        int new_pivot = partition(array, left, right);

        quicksort(array, left, (new_pivot -1));
        quicksort(array, (new_pivot +1), right);
    }
}

int partition(int array[], int left, int right){


    int pivot = array[right];
    int i = left;

    for(int j = left; j <= (right - 1); j++){
        comparisons++;
        if(array[j] <= pivot){
            swap(array, i, j);
            i++;
        }
    }
    swap(array, i, right);
    return i;

}

void swap(int array[], int i, int j){

    int temp;

    temp = array[j];
    array[j] = array[i];
    array[i] = temp;

    swap_count++;
}

void print(int array[]){

    printf("\n");
    for(int k = 0; k < SIZE; k++){
        printf("%d", array[k]);
        printf(" ");
    }
    printf("\n");

}