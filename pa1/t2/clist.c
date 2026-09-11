#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

void insert_cnode(CNode **clist, int data){
    if (clist == NULL){
        return;
    }

    //maak nieuwe node en wijs geheugen toe
    CNode* newCNode = (CNode*) malloc (sizeof(CNode));
    if (newCNode == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newCNode -> data = data;

    //check voor een lege lijst
    if (*clist = NULL){
        newCNode -> next = newCNode;
        newCNode -> prev = newCNode;
        *clist = newCNode;
        return;
    }

    //niet lege lijst zoek juiste node voor plaatsen
    CNode *current = *clist;
    CNode *start = *clist
    while (
        //niet tussen huidige en volgende node
        !(data >= current -> data && data < current -> next -> data) &&
        //niet een omslagpunt waar data buitenvalt
        !(current -> data > current -> next -> data && (data >= current -> data || data < curr -> next -> data)) &&
        //geen hele ronde gedaan
        (current -> next != start)
    ){
        current = current -> next;
    }

    //voeg de nieuwe node toe en update clist
    newCNode -> next = current -> next;
    newCNode -> prev = current;
    current -> next -> prev = newCNode;
    current -> next = newCNode;
    *clist = newCNode;
}

void delete_cnode(CNode **clist, int data){
    
}
