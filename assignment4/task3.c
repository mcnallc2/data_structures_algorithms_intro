#include <stdio.h>
#include <stdlib.h>

#define SIZE 5000
#define MAX_BUFFER 256

int parce_vertices(FILE *vertices, char *buf, int max);

int main ( int argc, char *argv[] ) {

    char *ID[SIZE];
    char *Name[SIZE];
    char *Latitude[SIZE];
    char *Longitude[SIZE];

	FILE *vertices;
    FILE *edges;

	char buffer[MAX_BUFFER];
    int i =0;

	if( argc < 2 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}
	
	vertices = fopen(argv[1], "r");
	if(!vertices) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}

    while(!parce_vertices(vertices, buffer, MAX_BUFFER));
	
    int eor;
	while(!feof(vertices)) {

		eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        ID[i] = buffer;
    
        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Name[i] = buffer;

        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Latitude[i] = buffer;

        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Longitude[i] = buffer;

	}

    edges = fopen(argv[1], "r");
	if(!vertices) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}

    while(!parce_vertices(vertices, buffer, MAX_BUFFER));
	
    int eor;
	while(!feof(vertices)) {

		eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        ID[i] = buffer;
    
        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Name[i] = buffer;

        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Latitude[i] = buffer;

        eor = next_field(vertices, buffer, MAX_BUFFER );
		if(eor = 1){
            i++;
        }
        Longitude[i] = buffer;

	}
	
	fclose(vertices);
    fclose(edges);
	return EXIT_SUCCESS;
}


// The vertices parser
int parce_vertices(FILE *vertices, char *buf, int max) {

	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(vertices);
        
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"'){ 
            quoted = !quoted; 
            buf[i] = fgetc(vertices);
        }

		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted){ 
            break;
        }

		// end record on newline or end of file
		if(feof(vertices) || buf[i]=='\n'){ 
            end = 1; 
            break;
        } 

		// truncate fields that would overflow the buffer
		if(i < max-1){ 
            ++i;
        } 
	}
	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}