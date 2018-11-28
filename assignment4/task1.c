#include <stdio.h> 
#include <stdlib.h>

#define N_COUNT 6
#define P_COUNT 4

typedef struct node { 

    char name;
    int flag; 
    struct node* next[P_COUNT]; 

}node; 

// typedef struct queue { 

//     char name;
//     struct queue* next; 

// }queue; 

node* Add_Node(char name); 
void Add_Edge(node* start, node* end); 
void Set_Flags(node* nodes[]);
void DFS_Graph(node* root);
void BFS_Graph(node* root);
void Print_Connections(node * root);

int main(){ 

    //printf("\nDEBUG\n");
    node* nodes[N_COUNT];
    node* root = nodes[0];
    char name = 'A';
    //printf("\nDEBUG\n");

    //creating the nodes for the given graph
    for(int i = 0; i < N_COUNT; i++){
        nodes[i] = Add_Node(name);
        //printf("\nAdding %c\n", name);
        name++;
    }

    //adding the edges for the given graph
    Add_Edge(nodes[0], nodes[1]);
    Add_Edge(nodes[0], nodes[3]);
    Add_Edge(nodes[0], nodes[4]);
    Add_Edge(nodes[1], nodes[2]);
    Add_Edge(nodes[1], nodes[3]);
    Add_Edge(nodes[2], nodes[1]);
    Add_Edge(nodes[2], nodes[3]);
    Add_Edge(nodes[3], nodes[5]);
    Add_Edge(nodes[4], nodes[3]);
    Add_Edge(nodes[5], nodes[2]);

    Set_Flags(nodes);

    printf("DFS: ");
    DFS_Graph(nodes[0]);
    printf("\n\n");

    Set_Flags(nodes);

    printf("BFS: ");
    BFS_Graph(nodes[0]);
    printf("\n\n");

    //Print_Graph(nodes);
    return 0; 
} 

//function creates a new vertex and sets its attributes
node* Add_Node(char name){

    node* New_Node = (node*)malloc(sizeof(node)); 
    New_Node->name = name; 

    for(int i = 0; i < P_COUNT; i++){
        New_Node->next[i] = NULL; 
    }
    return New_Node;
}

//function to add edges between vertices using the next pointers
void Add_Edge(node* start, node* end){
    
    int i = 0;
    node* curr = start->next[i];

    while(curr != NULL){
        i++;
        curr = start->next[i];
    }
    start->next[i] = end;
    //printf("\nAdding Edge\n");

}

//resets all the visited flags to unvisited
void Set_Flags(node* nodes[]){

    for(int i = 0; i < N_COUNT; i++){
        nodes[i]->flag = 0;
    }
}

//performs Depth First Search on the graph using recursion
void DFS_Graph(node* root) { 

    //if the vertex is not visited
    if(root->flag != 1){

        //print the name and mark as visited
        printf("%c ", root->name);
        root->flag = 1;
        int i = 0;
        node* curr = root->next[i];

        //recursive call this function on all the neighbours
        while(curr != NULL){
            DFS_Graph(curr);
            i++;
            curr = root->next[i];
        }
    }
}

//performs Breath First Search on the graph using recursion
void BFS_Graph(node* root){ 

    //if the flag is not print the vertex and change the flag
    if(root->flag != 1){
        printf("%c ", root->name);
        root->flag = 1;
    }
    //print all neighbours that havent been visited
    Print_Connections(root);

    int i = 0;
    node* curr = root->next[i];

    //print all the neighrbours for ech neighbour that havent been visited
    while(curr != NULL){

        Print_Connections(curr);  

        i++;
        curr = root->next[i];
    }
}

//prints all the neighbours that havent been visited for a node
void Print_Connections(node * root){

    int i = 0;
    node* curr = root->next[i];

    while(curr != NULL){
        if(curr->flag != 1){
            printf("%c ", curr->name);
            curr->flag = 1;
        }
        i++;
        curr = root->next[i];
    }

}


// void Push(node* add_node){ 

//     queue* New_Node = (queue*)malloc(sizeof(queue)); 

//     New_Node->name = add_node->name;
//     head = New_Node;
//     New_Node->next = NULL;
    
// }

// void Pop(node* remove_node){ 

//     queue* curr = head;
//     while(curr != NULL){
//         if(curr = head){
//             head = curr->next;
//             free(curr);
//         }
//     }

// }