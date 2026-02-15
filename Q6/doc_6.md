# Q6. Given the array of the data (unsorted), Write a program to build the min and max heap.

### (a) Defining Data Structures:
```c
#define MAX 20

int minHeap[MAX], maxHeap[MAX];
int minSize = 0, maxSize = 0;
```

**Explanation:**
* `#define MAX 20` sets the maximum capacity of both heaps
* `minHeap[MAX]` is the integer array that stores the min heap — where the smallest element is always at index `0` (the root)
* `maxHeap[MAX]` is the integer array that stores the max heap — where the largest element is always at index `0` (the root)
* `minSize` and `maxSize` track how many elements are currently in each heap
* A heap is stored as a **flat array** where for any node at index `i`, its left child is at `2*i+1`, its right child is at `2*i+2`, and its parent is at `(i-1)/2`

---

### (b) Functions:

* `swap(int arr[], int i, int j)`: Swaps two elements at indices `i` and `j` in the given array using a temporary variable.
* `insertMinHeap(int val)`: Inserts a value at the end of the min heap array, then **bubbles it up** by repeatedly comparing with its parent and swapping if the child is smaller, until the min-heap property is restored.
* `insertMaxHeap(int val)`: Inserts a value at the end of the max heap array, then **bubbles it up** by repeatedly comparing with its parent and swapping if the child is larger, until the max-heap property is restored.
* `heapifyDown_Min(int i)`: Recursively pushes a node **down** the min heap by finding the smallest among the node and its two children, swapping if needed, and repeating until the heap property holds.
* `heapifyDown_Max(int i)`: Recursively pushes a node **down** the max heap by finding the largest among the node and its two children, swapping if needed, and repeating until the heap property holds.
* `displayHeap(int arr[], int size, char* type)`: Prints the heap array as a flat list.
* `displayTree(int arr[], int size, char* type)`: Prints the heap level by level to visualize the tree structure.

---

### (c) Key Logic — Heap Array Indexing

A heap is stored in a **flat array** using this parent-child index formula:

| Relationship | Formula |
| :--- | :--- |
| Parent of node `i` | `(i - 1) / 2` |
| Left child of node `i` | `2 * i + 1` |
| Right child of node `i` | `2 * i + 2` |

This means no pointers or dynamic memory are needed — the entire tree structure is implied by the array indices.

---

### (d) Key Logic — Insert with Bubble Up

When inserting a new value, it is placed at the end of the array (next available slot) and then **bubbled up** to its correct position:

```c
void insertMinHeap(int val)
{
    minHeap[minSize] = val;
    int i = minSize;
    minSize++;

    while (i > 0 && minHeap[(i - 1) / 2] > minHeap[i])
    {
        swap(minHeap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}
```

For **Min Heap**: bubble up if child is **smaller** than parent.
For **Max Heap**: bubble up if child is **larger** than parent.

Bubble up trace inserting `5` into a partial min heap `[35, 10, 50]`:

| Step | Array State | Comparison | Action |
| :--- | :--- | :--- | :--- |
| Insert | `[35, 10, 50, 5]` | `5 < parent(10)` | Swap 5 and 10 |
| After swap | `[35, 5, 50, 10]` | `5 < parent(35)` | Swap 5 and 35 |
| After swap | `[5, 35, 50, 10]` | `5` is root | Stop |

---

### (e) Key Logic — Heapify Down

Used after deletion (removing root) to restore the heap property by pushing the misplaced root down:

```c
void heapifyDown_Min(int i)
{
    int smallest = i;
    int left     = 2 * i + 1;
    int right    = 2 * i + 2;

    if (left < minSize && minHeap[left] < minHeap[smallest])
        smallest = left;
    if (right < minSize && minHeap[right] < minHeap[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(minHeap, i, smallest);
        heapifyDown_Min(smallest);
    }
}
```

For **Min Heap**: find the smallest among node and its children, swap downward.
For **Max Heap**: find the largest among node and its children, swap downward.

---

### (f) Main Method Organization

The `main()` function serves as the interface:
1. **Input**: Reads the number of elements `n` from the user, then reads each element one by one into `arr[]` using `scanf()`.
2. **Build**: Calls `insertMinHeap()` and `insertMaxHeap()` for each element, building both heaps simultaneously.
3. **Output**: Displays each heap as a flat array and also as a level-by-level tree structure.

---

### (g) Sample Output / Test Cases

**Input Array:** `35 10 50 5 20 45 15 30`

| Heap Type | Array Representation | Root (Extreme Value) |
| :--- | :--- | :--- |
| Min Heap | `5 10 15 30 20 50 45 35` | `5` (smallest) |
| Max Heap | `50 30 45 20 10 35 15 5` | `50` (largest) |

```text
Enter number of elements : 8
Enter 8 elements        : 35 10 50 5 20 45 15 30

Original Array : 35 10 50 5 20 45 15 30

Min Heap : 5 10 15 30 20 50 45 35

Min Heap Tree Structure:
Level 0: 5
Level 1: 10 15
Level 2: 30 20 50 45
Level 3: 35

Max Heap : 50 30 45 20 10 35 15 5

Max Heap Tree Structure:
Level 0: 50
Level 1: 30 45
Level 2: 20 10 35 15
Level 3: 5
```

---

### (h) Min Heap vs Max Heap Comparison

| Property | Min Heap | Max Heap |
| :--- | :--- | :--- |
| Root value | Smallest element | Largest element |
| Parent vs Child | Parent ≤ Children | Parent ≥ Children |
| Bubble up condition | Child **smaller** than parent | Child **larger** than parent |
| Heapify down condition | Swap with **smallest** child | Swap with **largest** child |
| Common use | Priority queues, Dijkstra's algorithm | Heap sort, scheduling |