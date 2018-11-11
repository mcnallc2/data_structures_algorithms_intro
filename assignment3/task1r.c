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
void tree_print_sorted(Tree_Node* root);
void tree_delete(Tree_Node* root);

int main(){

    Tree_Node* root = NULL;
    Tree_Node* search_node = NULL;

    char array[] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I', 'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T', 'I', 'O', 'N'};

    printf("ADDING: ");
    for(int i = 0; i < array_size; i++){

        printf("%c ", array[i]);
        tree_insert (&root, array[i]);
 
    }
    printf("\nSORTED: ");
    tree_print_sorted(root);
    printf("\n");
    //printf("\n---%c---\n", root->right->left->left->left->left->data);


    char search;

    for(int s = 0; s < 2; s++){

        search = 'A' + (rand() % 26);
        search_node = tree_search(root, search);

        printf("\n%c ", search);
        if(search_node == NULL){
            printf("is in tree.");
        }
        else{
            printf("is not in tree.");
        }
    }

    printf("\n\nDELETING: ");
    tree_delete(root);
    
    return 0; 
} 

void tree_insert(Tree_Node** root_ptr, char data){

    if((*root_ptr) == NULL){
    
        Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root_ptr) = new_node;
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
    else if(data < root->data){
        //printf("\n---Going Left---\n");
        return tree_search(root->left, data);
    }
    else{
        //printf("\n---Going Right---\n");
        return tree_search(root->right, data);
    }
}

//traversing through the tree recursively (in-order)
void tree_print_sorted(Tree_Node* root){

    if(root != NULL){
        tree_print_sorted(root->left);
        printf("%c ", root->data);
        tree_print_sorted(root->right);
    }
}

void tree_delete(Tree_Node* root){

    if(root != NULL){
        tree_delete(root->left);
        tree_delete(root->right);
        printf("%c ", root->data);
        free(root);
    }

}