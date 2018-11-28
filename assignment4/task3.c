#include <stdio.h>
#include <stdlib.h>

#define SIZE 8000
#define SIZE2 1400
#define MAX_BUFFER 256

int parce_vertices(FILE *vertices, char *buf, int max);
int parce_edges(FILE *edges, char *buf, int max);
int find_cost(int i, int j, int V1[SIZE], int V2[SIZE], int Weight[SIZE]);
void dijkstra(int graph[SIZE2][SIZE2], int start, int finish, int ID[SIZE], char *Name[SIZE], char *Latitude[SIZE], char *Longitude[SIZE]);

int main ( int argc, char *argv[] ) {

    int graph[SIZE2][SIZE2];

    int ID[SIZE];
    char *Name[SIZE];
    char *Latitude[SIZE];
    char *Longitude[SIZE];

    int V1[SIZE];
    int V2[SIZE];
    int Weight[SIZE];

	FILE *vertices;
    FILE *edges;

	char buffer[MAX_BUFFER];
    char buffer2[MAX_BUFFER];
    int i =0;

	if( argc < 3 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}
	
	vertices = fopen(argv[1], "r");
	if(!vertices) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
    //printf("opening %s\n", argv[1]); 

    while(!parcer(vertices, buffer, MAX_BUFFER));
	
    int eor;
    int index;
	while(!feof(vertices)) {

		eor = parcer(vertices, buffer, MAX_BUFFER );
        index = atoi(buffer);
        //printf("%s, ", buffer);
        ID[index] = index;
    
        eor = parcer(vertices, buffer, MAX_BUFFER );
        //printf("%s, ", buffer);
        Name[index] = buffer;

        eor = parcer(vertices, buffer, MAX_BUFFER );
        //printf("%s, ", buffer);
        Latitude[index] = buffer;

        eor = parcer(vertices, buffer, MAX_BUFFER );
        //printf("%s\n", buffer);
        Longitude[index] = buffer;

	}
    //printf("\nparced vetices\n");
    fclose(vertices);

    i =0;
    edges = fopen(argv[2], "r");
	if(!edges) { 
		printf("unable to open %s\n", argv[2]); 
		return EXIT_FAILURE; 
	}
    //printf("opening %s\n", argv[2]); 

    while(!parcer(edges, buffer2, MAX_BUFFER));
	
    int v1, v2, weight;
	while(!feof(edges)) {

		eor = parcer(edges, buffer2, MAX_BUFFER);
		if(eor = 1){
            i++;
        }
        v1 = atoi(buffer2);
        V1[i] = v1;
    
        eor = parcer(edges, buffer2, MAX_BUFFER);
		if(eor = 1){
            i++;
        }
        v2 = atoi(buffer2);
        V2[i] = v2;

        eor = parcer(edges, buffer2, MAX_BUFFER);
		if(eor = 1){
            i++;
        }
        weight = atoi(buffer2);
        Weight[i] = weight;
        //printf("%d\t", weight);

	}
    //printf("\nparced edges\n");
    fclose(edges);


    for(int i = 0; i < SIZE2; i++){
        for(int j = 0; j < SIZE2; j++){
            graph[i][j] = find_cost(i, j, V1, V2, Weight);
        }
    }

    // for(int i = 0; i < SIZE2; i++){
    //     for(int j = 0; j < SIZE2; j++){
    //         printf("%d\t", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("\ngraph ready\n");

    // int start, finish;

    // start = 0;
    // finish = 50;
    // dijkstra(graph, start, finish, ID, Name, Latitude, Longitude);

	return EXIT_SUCCESS;
}


// The parser
int parcer(FILE *file, char *buf, int max) {

	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(file);
        
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"'){ 
            quoted = !quoted; 
            buf[i] = fgetc(file);
        }

		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted){ 
            break;
        }

		// end record on newline or end of file
		if(feof(file) || buf[i]=='\n'){ 
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

int find_cost(int a, int b, int V1[], int V2[], int Weight[]){

    for(int i = 0; i < SIZE2; i++){
        if((V1[i] == a && V2[i] == b) || (V1[i] == b && V2[i] == a)){
            return Weight[i];
        }
    }
    return 9999;
}

void dijkstra(int graph[SIZE2][SIZE2], int start, int finish, int ID[SIZE], char *Name[SIZE], char *Latitude[SIZE], char *Longitude[SIZE]){
 
    int cost[SIZE2][SIZE2], dist[SIZE2], pred[SIZE2], perm[SIZE2], curr, min, distance, predeccesor;

    //initialise the cost matrix
    for(int i = 0; i < SIZE2; i++){
        for(int j = 0; j < SIZE2; j++){
            cost[i][j] = graph[i][j];
        }
    }

    //initialise the distance, predeccesor and permanent arrays
    for(int i = 0; i < SIZE2; i++){
        dist[i] = cost[start][i];
        pred[i] = start;
        perm[i] = 0;
    }
    
    //set the distance from A to A to zero! make A permanent
    dist[start] = 0;
    perm[start] = 1;
    int count = 1;
    curr = 0;

    //loop through until all vertices are permanent while printing them
    while(count < SIZE2){
        min = 9999;

        //loop checking for shortest distance for curr's neighbours
        for(int i = 1; i < SIZE2; i++){
            distance = dist[curr] + cost[curr][i];

            //if the new path is shorter, update dist array and predeccsor
            if(distance < dist[i] && perm[i] == 0){
                dist[i] = distance;
                pred[i] = curr;
            }
            //if the distance to i is less than the paths minimum, update mim and curr
            if(min > dist[i] && perm[i] == 0){
                min = dist[i];
                curr = i;
            }
        }
        //make curr permanent and print
        perm[curr] = 1;
        count++;
    }

    //printing the distance and path for each vertex
    printf("\n\nDistance of Stop ");
    printf("%d", start);
    printf(" to %d = %d\n\n", finish, dist[finish]);

    predeccesor = finish;

    printf("%d,\t", ID[predeccesor]);
    printf("%s,\t", Name[predeccesor]);
    printf("%s,\t", Latitude[predeccesor]);
    printf("%s,\n", Longitude[predeccesor]);

    //loop printing the predeccesors
    while(predeccesor != start){
        predeccesor = pred[predeccesor];
        printf("%d,\t", ID[predeccesor]);
        printf("%s,\t", Name[predeccesor]);
        printf("%s,\t", Latitude[predeccesor]);
        printf("%s,\n", Longitude[predeccesor]);
    }

}