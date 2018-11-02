#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256
#define ARRAY_SIZE 1000

typedef struct Game{

    char title[MAX_BUFFER];
    char platform[MAX_BUFFER];
    int score;
    int year;

}Game;

int next_field( FILE *f, char *buf, int max ) {

	int i=0, end=0, quoted=0;
	
	for(;;) {

		// fetch the next character from file		
		buf[i] = fgetc(f);

		// end of field on comma if we're not inside quotes
		if(buf[i]==','){
			 break;
		}

		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n'){
			 end=1; break;
		} 

		// truncate fields that would overflow the buffer
		if( i<max-1 ){
			++i;
		} 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

int main ( int argc, char *argv[] ) {
	FILE *f;		
	char buffer[MAX_BUFFER];

    Game Game_review[ARRAY_SIZE];

	// Users must pass the name of the input file through the command line. Make sure
	// that we got an input file. If not, print a message telling the user how to use
	// the program and quit
	if( argc < 2 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}

	// Try to open the input file. If there is a problem, report failure and quit
	f = fopen(argv[1], "r");
	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}

	//while( !next_field(f, buffer, MAX_BUFFER) ); // discard the header

	// Now read and print records until the end of the file
    int i = 0, score, year;
	while(i < ARRAY_SIZE) {
		
		//int eor = next_field(f, buffer, MAX_BUFFER);
		//printf("%s%c\n", buffer, ((eor)? '\n':' ' ));
        if(!next_field(f, buffer, MAX_BUFFER)){
            strcpy(Game_review[i].title, buffer);
        }
        if(!next_field( f, buffer, MAX_BUFFER )){
            strcpy(Game_review[i].platform, buffer);
        }
        if(!next_field( f, buffer, MAX_BUFFER )){
            score = atoi(buffer);
            Game_review[i].score = score;
        }
        if(!next_field( f, buffer, MAX_BUFFER )){
            year = atoi(buffer);
            Game_review[i].year = year;
        }
        if(next_field( f, buffer, MAX_BUFFER )){
            i++;
        }

	}

	int left = 0;
    int right = (ARRAY_SIZE-1);
	quicksort(Game_review, left, right);


	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}

void quicksort(Game Game_review[], int left, int right){

    if(left < right){

        int new_pivot = partition(Game_review, left, right);


        quicksort(Game_review, left, (new_pivot -1));
        quicksort(Game_review, (new_pivot +1), right);
    }
}

int partition(Game Game_review[], int left, int right){


    int pivot = Game_review[right].score;
    int i = left;

    for(int j = left; j <= (right - 1); j++){
        if(Game_review[j].score < pivot){
            swap(Game_review, i, j);
            i++;
        }
    }
    swap(Game_review, i, right);
    return i;

}

void swap(Game Game_review[], int i, int j){

    Game temp;

    if(i != j){
        temp = Game_review[j];
        Game_review[j] = Game_review[i];
        Game_review[i] = temp;
    }
}

void print(Game Game_review[]){

    printf("\n");
    for(int k = ARRAY_SIZE; k >= (ARRAY_SIZE-10); k--){
        printf("%s", Game_review[k].title);
        printf("\n");
    }
    printf("\n");

}