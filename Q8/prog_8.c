#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int arr[MAX], temp[MAX];
int n;
long long comparisons, swaps;

void printArray(int a[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void swap(int a[], int i, int j)
{
    int t  = a[i];
    a[i]   = a[j];
    a[j]   = t;
    swaps++;
}

void bubbleSort()
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

void selectionSort()
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
        {
            comparisons++;
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(arr, i, minIdx);
    }
}

void insertionSort()
{
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j   = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            comparisons++;
            arr[j + 1] = arr[j];
            swaps++;
            j--;
        }
        comparisons++;
        arr[j + 1] = key;
    }
}

void merge(int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right)
    {
        comparisons++;
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (int x = left; x <= right; x++)
    {
        arr[x] = temp[x];
        swaps++;
    }
}

void mergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main()
{
    int choice;
    comparisons = 0;
    swaps       = 0;

    srand(time(NULL));

    printf("Enter value of N/number_of_integers : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        arr[i] = (rand() % 1000) + 1;

    printf("\nArray before sorting:\n");
    printArray(arr, n);

    printf("\nChoose a sorting algorithm:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Insertion Sort\n");
    printf("4. Merge Sort\n");
    printf("Enter choice (1-4) : ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("\nUsing Bubble Sort...\n");
            bubbleSort();
            break;
        case 2:
            printf("\nUsing Selection Sort...\n");
            selectionSort();
            break;
        case 3:
            printf("\nUsing Insertion Sort...\n");
            insertionSort();
            break;
        case 4:
            printf("\nUsing Merge Sort...\n");
            mergeSort(0, n - 1);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
    }

    printf("\nArray after sorting:\n");
    printArray(arr, n);

    printf("\n--- Statistics ---\n");
    printf("Total Comparisons : %lld\n", comparisons);

    if (choice == 4)
        printf("Total Moves (copy): %lld\n", swaps);
    else
        printf("Total Swaps       : %lld\n", swaps);

    return 0;
}