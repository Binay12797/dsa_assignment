/*How can we implement the undirected graph using the adjacency matrix? Write a function
that implements the BFS and DFS technique to traverse through the graph. Demonstrate
the use of your program with an example graph.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 10


int adjMatrix[MAX][MAX]; // initializing adjacency matrix
int visited[MAX];        // visited array for traversal
int vertices;            // number of vertices


int queue[MAX];
int front = -1, rear = -1;

void enqueue(int val)
{
    if (rear == MAX - 1)
    {
        printf("Queue full\n");
        return;
    }
    if (front == -1) front = 0;
    queue[++rear] = val;
}

int dequeue()
{
    if (front == -1 || front > rear)
    {
        printf("Queue empty\n");
        return -1;
    }
    return queue[front++];
}

int isQueueEmpty()
{
    return (front == -1 || front > rear);
}


void initGraph(int v)
{
    vertices = v;
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            adjMatrix[i][j] = 0;
}



void addEdge(int u, int v)
{
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1; 
}


void displayMatrix()
{
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < vertices; i++)
        printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < vertices; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j < vertices; j++)
            printf("%2d ", adjMatrix[i][j]);
        printf("\n");
    }
}


void BFS(int start)
{

    for (int i = 0; i < vertices; i++)
        visited[i] = 0;

    
    front = -1;
    rear = -1;

    printf("\nBFS Traversal starting from vertex %d:\n", start);

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
    printf("\n");
}


void DFS(int vertex)
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    // visit all unvisited neighbors recursively
    for (int i = 0; i < vertices; i++)
    {
        if (adjMatrix[vertex][i] == 1 && visited[i] == 0)
            DFS(i);
    }
}

void startDFS(int start)
{
    
    for (int i = 0; i < vertices; i++)
        visited[i] = 0;

    printf("\nDFS Traversal starting from vertex %d:\n", start);
    DFS(start);
    printf("\n");
}



int main()
{
    
    initGraph(6);

    addEdge(0, 1);
    addEdge(0, 3);
    addEdge(1, 2);
    addEdge(1, 4);
    addEdge(3, 4);
    addEdge(4, 5);

    displayMatrix();

    BFS(0);
    startDFS(0);

    return 0;
}