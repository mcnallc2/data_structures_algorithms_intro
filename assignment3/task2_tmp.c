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

typedef struct Tree_Node {

    int   doc_id;           // unique identifier for the document
    char *name;             // file name of the document    
    int   word_count;       // number of words in the document      
    struct Tree_Node *left; // pointer to the next node in the list
	struct Tree_Node *right; // pointer to the next node in the list

}Tree_Node;

Tree_Node* root;


int next_id;     // ID of the next document to be added
int direction;

int bstdb_init(void){

	next_id = 0;
	direction = -1;
	root = NULL;
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	return 1;
}

int bstdb_add(char *name, int word_count){

    int left_right;

    Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->name = *name;
	new_node->word_count = word_count;
	new_node->doc_id = next_id;

    Tree_Node* prev = NULL;
    Tree_Node* curr = NULL;
    Tree_Node* next = NULL;

    if(root == NULL){
        new_node->left = NULL;
        new_node->right = NULL;
        root = new_node;
    }
    else{
        curr = root;
        while(curr != NULL){
            if(next_id <= curr->doc_id){
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


	if(direction < 0 && next_id <= 0){
		next_id--;
	}

	if(direction > 0 && next_id < 0){
		next_id = (next_id * (-1));
	}

	if(direction < 0 && next_id > 0){
		next_id++;
		next_id = (next_id * direction);
	}

	if(direction > 0 && next_id > 0){
		next_id++;
	}

	direction = (direction * (-1));

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
	return -1;
}

int
bstdb_get_word_count ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	return -1;
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	return 0;
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
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
}




// //-------------------------------------------

// static void
// free_list_node ( struct list_node *node ) {
//     struct list_node *p;
//     p = node;
//     while (p) {
//         p = node->next;
//         if (node->name) free(node->name);
//         free(node);
//         node = p;
//     }
// }

// static struct list_node *
// find_document ( int doc_id ) {
//     struct list_node *p = g_linked_list;
    
//     // Count how many times this function was called so we can get 
//     // average number of nodes traversed for each query
//     g_num_searches++;
    
//     while (p) {
//         // count the number of traversals
//         g_num_comps++;
//         // If we found the node, return it. Otherwise keep searching.
//         if (p->doc_id == doc_id) { break; }
//         p = p->next;
//     }

//     return p;
// }

// static int
// len_list ( struct list_node *ln ) {
//     int count = 0;
//     while (ln) {
//         count++;
//         ln = ln->next;
//     }
//     return count;
// }

// static struct list_node*
// create_list_node ( int doc_id, char *name, int word_count, 
//         struct list_node *next ) {
//     struct list_node *ln;
//     size_t len_name;

//     // Allocate memory for the new list node
//     ln = malloc( sizeof(struct list_node) );
    
//     // malloc can fail, so make sure ln is pointing to something before we try
//     // writing to it.
//     if (ln) {       
//         // Store data in the list node
//         ln->doc_id     = doc_id;
//         ln->word_count = word_count;
//         ln->next       = next;

//         // Allocate memory to store the file name and copy the string into the
//         // new list node
//         len_name = strlen(name)+1;
//         ln->name = calloc(len_name, sizeof(char));
//         if (ln->name) {
//             // if calloc was successful, copy the filename into the node
//             strcpy( ln->name, name );
//         } else {
//             // if calloc failed, release any memory that was allocated and 
//             // report an error by returning NULL
//             ln->next = NULL;
//             free_list_node(ln);
//             ln = NULL;
//         }
//     }

//     return ln;
// }
