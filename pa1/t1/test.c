#include <stdio.h>
#include "list.h"

//main test function
int main() {
    Node* head = NULL;

    // Insert elements
    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);

    // Print the list
    printList(head); // Output: 10 -> 20 -> 30 -> NULL

    // Free memory
    freeList(head);
    return 0;
}
