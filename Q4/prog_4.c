/* How can we implement the doubly linked list using structure? Write a method to
insert(after given node) and delete the node in a doubly linked list. Write main() to
demonstrate the use of the functions. */

#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
};


struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void insertAfter(struct Node* prevNode, int data)
{
    if (prevNode == NULL)
    {
        printf("Previous node cannot be NULL\n");
        return;
    }

    struct Node* newNode = createNode(data);

    newNode->next = prevNode->next; // new node points forward to prev's next
    newNode->prev = prevNode;       // new node points back to prevNode

    if (prevNode->next != NULL)
        prevNode->next->prev = newNode; // old next node points back to new node

    prevNode->next = newNode;       // prevNode now points forward to new node
}


void deleteNode(struct Node** head, struct Node* delNode)
{
    if (*head == NULL || delNode == NULL)
    {
        printf("List is empty or node is NULL\n");
        return;
    }

    if (*head == delNode)
        *head = delNode->next; // move head if deleting head node

    if (delNode->next != NULL)
        delNode->next->prev = delNode->prev; // bypass forward

    if (delNode->prev != NULL)
        delNode->prev->next = delNode->next; // bypass backward

    free(delNode);
    printf("Node deleted successfully\n");
}


void displayForward(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("Forward  : ");
    struct Node* temp = head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


void displayBackward(struct Node* head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next; // go to last node

    printf("Backward : ");
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}


int main()
{
    struct Node* head = NULL;

    // Build initial list: 10 <-> 20 <-> 30
    head = createNode(10);
    insertAfter(head, 20);
    insertAfter(head->next, 30);

    printf("Initial List: \n");
    displayForward(head);
    displayBackward(head);

    // Insert 15 after node with value 10
    printf("\nAfter inserting 15, after node 10:\n");
    insertAfter(head, 15);
    displayForward(head);
    displayBackward(head);

    // Delete head node (10)
    printf("\nAfter deleting head node (10):\n");
    deleteNode(&head, head);
    displayForward(head);
    displayBackward(head);

    // Delete node (20)
    printf("\nAfter deleting node (20):\n");
    deleteNode(&head, head->next);
    displayForward(head);
    displayBackward(head);

    return 0;
}