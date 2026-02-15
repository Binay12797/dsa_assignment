# Q3. Write and Implement the reverse traversal algorithm in the linked list. Write main() to demonstrate the use of the function.

### (a) Defining Data Structures:
```c
struct Node 
{
    int data;
    struct Node* next;
};
```

**Explanation:**
* `struct Node` defines the blueprint for each element in the linked list
* `int data` stores the integer value held by the node
* `struct Node* next` is a self-referential pointer that points to the next node in the list, forming the chain

---

### (b) Functions:

* `createNode(int data)`: Dynamically allocates memory for a new node using `malloc()`, assigns the given `data` value to it, sets its `next` pointer to `NULL`, and returns a pointer to the newly created node.
* `reverseTraversal(struct Node* head)`: Recursively traverses to the end of the linked list before printing. Each call pushes the current node onto the call stack and only prints after the recursive call returns — effectively printing in reverse order.

---

### (c) Key Logic — Recursive Reverse Traversal

The function works by exploiting the **call stack** as an implicit storage mechanism:

```c
void reverseTraversal(struct Node* head) 
{
    if (head == NULL)   // base case: end of list reached
        return;

    reverseTraversal(head->next); // go deeper first
    printf("%d ", head->data);    // print on the way BACK
}
```

The recursion unwinds as follows for the list `10 → 20 → 30 → 40`:

| Call | Action |
| :--- | :--- |
| `reverseTraversal(10)` | Calls `reverseTraversal(20)` — waits |
| `reverseTraversal(20)` | Calls `reverseTraversal(30)` — waits |
| `reverseTraversal(30)` | Calls `reverseTraversal(40)` — waits |
| `reverseTraversal(40)` | Calls `reverseTraversal(NULL)` — waits |
| `reverseTraversal(NULL)` | Base case hit → returns |
| Back at `40` | Prints `40` |
| Back at `30` | Prints `30` |
| Back at `20` | Prints `20` |
| Back at `10` | Prints `10` |

> No extra array or stack data structure is needed — the recursion itself acts as the stack.

---

### (d) Main Method Organization

The `main()` function serves as the interface:
1. **Setup**: Declares a `head` pointer initialized to `NULL` and a temporary `temp` pointer.
2. **Node Creation**: Manually links 4 nodes by directly assigning `next` pointers:
   ```c
   head = createNode(10);
   head->next = createNode(20);
   head->next->next = createNode(30);
   head->next->next->next = createNode(40);
   ```
3. **Processing**: Calls `reverseTraversal(head)` to print the list in reverse.
4. **Output**: The nodes are printed from tail to head: `40 30 20 10`.

---

### (e) Sample Output / Test Cases

| Linked List | Reverse Traversal Output |
| :--- | :--- |
| `10 → 20 → 30 → 40` | `40 30 20 10` |
| `5 → 10 → 15` | `15 10 5` |
| `99` (single node) | `99` |
| (empty list) | (nothing printed) |

```text
Reverse Traversal: 40 30 20 10
```
