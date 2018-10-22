#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

void bubblesort(int array[]);
void swap(int array[], int j);
void print(int array[]);
int check(int array[], int random, int i);
char check_sorted(int array[]);

int swap_count = 0;
int comparisons = 0;

int main (){

    int Array1[SIZE], random;
    int Array2[SIZE];
    int Array3[SIZE];
    int Array4[SIZE], num;
    int Array5[SIZE];

    for(int i =0; i <SIZE; i++){
        random = rand();
        while(check(Array1, random, i) == 0){
            random = rand();
        }
        Array1[i] = rand();
    }

    for(int i =0; i <SIZE; i++){
        Array2[i] = rand();
    }

    for(int i =0; i <SIZE; i++){
        Array3[i] = (i + 1);
    }

    num = SIZE;
    for(int i =0; i <SIZE; i++){
        Array4[i] = num;
        num--;
    }

    for(int i =0; i <SIZE; i++){
        Array5[i] = 3;
    }

    int left = 0;
    int right = (SIZE-1);

    swap_count = 0;
    comparisons = 0;
    bubblesort(Array1);
    printf("\nTEST  : Unique random values\n");
    printf("SORTED: %c\n", check_sorted(Array1));
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    bubblesort(Array2);
    printf("\nTEST  : Random values\n");
    printf("SORTED: %c\n", check_sorted(Array2));
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    bubblesort(Array3);
    printf("\nTEST  : Ascending sorted list\n");
    printf("SORTED: %c\n", check_sorted(Array3));
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    bubblesort(Array4);
    printf("\nTEST  : Descending sorted list\n");
    printf("SORTED: %c\n", check_sorted(Array4));
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

    swap_count = 0;
    comparisons = 0;
    bubblesort(Array5);
    printf("\nTEST  : Uniform list\n");
    printf("SORTED: %c\n", check_sorted(Array5));
    printf("SWAPS : %d\n", swap_count);
    printf("COMPS : %d\n", comparisons);

}

void bubblesort(int array[]){

    for(int i = 0; i < SIZE; i ++){
        for(int j = 0; j < (SIZE - 1); j++){
            comparisons++;
            if(array[j] > array[j+1]){
                swap_count++;
                swap(array, j);
            }
        }
    }
}

void swap(int array[], int j){

    int temp;

    temp = array[j+1];
    array[j+1] = array[j];
    array[j] = temp;

}

void print(int array[]){

    printf("\n");
    for(int k = 0; k < SIZE; k++){
        printf("%d", array[k]);
        printf(" ");
    }
    printf("\n");

}

int check(int array[], int random, int end){
    for(int i =0; i < end; i++){
        if(array[i] == random){
            return 0;
        }
    }
    return 1;
}

char check_sorted(int array[]){

    for(int i = 0; i < (SIZE-1); i++){
        if(array[i+1] < array[i]){
            return 'N';
        }
    }
    return 'Y';

}