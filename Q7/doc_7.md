# Q7. Given a weighted graph, implement Dijkstra's algorithm to find the shortest path from a source node to all other nodes.

### (a) Defining Data Structures:
```c
#define MAX 10
#define INF 99999

int dist[MAX];
int visited[MAX];
int adjMatrix[MAX][MAX];
int vertices;
```

**Explanation:**
* `#define MAX 10` sets the maximum number of vertices the graph can have
* `#define INF 99999` represents infinity — the initial distance to all unvisited vertices, meaning "not yet reachable"
* `dist[MAX]` stores the current known shortest distance from the source to each vertex
* `visited[MAX]` tracks which vertices have already been finalized (shortest path confirmed)
* `adjMatrix[MAX][MAX]` is a 2D weighted adjacency matrix where `adjMatrix[i][j]` holds the weight of the edge between vertex `i` and `j`, and `0` means no edge
* `vertices` stores the total number of vertices in the graph

---

### (b) Functions:

* `minDistance()`: Scans the `dist[]` array and returns the index of the unvisited vertex with the smallest current distance. This is the greedy selection step at the core of Dijkstra's algorithm.
* `dijkstra(int src)`: Implements the full Dijkstra algorithm. Initializes all distances to `INF` and source distance to `0`, then repeatedly picks the nearest unvisited vertex, marks it visited, and relaxes all its neighbors.
* `displayResult(int src)`: Prints a formatted table showing the shortest distance from the source to every other vertex. Unreachable vertices are shown as `INF`.
* `displayMatrix()`: Prints the weighted adjacency matrix with `-` for no edge and the actual weight otherwise.

---

### (c) Key Logic — Dijkstra's Algorithm

Dijkstra works by **greedily** always extending the shortest known path:

```c
dist[src] = 0;

for (int count = 0; count < vertices - 1; count++)
{
    int u = minDistance();   
    visited[u] = 1;          

    for (int v = 0; v < vertices; v++)
    {
        if (!visited[v] &&
            adjMatrix[u][v] != 0 &&
            dist[u] != INF &&
            dist[u] + adjMatrix[u][v] < dist[v])
        {
            dist[v] = dist[u] + adjMatrix[u][v]; 
        }
    }
}
```

The inner condition is called **edge relaxation** — if going through `u` to reach `v` gives a shorter path than the currently known distance to `v`, update it.

---

### (d) Step-by-Step Trace

**Example Graph:**
```
        10
   0 ────── 1
   |      / |
  3|    4/  |2
   |   /    |
   2 ────── 3 ────── 4
       8         7
```

**Edge list:** `(0,1,10), (0,2,3), (1,2,4), (1,3,2), (2,3,8), (3,4,7)`

| Iteration | Vertex Picked | dist[0] | dist[1] | dist[2] | dist[3] | dist[4] |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Start | — | 0 | INF | INF | INF | INF |
| 1 | `0` (dist=0) | 0 | 10 | 3 | INF | INF |
| 2 | `2` (dist=3) | 0 | 7 | 3 | 11 | INF |
| 3 | `1` (dist=7) | 0 | 7 | 3 | 9 | INF |
| 4 | `3` (dist=9) | 0 | 7 | 3 | 9 | 16 |
| 5 | `4` (dist=16) | 0 | 7 | 3 | 9 | 16 |

**Final shortest paths from vertex `0`:** `0→0=0`, `0→2→1=7`, `0→2=3`, `0→2→1→3=9`, `0→2→1→3→4=16`

---

### (e) Main Method Organization

The `main()` function serves as the interface:
1. **Setup**: Hardcodes `vertices = 5` and `src = 0`, and defines the graph as a 2D array `graph[5][5]` with weights.
2. **Copy**: Transfers the hardcoded values into `adjMatrix[][]` so all functions can access it.
3. **Display Matrix**: Calls `displayMatrix()` to show the weighted adjacency matrix.
4. **Run Algorithm**: Calls `dijkstra(src)` to compute shortest distances from vertex `0`.
5. **Output**: Calls `displayResult(src)` to print the final distance table.

---

### (f) Sample Output

```text
Graph edges and weights:
  (0,1)=10  (0,2)=3
  (1,2)=4   (1,3)=2
  (2,3)=8   (3,4)=7

Adjacency Matrix (weights):
       0    1    2    3    4
 0     -   10    3    -    -
 1    10    -    4    2    -
 2     3    4    -    8    -
 3     -    2    8    -    7
 4     -    -    -    7    -

Shortest distances from source vertex 0:
Vertex     Distance
--------------------
0          0
1          7
2          3
3          9
4          16
```

---

### (g) Key Properties of Dijkstra's Algorithm

| Property | Detail |
| :--- | :--- |
| Type | Greedy algorithm |
| Works on | Non-negative weighted graphs only |
| Time Complexity | O(V²) with adjacency matrix |
| Space Complexity | O(V²) for the adjacency matrix |
| Limitation | Does not work with negative edge weights |
| Best used for | GPS navigation, network routing, shortest path problems |