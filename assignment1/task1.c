#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle

int hash1(char *s);

// The CSV parser
int next_field( FILE *f, char *buf, int max ) {

	int i=0, end=0, quoted=0;
	
	for(;;) {

		// fetch the next character from file		
		buf[i] = fgetc(f);

		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"'){
			quoted=!quoted; buf[i] = fgetc(f);
		}

		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted){
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
	int key;

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

	while( !next_field(f, buffer, MAX_BUFFER) ); // discard the header

	// Now read and print records until the end of the file
	while(!feof(f)) {
		int eor = next_field( f, buffer, MAX_BUFFER );
		//printf("%s%c\n", buffer, ((eor)? '\n':' '));  // double newline if eor is not 0

		key = hash1(buffer);
		printf("%d", key);
		printf("\n");
	}

	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}

int hash1(char *s){
    int hash = 0;
    while(*s){
        hash = hash + *s;
        s++;
    }
    return hash;
}