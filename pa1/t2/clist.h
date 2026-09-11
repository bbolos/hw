//  
//  clist.h
//  INFO3BSEC Programming Assignment 1, Task 2
//  Created by Gabriele Keller

#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

typedef struct CNode_str {
    int data;
    struct CNode_str *next;
    struct CNode_str *prev;
} CNode;

// Insert a new node with 'data' into the sorted circular doubly linked list.
// The list is assumed to be sorted in ascending order. If the list already contains
// a node with the same data, insert the new node after the existing one(s).
// After insertion, '*clist' will point to the newly inserted node.
void insert_cnode(CNode **clist, int data);

// Delete the first occurrence of a node with 'data' from the sorted circular doubly linked list.
// If the list becomes empty after deletion, '*clist' will be set to NULL.
// Otherwise, '*clist' will point to the successor of the deleted node.
void delete_cnode(CNode **clist, int data);

// Print the elements of the sorted circular doubly linked list, separated by a space,
// starting from the smallest element. Traverse the list once and stop.
// If the list is empty, print nothing.
void print_clist(CNode *clist);

// Apply the function 'fptr' to each element of the list and update the element's data with the result.
// 'fptr' is a pointer to a function that takes an int and returns an int.
// Example: int square(int x) { return x * x; }
void map_clist(CNode *clist, int (*fptr)(int));

// Free all nodes in the list and set '*clist' to NULL.
void free_clist(CNode **clist);

#endif



