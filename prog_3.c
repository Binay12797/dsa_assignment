//Write and Implement the reverse traversal algorithm in the linked list. Write main() to demonstrate the use of the function.

#include <stdio.h>
#include <stdlib.h>

// structure for node
struct Node 
{
    int data;
    struct Node* next;
};

// for new node creation
struct Node* createNode(int data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Reverse Traversal Funtion
void reverseTraversal(struct Node* head) 
{
    if (head == NULL)
        return;

    reverseTraversal(head->next);
    printf("%d ", head->data);
}


int main() 
{
    struct Node* head = NULL;
    struct Node* temp;

    head = createNode(10); //fist
    head->next = createNode(20); //second
    head->next->next = createNode(30); //3rd
    head->next->next->next = createNode(40); //4th

    printf("Reverse Traversal: ");
    reverseTraversal(head);

    return 0;
}
