#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6

void quicksort(int array[], int left, int right);
int partition(int array[], int left, int right);
void swap(int array[], int i, int j);
void print(int array[]);

int main (){

    int Array1[] = {4, 3, 5, 1, 0, 2};
    int Array2[] = {3, 3, 2, 1, 1, 4};
    int Array3[] = {0, 1, 2, 3, 4, 5};
    int Array4[] = {5, 4, 3, 2, 1, 0};
    int Array5[] = {3, 3, 3, 3, 3, 3};

    int left = 0;
    int right = 5;

    print(Array1);
    quicksort(Array1, left, right);
    print(Array1); 

    // printf("Array_1 :");
    // quicksort(Array1, left, right);
    // print(Array1);  

    // printf("Array_2 :");
    // quicksort(Array2, left, right);
    // print(Array2); 

    // printf("Array_3 :");
    // quicksort(Array3, left, right);
    // print(Array3); 

    // printf("Array_4 :");
    // quicksort(Array4, left, right);
    // print(Array4); 

    // printf("Array_5 :");
    // quicksort(Array5, left, right);
    // print(Array5); 

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
}

void print(int array[]){

    printf("\n");
    for(int k = 0; k < SIZE; k++){
        printf("%d", array[k]);
        printf(" ");
    }
    printf("\n");

}