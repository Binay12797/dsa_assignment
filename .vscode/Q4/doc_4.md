# Q4. How can we implement the doubly linked list using structure? Write a method to insert(after given node) and delete the node in a doubly linked list. Write main() to demonstrate the use of the functions.

### (a) Defining Data Structures:
```c
struct Node
{
    int data;
    struct Node* prev;
    struct Node* next;
};
```

**Explanation:**
* `struct Node` defines the blueprint for each element in the doubly linked list
* `int data` stores the integer value held by the node
* `struct Node* next` points to the **next** node in the list (forward direction)
* `struct Node* prev` points to the **previous** node in the list (backward direction) — this is what makes it *doubly* linked, unlike a singly linked list which only has `next`

---

### (b) Functions:

* `createNode(int data)`: Dynamically allocates memory for a new node using `malloc()`, assigns the given `data`, and sets both `prev` and `next` to `NULL`. Returns a pointer to the new node.
* `insertAfter(struct Node* prevNode, int data)`: Inserts a new node immediately after the given `prevNode`. Handles all four pointer re-links needed to maintain the doubly linked structure.
* `deleteNode(struct Node** head, struct Node* delNode)`: Removes the given node from the list by bypassing it in both directions and freeing its memory. Uses a double pointer `**head` so the head itself can be updated if the head node is deleted.
* `displayForward(struct Node* head)`: Traverses the list from head to tail using `next` pointers and prints each node's data.
* `displayBackward(struct Node* head)`: First walks to the last node, then traverses back to head using `prev` pointers and prints each node's data — confirming both link directions are intact.

---

### (c) Key Logic — Insert After a Given Node

Inserting a new node after `prevNode` requires updating **four pointers**:

```
Before: ... prevNode <──────────────> nextNode ...

After:  ... prevNode <──> newNode <──> nextNode ...
```

```c
newNode->next = prevNode->next; // 1. new node's next → old next node
newNode->prev = prevNode;       // 2. new node's prev → prevNode
if (prevNode->next != NULL)
    prevNode->next->prev = newNode; // 3. old next node's prev → new node
prevNode->next = newNode;           // 4. prevNode's next → new node
```

> The `NULL` check on step 3 is critical — if `prevNode` was the last node, there is no next node to update.

---

### (d) Key Logic — Delete a Node

Deleting a node requires **bypassing** it in both directions and then freeing its memory:

```
Before: ... prevNode <──> delNode <──> nextNode ...

After:  ... prevNode <──────────────> nextNode ...
```

```c
if (*head == delNode)
    *head = delNode->next;              // update head if needed

if (delNode->next != NULL)
    delNode->next->prev = delNode->prev; // bypass forward link

if (delNode->prev != NULL)
    delNode->prev->next = delNode->next; // bypass backward link

free(delNode);                           // release memory
```

> Both `NULL` checks are essential to handle edge cases like deleting the **first node** (no `prev`) or the **last node** (no `next`).

---

### (e) Main Method Organization

The `main()` function serves as the interface:
1. **Setup**: Builds an initial list `10 ↔ 20 ↔ 30` using `createNode()` and `insertAfter()`.
2. **Insert**: Inserts `15` after node `10` and `25` after node `20`, growing the list to `10 ↔ 15 ↔ 20 ↔ 25 ↔ 30`.
3. **Delete**: Deletes the head node (`10`) and then a middle node (`25`).
4. **Output**: After each operation, both `displayForward()` and `displayBackward()` are called to confirm the list is correctly linked in both directions.

---

### (f) Sample Output / Test Cases

| Operation | Forward Result | Backward Result |
| :--- | :--- | :--- |
| Initial list | `10 20 30` | `30 20 10` |
| Insert `15` after `10` | `10 15 20 30` | `30 20 15 10` |
| Insert `25` after `20` | `10 15 20 25 30` | `30 25 20 15 10` |
| Delete head node (`10`) | `15 20 25 30` | `30 25 20 15` |
| Delete middle node (`25`) | `15 20 30` | `30 20 15` |

```text
=== Initial List ===
Forward  : 10 20 30
Backward : 30 20 10

=== After inserting 15 after node 10 ===
Forward  : 10 15 20 30
Backward : 30 20 15 10

=== After inserting 25 after node 20 ===
Forward  : 10 15 20 25 30
Backward : 30 25 20 15 10

=== After deleting head node (10) ===
Node deleted successfully
Forward  : 15 20 25 30
Backward : 30 25 20 15

=== After deleting middle node (25) ===
Node deleted successfully
Forward  : 15 20 30
Backward : 30 20 15
```