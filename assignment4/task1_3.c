#include <stdio.h> 
#include <stdlib.h>

#define N_COUNT 6

typedef struct Graph{

    struct List* array; 

}Graph; 

typedef struct List{ 

    struct Node* Head; 
    
}List; 

typedef struct Node { 

    char Name;
    int Flag; 
    struct Node* Next; 

}Node; 

Node* Add_Node(char end);
Graph* createGraph();
void Add_Edge(Graph* graph, int start, char end);


int main(){ 

    Graph* graph = createGraph(); 
    Add_Edge(graph, 0, 1);
    Add_Edge(graph, 0, 3);
    Add_Edge(graph, 0, 4);
    Add_Edge(graph, 1, 2);
    Add_Edge(graph, 1, 3);
    Add_Edge(graph, 2, 1);
    Add_Edge(graph, 2, 3);
    Add_Edge(graph, 3, 5);
    Add_Edge(graph, 4, 3);
    Add_Edge(graph, 5, 2);

    Set_Flags(nodes);

    printf("DFS: ");
    DFS_Graph(nodes[0]);
    printf("\n\n");

    // Set_Flags(nodes);

    // printf("BFS: ");
    // BFS_Graph(nodes[0]);
    // printf("\n\n");

    //Print_Graph(nodes);
    return 0; 
} 

Node* Add_Node(char name){ 

    Node* New_Node = (Node*) malloc(sizeof(Node)); 
    New_Node->Name = name; 
    New_Node->Next = NULL; 
    return New_Node; 
}

Graph* createGraph(){ 

    Graph* graph = (Graph*)malloc(sizeof(Graph)); 
   
    graph->array = (List*)malloc(N_COUNT * (sizeof(List)));

    for(int i = 0; i < N_COUNT; i++){
        
        graph->array[i].Head = NULL; 
    }
  
    return graph; 
} 

void Add_Edge(Graph* graph, int start, char end){ 

    Node* New_Node = Add_Node(end); 
    New_Node->Next = graph->array[start].Head; 
    graph->array[start].Head = New_Node; 

} 

void DFS_Graph(Graph* graph) { 

    if(graph->array[i].Head->Flag != 1){

        printf("%c ", graph->array[i].Head->name);
        graph->array[i].Head->Flag->flag = 1;

        int i = 0;
        Node* curr = graph->array[i].Head->Next;

        while(curr != NULL){
            DFS_Graph(curr);
            i++;
            curr = graph->array[i].Head->next[i];
        }
    }
}

// node* Add_Node(char name){

//     node* New_Node = (node*)malloc(sizeof(node)); 
//     New_Node->name = name; 

//     for(int i = 0; i < P_COUNT; i++){
//         New_Node->next[i] = NULL; 
//     }
//     return New_Node;
// }

// void Add_Edge(node* start, node* end){
    
//     int i = 0;
//     node* curr = start->next[i];

//     while(curr != NULL){
//         i++;
//         curr = start->next[i];
//     }
//     start->next[i] = end;
//     //printf("\nAdding Edge\n");

// }

// void Set_Flags(node* nodes[]){

//     for(int i = 0; i < N_COUNT; i++){
//         nodes[i]->flag = 0;
//     }
// }

// void DFS_Graph(node* root) { 

//     if(root->flag != 1){

//         printf("%c ", root->name);
//         root->flag = 1;
//         int i = 0;
//         node* curr = root->next[i];

//         while(curr != NULL){
//             DFS_Graph(curr);
//             i++;
//             curr = root->next[i];
//         }
//     }
// }

// void BFS_Graph(node* root) { 
// Node* Add_Node(char name); 
// void Add_Edge(node* start, node* end); 
// void Set_Flags(node* nodes[]);
// void DFS_Graph(node* root);
// void BFS_Graph(node* root);
//     int i = 0;
//     node* curr = root->next[i];

//     while(curr != NULL){
//         if(curr->flag != 1){
//             printf("%c ", curr->name);
//             curr->flag = 1;
//         }
//         i++;
//         curr = root->next[i];
//     }

//     // i = 0;
//     // curr = root->next[i];
//     // while(curr != NULL){
//     //     BFS_Graph(curr);
//     //     curr->flag = 1;
//     //     i++;
//     //     curr = root->next[i];
//     // }
// }


