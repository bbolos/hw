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
    if (*clist == NULL){
        newCNode -> next = newCNode;
        newCNode -> prev = newCNode;
        *clist = newCNode;
        return;
    }

    //niet lege lijst zoek juiste node voor plaatsen
    CNode *current = *clist;
    CNode *start = *clist;
    while (
        //niet tussen huidige en volgende node
        !(data >= current -> data && data < current -> next -> data) &&
        //niet een omslagpunt waar data buitenvalt
        !(current -> data > current -> next -> data && (data >= current -> data || data < current -> next -> data)) &&
        //geen hele ronde gedaan
        (current -> next != start)){
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
    //leeg is klaar
    if (clist == NULL || *clist == NULL) {
        return;
    }

    //kijk of er een met data in zit
    CNode *current = *clist;
    CNode *found = NULL;

    do {
        if (current -> data == data){
            found = current;
            break;
        }
        current = current -> next;
    } while (current != *clist);

    //geen gevonden klaar
    if (found == NULL){
        return;
    }

    //gevonden maar enige node
    if (found == found -> next){
        free(found);
        *clist = NULL;
        return;
    }

    //gevonden maar meerdere nodes
    found -> next -> prev = found -> prev;
    found -> prev -> next = found -> next;
    *clist = found -> next;
    free(found);
}

void print_clist(CNode *clist){
    //print niets wanneer de lijst leeg is
    if (clist == NULL){
        return;
    }

    //zoek eerste element
    CNode *current = clist;
    CNode *first = clist;

    do {
        if (current -> data > current -> next -> data){
            first = current -> next;
            break;
        }
        current = current -> next;
    } while (current != clist);

    current = first;
    //print lijst
    do {
        printf("%d ", current -> data);
        current = current -> next;
    } while (current != first);

    printf("\n");
}

void map_clist(CNode *clist, int (*fptr)(int)){
    //doe niks wanneer de lijst of de functie leeg is
    if (clist == NULL || fptr == NULL){
        return;
    }

    //doe de functie op alle elementen
    CNode *current = clist;

    do{
        current -> data = fptr(current -> data);
        current = current -> next;
    } while (current != clist);
}

void free_clist(CNode **clist){
    //leeg return
    if (clist == NULL || *clist == NULL){
        return;
    }

    //breek oneindige loop en free alles
    CNode *current = *clist;
    current -> prev -> next = NULL;

    while (current != NULL){
        CNode *temp = current;
        current = current -> next;
        free(temp);
    }

    *clist = NULL;
}
