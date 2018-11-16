#include "bstdb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

#define ARRAY_SIZE 100000

typedef struct Tree_Node {

    int doc_id;           // unique identifier for the document
    char *name;             // file name of the document    
    int word_count;       // number of words in the document      
    struct Tree_Node *left; // pointer to the next node in the list
	struct Tree_Node *right; // pointer to the next node in the list

}Tree_Node;

Tree_Node* root;
int i;
int names_array[ARRAY_SIZE];

Tree_Node* tree_insert(Tree_Node** root_ptr, char *name, int word_count);
Tree_Node* Insert(Tree_Node *root, char *name, int word_count, int doc_id);
Tree_Node* tree_search(Tree_Node* search, int doc_id);
void delete_tree(Tree_Node* delete);
void unique_array();

int
bstdb_init ( void ) {

	root = NULL;
	i = 0;
    unique_array();
    printf("\ninit\n");
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	return 1;
}

int
bstdb_add ( char *name, int word_count ) {

	// if(!tree_insert(&root, name, word_count)){
    //     return -1;
    // }
    // else{
    //     printf("\nAdding...\n");
    //     return (tree_insert(&root, name, word_count))->doc_id;
    // }
    int doc_id = names_array[i];

    if(Insert(root, name, word_count, doc_id) == NULL){
        return -1;
    }
    else{
        printf("\nAdding...\n");
        int ret = Insert(root, name, word_count, doc_id)->doc_id;
        return ret;
    }
    i++;

    // int left_right;
    //
    // Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    // strcpy(new_node->name, name);
	// new_node->word_count = word_count;
	// new_node->doc_id = next_id;

    // Tree_Node* prev = NULL;
    // Tree_Node* curr = NULL;
    // Tree_Node* next = NULL;

	// next_id = rand();

    // if(root == NULL){
    //     new_node->left = NULL;
    //     new_node->right = NULL;
    //     root = new_node;
    // }
    // else{
    //     curr = root;
    //     while(curr != NULL){
    //         if(next_id <= curr->doc_id){
    //             next = curr->left;
    //             left_right = 1;
    //         }
    //         else{
    //             next = curr->right;
    //             left_right = 2;
    //         }
    //         prev = curr;
    //         curr = next;
    //     }

    //     if(left_right == 1){
    //         prev->left = new_node;
    //     }
    //     else{
    //         prev->right = new_node;
    //     }
    // }
	// return new_node->doc_id;


	// This function should create a new node in the binary search tree, 
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	//return -1;
}

int
bstdb_get_word_count ( int doc_id ) {

    Tree_Node *p = tree_search(root, doc_id);
    if(p == NULL){
        return -1;
    }
    else{
        return p->word_count;
    }

    // Tree_Node* curr;
    // Tree_Node* next;

    // if(root == NULL){
    //     return -1;
    // }
    // else{
    //     curr = root;
    //     while(curr != NULL){
	// 		if(doc_id == curr->doc_id){
    //             return curr->word_count;
    //         }
    //         if(doc_id < curr->doc_id){
    //             next = curr->left;
    //         }
    //         else{
    //             next = curr->right;
    //         }
    //         curr = next;
    //     }
    //     return -1;
    // }

	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
}

char*
bstdb_get_name ( int doc_id ) {

	Tree_Node *p = tree_search(root, doc_id);
    if(p == NULL){
        return 0;
    }
    else{
        return p->name;
    }

    // Tree_Node* curr;
    // Tree_Node* next;

    // if(root == NULL){
    //     return 0;
    // }
    // else{
    //     curr = root;
    //     while(curr != NULL){
	// 		if(doc_id == curr->doc_id){
    //             return curr->name;
    //         }
    //         if(doc_id < curr->doc_id){
    //             next = curr->left;
    //         }
    //         else{
    //             next = curr->right;
    //         }
    //         curr = next;
    //     }
    //     return 0;
    // }

	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
}

void
bstdb_stat ( void ) {

	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}

void
bstdb_quit ( void ) {

	delete_tree(root);
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
}


Tree_Node* tree_insert(Tree_Node** root_ptr, char *name, int word_count){

    if((*root_ptr) == NULL){
    
        Tree_Node* new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root_ptr) = new_node;
        strcpy((*root_ptr)->name, name);
		(*root_ptr)->word_count = word_count;
		(*root_ptr)->doc_id = names_array[i];
        i++;
        (*root_ptr)->left = NULL;
        (*root_ptr)->right = NULL;
		return (*root_ptr);

    }
    else if(names_array[i] <= (*root_ptr)->doc_id){
        return tree_insert(&(*root_ptr)->left, name, word_count);
    }
    else{
        return tree_insert(&(*root_ptr)->right, name, word_count);
    }
}



Tree_Node* tree_search(Tree_Node* search, int doc_id){

    if(search == NULL){
        return NULL;
    }
    else if(search->doc_id == doc_id){
        return search;
    }
    else if(doc_id < search->doc_id){
        return tree_search(search->left, doc_id);
    }
    else{
        return tree_search(search->right, doc_id);
    }
}

void
delete_tree(Tree_Node* delete){
	if(delete != NULL){
        delete_tree(delete->left);
        delete_tree(delete->right);
        free(delete);
    }
}

void unique_array(){

    int temp, f, j;
    //fill a uniform array
    for(f = 0; f < ARRAY_SIZE; f++){
        names_array[f] = f;
    }

    //shuffle the array
    for(f = ARRAY_SIZE-1; f > 0; f--){

        j = rand() % (f - 1);

        //swap two indexs
        temp = names_array[j];
        names_array[j] = names_array[f];
        names_array[f] = temp;
    }
}

Tree_Node* Insert(Tree_Node *root, char *name, int word_count, int doc_id)
{

    if(!root)                              //Explicitly insert into head if it is NULL
    {
        root = malloc(sizeof *root);
        strcpy(root->name, name);
		root->word_count = word_count;
		root->doc_id = doc_id;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    for(Tree_Node *temp = root, *temp2 = root; ;(temp = (names_array[i] > temp->doc_id)?(temp->right):(temp->left)))
    {
        if(temp == NULL)
        {
            temp = malloc(sizeof *temp);
            strcpy(temp->name, name);
		    temp->word_count = word_count;
		    temp->doc_id = doc_id;
            temp->left = NULL;
            temp->right = NULL;

            if(names_array[i] > temp2->doc_id)  //update previous nodes left or right pointer accordingly 
                temp2->right = temp;
            else
                temp2->left = temp;

            break;
        }

        temp2 = temp;      //Use a another pointer to store previous value of node
    }

    return root;
}