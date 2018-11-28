#include <stdio.h>
#include <stdlib.h>
#define SIZE 7

void dijkstra(int graph[SIZE][SIZE], int startnode);
void print_vertex(int vertex);

int main(){ 

   int graph[SIZE][SIZE] = {{0,1,3,0,0,10,0}, 
                            {1,0,1,7,5,0,2}, 
                            {3,1,0,9,3,0,0}, 
                            {0,7,9,0,2,1,12}, 
                            {0,5,3,2,0,2,0}, 
                            {0,0,0,1,2,0,0}, 
                            {0,2,0,12,0,0,0}}; 
   
    dijkstra(graph, 0); 
   
    return 0; 
}

void dijkstra(int graph[SIZE][SIZE], int start){
 
    int cost[SIZE][SIZE], dist[SIZE], pred[SIZE], perm[SIZE], curr, min, distance, predeccesor;

    //initialise the cost matrix, adding a large value when there is no path
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(graph[i][j] == 0){
                cost[i][j] = 9999;
            }
            else{
                cost[i][j] = graph[i][j];
            }
        }
    }

    //initialise the distance, predeccesor and permanent arrays
    for(int i = 0; i < SIZE; i++){
        dist[i] = cost[start][i];
        pred[i] = start;
        perm[i] = 0;
    }
    
    //set the distance from A to A to zero! make A permanent
    dist[start] = 0;
    perm[start] = 1;
    int count = 1;
    curr = 0;


    printf("\nOrder of Vertices being made permanent: ");
    print_vertex(start);

    //loop through until all vertices are permanent while printing them
    while(count < SIZE){
        min = 9999;

        //loop checking for shortest distance for curr's neighbours
        for(int i = 1; i < SIZE; i++){
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
        printf(" -> ");
        print_vertex(curr);
        count++;
    }
    printf("\n");

    //printing the distance and path for each vertex
    for(int i = 1; i < SIZE; i++){

        printf("\n\nDistance of vertex ");
        print_vertex(i);
        printf(" from A = %d\n", dist[i]);
        printf("Path = ");
            
        predeccesor = i;
        print_vertex(predeccesor);

        //loop printing the predeccesors
        while(predeccesor != start){
            predeccesor = pred[predeccesor];
            printf(" - ");
            print_vertex(predeccesor);
        }
    }
    printf("\n\n");
}

//function to print the corresponding char for each index
void print_vertex(int vertex){

    char node = (vertex + 'A');
    printf("(%c)", node);
}