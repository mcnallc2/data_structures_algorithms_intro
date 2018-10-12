#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_NAME_SIZE 256
#define TABLE_SIZE 71

typedef struct Element{

    char Name[MAX_NAME_SIZE];
    int Frequency;

}Element;

int hash2(char *s);
int hash3(char *s);
void next_field( FILE *f, char *buf, int max );
int add_to_hashtable(char *name, Element *hash_table);
void print_hashtable(Element *hash_table);
int count_hashtable(Element *hash_table);

int main ( int argc, char *argv[] ) {
	FILE *f;		
	char buffer[MAX_BUFFER];
	char find[MAX_NAME_SIZE];
	int collisions = 0, terms;
	double load;

    Element hash_table[TABLE_SIZE];

	for(int i = 0; i < TABLE_SIZE; i++){
		strcpy(hash_table[i].Name, "");
		hash_table[i].Frequency = 0;
	}

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
	// Now read and print records until the end of the file
	while(!feof(f)) {
		next_field(f, buffer, MAX_BUFFER);
        if(add_to_hashtable(buffer, hash_table) == 1){
			collisions++;
		}
	}

	terms = count_hashtable(hash_table);
	load = (double)terms / (double)TABLE_SIZE;

	printf("names.csv loaded!!!\n\n");
	printf("Capacity = ");
	printf("%d", TABLE_SIZE);
	printf("\n");
	printf("Number of terms = ");
	printf("%d", terms);
	printf("\n");
	printf("Collisions = ");
	printf("%d", collisions);
	printf("\n");
	printf("Load = ");
	printf("%f", load);
	printf("\n");
	printf("\n\n");


	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}

int add_to_hashtable(char *name, Element *hash_table){

	//find the key of the name
    int key;
	int sentinel = 0;
	int switc = 0;
	int collision = 0;
    int i = 0;
 

	//interate until the correct key is found
	while(sentinel == 0){

        //if the key is not empty but its only an anogram etc go to next key
		key = (hash2(name) + (i * hash3(name))) % TABLE_SIZE;

		//if this key is empty
		if(hash_table[key].Frequency == 0){
			strcpy(hash_table[key].Name, name);
			hash_table[key].Frequency = 1;
			sentinel = 1;
			switc = 0;
            i = 0;
		}

		//if it is the same exact same string increment frequency
		else if(strcmp(name, hash_table[key].Name) == 0){
			hash_table[key].Frequency = hash_table[key].Frequency + 1;
			sentinel = 1;
			switc = 0;
            i = 0;
		}
		else if(switc == 0){
			//printf("Collision\n");
			collision = 1;
			switc = 1;
		}
        i++;

		
	}
	return collision;
}

void print_hashtable(Element *hash_table){

	for(int i = 0; i < TABLE_SIZE; i++){

		if(hash_table[i].Frequency != 0){
			
			printf("%d", i);
			printf("\t");
			printf("%s", hash_table[i].Name);
			printf("\t");
			printf("%d", hash_table[i].Frequency);
			printf("\n");
		}
	}
}

int count_hashtable(Element *hash_table){

	int count = 0;
	for(int i = 0; i < TABLE_SIZE; i++){
		if(hash_table[i].Frequency != 0){
			count++;
		}
	}
	return count;
}

// The CSV parser
void next_field( FILE *f, char *buf, int max ) {

	int i = 0;
	
	for(;;) {

		// fetch the next character from file		
		buf[i] = fgetc(f);

		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n'){
			break;
		} 

		// truncate fields that would overflow the buffer
		if( i<max-1 ){
			++i;
		} 
	}

	buf[i] = 0; // null terminate the string
}

int hash2(char *s){

    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    hash = (hash * 11) % TABLE_SIZE;
    return hash;
}

int hash3(char *s){

    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    hash = 7 - (hash % 7);
    return hash;
}