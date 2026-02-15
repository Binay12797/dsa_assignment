# Q5. How can we implement the undirected graph using the adjacency matrix? Write a function that implements the BFS and DFS technique to traverse through the graph. Demonstrate the use of your program with an example graph.

### (a) Defining Data Structures:
```c
#define MAX 10

int adjMatrix[MAX][MAX]; // adjacency matrix
int visited[MAX];        // visited array for traversal
int vertices;            // number of vertices

int queue[MAX];          // queue for BFS
int front = -1, rear = -1;
```

**Explanation:**
* `adjMatrix[MAX][MAX]` is a 2D integer array representing the graph. `adjMatrix[i][j] = 1` means there is an edge between vertex `i` and vertex `j`, and `0` means no edge
* `visited[MAX]` tracks which vertices have already been visited during traversal to avoid revisiting
* `vertices` stores the total number of vertices in the graph
* `queue[MAX]` with `front` and `rear` implements a simple linear queue used exclusively by BFS

---

### (b) Functions:

* `initGraph(int v)`: Initializes the graph with `v` vertices by setting all cells of the adjacency matrix to `0`.
* `addEdge(int u, int v)`: Adds an undirected edge between vertices `u` and `v` by setting `adjMatrix[u][v] = 1` **and** `adjMatrix[v][u] = 1` (both directions).
* `displayMatrix()`: Prints the full adjacency matrix with row and column labels for easy reading.
* `enqueue(int val)` / `dequeue()` / `isQueueEmpty()`: Helper functions that implement a basic linear queue for use in BFS.
* `BFS(int start)`: Implements **Breadth First Search** — visits all vertices level by level using a queue. Resets the `visited` array and queue before starting.
* `DFS(int vertex)`: Recursive helper that implements **Depth First Search** — dives as deep as possible along each branch before backtracking.
* `startDFS(int start)`: Wrapper for DFS that resets the `visited` array and initiates the recursive `DFS()` call.

---

### (c) Key Logic — Adjacency Matrix for Undirected Graph

For an undirected graph, every edge `(u, v)` must be recorded **symmetrically**:

```c
void addEdge(int u, int v)
{
    adjMatrix[u][v] = 1; // u → v
    adjMatrix[v][u] = 1; // v → u 
}
```

This ensures the matrix is always **symmetric along the diagonal**, i.e., `adjMatrix[i][j]` always equals `adjMatrix[j][i]`.

---

### (d) Key Logic — BFS (Breadth First Search)

BFS uses a **queue** to visit vertices level by level — all neighbors of a node are visited before going deeper:

```c
visited[start] = 1;
enqueue(start);

while (!isQueueEmpty())
{
    int current = dequeue();
    printf("%d ", current);

    for (int i = 0; i < vertices; i++)
    {
        if (adjMatrix[current][i] == 1 && visited[i] == 0)
        {
            visited[i] = 1;
            enqueue(i);
        }
    }
}
```

BFS trace for the example graph starting from vertex `0`:

| Step | Current | Queue After | Visited |
| :--- | :--- | :--- | :--- |
| 1 | `0` | `[1, 3]` | 0 |
| 2 | `1` | `[3, 2, 4]` | 0, 1 |
| 3 | `3` | `[2, 4]` | 0, 1, 3 |
| 4 | `2` | `[4]` | 0, 1, 3, 2 |
| 5 | `4` | `[5]` | 0, 1, 3, 2, 4 |
| 6 | `5` | `[]` | 0, 1, 3, 2, 4, 5 |

**Result:** `0 1 3 2 4 5`

---

### (e) Key Logic — DFS (Depth First Search)

DFS uses **recursion** (the call stack) to dive as deep as possible before backtracking:

```c
void DFS(int vertex)
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < vertices; i++)
    {
        if (adjMatrix[vertex][i] == 1 && visited[i] == 0)
            DFS(i); // recurse deeper
    }
}
```

DFS trace for the example graph starting from vertex `0`:

| Step | Vertex | Action |
| :--- | :--- | :--- |
| 1 | `0` | Visit, recurse into `1` |
| 2 | `1` | Visit, recurse into `2` |
| 3 | `2` | Visit, no unvisited neighbors → backtrack |
| 4 | `1` | Recurse into `4` |
| 5 | `4` | Visit, recurse into `3` |
| 6 | `3` | Visit, no unvisited neighbors → backtrack |
| 7 | `4` | Recurse into `5` |
| 8 | `5` | Visit, no unvisited neighbors → backtrack |

**Result:** `0 1 2 4 3 5`

---

### (f) Example Graph

```
    0 ── 1 ── 2
    |    |
    3 ── 4 ── 5
```

| Edge | Vertices Connected |
| :--- | :--- |
| `(0,1)` | 0 and 1 |
| `(0,3)` | 0 and 3 |
| `(1,2)` | 1 and 2 |
| `(1,4)` | 1 and 4 |
| `(3,4)` | 3 and 4 |
| `(4,5)` | 4 and 5 |

---

### (g) Sample Output

```text
Adjacency Matrix:
    0  1  2  3  4  5
 0  0  1  0  1  0  0
 1  1  0  1  0  1  0
 2  0  1  0  0  0  0
 3  1  0  0  0  1  0
 4  0  1  0  1  0  1
 5  0  0  0  0  1  0

BFS Traversal starting from vertex 0:
0 1 3 2 4 5

DFS Traversal starting from vertex 0:
0 1 2 4 3 5
```

---

### (h) BFS vs DFS Comparison

| Feature | BFS | DFS |
| :--- | :--- | :--- |
| Data Structure Used | Queue | Recursion (Call Stack) |
| Traversal Order | Level by level (wide) | Branch by branch (deep) |
| Result from vertex `0` | `0 1 3 2 4 5` | `0 1 2 4 3 5` |
| Best used for | Shortest path, nearest neighbor | Cycle detection, topological sort |
