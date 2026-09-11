#ifndef LIST_H
#define LIST_H

// Node structure
struct Node_str{
	int data;
	struct Node_str * next;
};

// defining 'Node' to be a type synonym of 'struct Node_str
// (could have been combined with the declaration of Node_str,
// see slides)
typedef struct Node_str Node;

// Functies
Node* createNode(int data);
void insertEnd(Node** head, int data);
void printList(Node* head);
void freeList(Node* head);
int dumpList(Node* head, int *resultBuff, int maxElems);
void reverseList(Node** head);

#endif
