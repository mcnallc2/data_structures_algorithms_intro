#include <stdio.h> 
#include <stdlib.h> 

#define array_size 29
  
typedef struct Tree_Node  
{ 
    char data; 
    struct Tree_Node *left; 
    struct Tree_Node *right; 

}Tree_Node; 

void tree_insert(Tree_Node** root_ptr, char data); 
Tree_Node* tree_search(Tree_Node* root, char data);

int main(){

    Tree_Node* root = NULL;
    Tree_Node* search_node = NULL;

    char array[] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I', 'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T', 'I', 'O', 'N'};

    printf("ADDING: ");
    for(int i = 0; i < array_size; i++){

        printf("%c ", array[i]);
        tree_insert (&root, array[i]);
 
    }
    //printf("\n---%c---\n", root->right->data);


    char search;

    printf("Enter data to search for....");
    scanf("%c\n\n", &search);

    search_node = tree_search(root, search);

    if(search_node == NULL){
        printf("Data not found");
    }
    else{
        printf("Data found: ");
        printf("%c\n", search_node->data);
    }

    return 0; 
} 

void tree_insert(Tree_Node** root_ptr, char data){

    if(*root_ptr == NULL){
    
        Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
        *root_ptr = new_node;
        (*root_ptr)->data = data;
        (*root_ptr)->left = NULL;
        (*root_ptr)->right = NULL;

    }
    else if(data <= (*root_ptr)->data){
        tree_insert(&((*root_ptr)->left), data);
    }
    else{
        tree_insert(&((*root_ptr)->right), data);
    }
}

Tree_Node* tree_search(Tree_Node* root, char data){

    if(root == NULL){
        return NULL;
    }
    else if(root->data == data){
        return root;
    }
    else if(root->data < data){
        tree_search(root->left, data);
    }
    else{
        tree_search(root->right, data);
    }
}