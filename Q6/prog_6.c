#include <stdio.h>

#define MAX 20

int minHeap[MAX], maxHeap[MAX];
int minSize = 0, maxSize = 0;

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i]   = arr[j];
    arr[j]   = temp;
}

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

void insertMaxHeap(int val)
{
    maxHeap[maxSize] = val;
    int i = maxSize;
    maxSize++;

    while (i > 0 && maxHeap[(i - 1) / 2] < maxHeap[i])
    {
        swap(maxHeap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

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

void heapifyDown_Max(int i)
{
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left < maxSize && maxHeap[left] > maxHeap[largest])
        largest = left;

    if (right < maxSize && maxHeap[right] > maxHeap[largest])
        largest = right;

    if (largest != i)
    {
        swap(maxHeap, i, largest);
        heapifyDown_Max(largest);
    }
}

void displayHeap(int arr[], int size, char* type)
{
    printf("%s Heap : ", type);
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void displayTree(int arr[], int size, char* type)
{
    printf("\n%s Heap Tree Structure:\n", type);
    int level = 0;
    int i     = 0;
    int count = 1;

    while (i < size)
    {
        printf("Level %d: ", level);
        for (int j = 0; j < count && i < size; j++, i++)
            printf("%d ", arr[i]);
        printf("\n");
        level++;
        count *= 2;
    }
}

int main()
{
    int arr[MAX], n;

    printf("Enter number of elements : ");
    scanf("%d", &n);

    printf("Enter %d elements        : ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array : ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++)
    {
        insertMinHeap(arr[i]);
        insertMaxHeap(arr[i]);
    }

    displayHeap(minHeap, minSize, "Min");
    displayTree(minHeap, minSize, "Min");

    printf("\n");

    displayHeap(maxHeap, maxSize, "Max");
    displayTree(maxHeap, maxSize, "Max");

    return 0;
}