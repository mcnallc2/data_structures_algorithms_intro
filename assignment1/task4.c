#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_NAME_SIZE 256
#define TABLE_SIZE 71

typedef struct Element{

	int P_ID;
	int D_ID;
    char S_Name[MAX_NAME_SIZE];
	char F_Name[MAX_NAME_SIZE];
	int Age;
	char P_Type[MAX_NAME_SIZE];
	char Gender[MAX_NAME_SIZE];
	char Nationality[MAX_NAME_SIZE];
	char Religion[MAX_NAME_SIZE];
	char Occupation[MAX_NAME_SIZE];
	struct Element * next;

}Element;

void add_surname(char *name, Element *hash_table);
void add_node(char * name, Element *  next);
void next_field( FILE *f, char *buf, int max );
int hash1(char *s);
void print_hashtable(Element *hash_table);

int main ( int argc, char *argv[] ) {

	FILE *f;		
	char buffer[MAX_BUFFER];

    Element hash_table[TABLE_SIZE];

	for(int i = 0; i < TABLE_SIZE; i++){

		hash_table[i].P_ID = 0;
		hash_table[i].D_ID = 0;
		strcpy(hash_table[i].S_Name, "");
		strcpy(hash_table[i].F_Name, "");
		hash_table[i].Age = 0;
		strcpy(hash_table[i].P_Type, "");
		strcpy(hash_table[i].Gender, "");
		strcpy(hash_table[i].Nationality, "");
		strcpy(hash_table[i].Religion, "");
		strcpy(hash_table[i].Occupation, "");
		hash_table[i].next = NULL;
	
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
		add_surname(buffer, hash_table);

	}

	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}

void add_surname(char *name, Element *hash_table){

	//find the key of the name
    int key = hash1(name);
	Element * curr = NULL;

	//if this key is empty add surname
	if(strcmp(hash_table[key].S_Name, "") == 0){
		strcpy(hash_table[key].S_Name, name);	
	}

	//if it has the same name chain out
	else if(strcmp(name, hash_table[key].S_Name) == 0){
		curr = hash_table[key].next;
		add_node(name,curr);
	}
}

void add_node(char * name, Element *  curr){

    Element* new = (Element*)malloc(sizeof(Element));
	*new->S_Name = name;

	while(curr->next != NULL){
		curr = curr->next;
	}
    new->next = NULL;
    new = curr;
}

void print_hashtable(Element *hash_table){

	Element * curr = NULL;

	for(int i = 0; i < TABLE_SIZE; i++){

		if(strcmp(hash_table[i].S_Name, "") != 0){
			
			printf("%s", hash_table[i].S_Name);
			printf("\n");

			curr = hash_table[i].next;
			while(curr != NULL){
				printf("%s", hash_table[i].S_Name);
				printf("\n");
				curr = curr->next;
			}
			printf("\n\n");

		}
	}
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

int hash1(char *s){

    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    hash = hash % TABLE_SIZE;
    return hash;
}