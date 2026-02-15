#include <stdio.h>

#define MAX 10
#define INF 99999

int dist[MAX];
int visited[MAX];
int adjMatrix[MAX][MAX];
int vertices;

int minDistance()
{
    int min     = INF;
    int minIndex = -1;

    for (int i = 0; i < vertices; i++)
    {
        if (visited[i] == 0 && dist[i] <= min)
        {
            min      = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(int src)
{
    for (int i = 0; i < vertices; i++)
    {
        dist[i]    = INF;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; count++)
    {
        int u = minDistance();

        if (u == -1)
            break;

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
}

void displayResult(int src)
{
    printf("\nShortest distances from source vertex %d:\n", src);
    printf("%-10s %-10s\n", "Vertex", "Distance");
    printf("--------------------\n");

    for (int i = 0; i < vertices; i++)
    {
        if (dist[i] == INF)
            printf("%-10d %-10s\n", i, "INF");
        else
            printf("%-10d %-10d\n", i, dist[i]);
    }
}

void displayMatrix()
{
    printf("\nAdjacency Matrix (weights):\n");
    printf("   ");
    for (int i = 0; i < vertices; i++)
        printf("%5d", i);
    printf("\n");

    for (int i = 0; i < vertices; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j < vertices; j++)
        {
            if (adjMatrix[i][j] == 0)
                printf("%5s", "-");
            else
                printf("%5d", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    vertices = 5;
    int src  = 0;

    int graph[5][5] = {
        {0, 10,  3,  0,  0},
        {10, 0,  4,  2,  0},
        { 3, 4,  0,  8,  0},
        { 0, 2,  8,  0,  7},
        { 0, 0,  0,  7,  0}
    };

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            adjMatrix[i][j] = graph[i][j];

    printf("Graph edges and weights:\n");
    printf("  (0,1)=10  (0,2)=3\n");
    printf("  (1,2)=4   (1,3)=2\n");
    printf("  (2,3)=8   (3,4)=7\n");

    displayMatrix();
    dijkstra(src);
    displayResult(src);

    return 0;
}