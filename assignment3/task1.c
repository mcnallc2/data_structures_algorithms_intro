#include <stdio.h> 
#include <stdlib.h> 

#define array_size 29
  
typedef struct Tree_Node  
{ 
    char data; 
    struct Tree_Node *left; 
    struct Tree_Node *right; 

}Tree_Node; 

void tree_insert(Tree_Node** root, char data); 
Tree_Node* tree_search(Tree_Node* root, char data);

int main(){

    Tree_Node* root = NULL;

    char array[] = {'F', 'L', 'O', 'C', 'C', 'I', 'N', 'A', 'U', 'C', 'I', 'N', 'I', 'H', 'I', 'L', 'I', 'P', 'I', 'L', 'I', 'F', 'I', 'C', 'A', 'T', 'I', 'O', 'N'};

    printf("ADDING: ");
    for(int i = 0; i < array_size; i++){

        printf("%c ", array[i]);
        tree_insert (&root, array[i]);

    }

    char search;

    printf("Enter data to search for....");
    scanf("%c\n\n", &search);

    if(tree_search(root, search) == NULL){
        printf("Tree is empty");
    }
    else{
        printf("Data found: ");
        printf("%c\n", tree_search(root, search)->data);
    }

    return 0; 
} 

void tree_insert(Tree_Node ** root, char data){

    int left_right;

    Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->data = data;

    Tree_Node* prev = NULL;
    Tree_Node* curr = NULL;
    Tree_Node* next = NULL;

    if(*root == NULL){
        new_node->left = NULL;
        new_node->right = NULL;
        *root = new_node;
    }
    else{
        curr = *root;
        while(curr != NULL){
            if(data <= curr->data){
                next = curr->left;
                left_right = 1;
            }
            else{
                next = curr->right;
                left_right = 2;
            }
            prev = curr;
            curr = next;
        }

        if(left_right == 1){
            prev->left = new_node;
        }
        else{
            prev->right = new_node;
        }
    }
}

Tree_Node* tree_search(Tree_Node* root, char data){

    Tree_Node* prev = NULL;
    Tree_Node* curr = NULL;
    Tree_Node* next = NULL;

    if(root == NULL){
        return NULL;
    }
    else{
        curr = root;
        while(curr != NULL){
            if(data < curr->data){
                next = curr->left;
            }
            else if(data > curr->data){
                next = curr->right;
            }
            else if(data = curr->data){
                break;
            }
            prev = curr;
            curr = next;
        }
        return curr;
    }
}