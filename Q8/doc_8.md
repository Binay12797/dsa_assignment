# Q8. Write a program that generates a list of N random integers in the range [1, 1000], where N is provided by the user at run time. Then perform sorting using a chosen algorithm and display comparisons and swaps.

### (a) Defining Data Structures:
```c
#define MAX 1000

int arr[MAX], temp[MAX];
int n;
long long comparisons, swaps;
```

**Explanation:**
* `#define MAX 1000` sets the maximum number of elements the array can hold
* `arr[MAX]` stores the randomly generated integers to be sorted
* `temp[MAX]` is a temporary auxiliary array used exclusively by Merge Sort during the merge step
* `n` stores the user-provided count of integers
* `comparisons` and `swaps` are `long long` counters that track the total number of comparisons and swaps/moves made by whichever algorithm is chosen — `long long` is used since large inputs can produce millions of operations

---

### (b) Functions:

* `printArray(int a[], int size)`: Prints all elements of the array on a single line.
* `swap(int a[], int i, int j)`: Swaps two elements at indices `i` and `j` and increments the `swaps` counter.
* `bubbleSort()`: Repeatedly compares adjacent elements and swaps them if out of order, bubbling the largest unsorted element to its correct position each pass.
* `selectionSort()`: Finds the minimum element in the unsorted portion and swaps it into position — performs at most `n-1` swaps regardless of input.
* `insertionSort()`: Builds the sorted array one element at a time by inserting each new element into its correct position among the already-sorted elements.
* `merge(int left, int mid, int right)`: Merges two sorted halves of `arr[]` into a single sorted section using `temp[]` as scratch space, counting each element copy as a move.
* `mergeSort(int left, int right)`: Recursively splits the array in half until single elements remain, then merges them back in sorted order.

---

### (c) Key Logic — Counting Comparisons and Swaps

Each algorithm increments the global `comparisons` and `swaps` counters at the exact point the operation occurs:

**Bubble Sort** — every adjacent pair is a comparison; every out-of-order swap is counted:
```c
comparisons++;
if (arr[j] > arr[j + 1])
    swap(arr, j, j + 1);  // swap() increments swaps
```

**Selection Sort** — every inner loop iteration is a comparison; only swaps when minimum isn't already in place:
```c
comparisons++;
if (arr[j] < arr[minIdx])
    minIdx = j;
// ...
if (minIdx != i)
    swap(arr, i, minIdx);
```

**Insertion Sort** — each while-loop check and the final boundary check are comparisons; each shift counts as a swap:
```c
while (j >= 0 && arr[j] > key)
{
    comparisons++;
    arr[j + 1] = arr[j];
    swaps++;
    j--;
}
comparisons++; // the failing comparison that exits the loop
```

**Merge Sort** — each element comparison during merge is counted; each element copy into `temp[]` counts as a move:
```c
comparisons++;
if (arr[i] <= arr[j])
    temp[k++] = arr[i++];
// ...
arr[x] = temp[x];
swaps++;  // copy back counts as a move
```

> For Merge Sort, `swaps` is labeled **"Total Moves (copy)"** in the output since Merge Sort does not swap in place — it copies elements.

---

### (d) Algorithm Comparison

| Algorithm | Best Case | Average Case | Worst Case | Swaps | Stable |
| :--- | :--- | :--- | :--- | :--- | :--- |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(n²) | Yes |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(n) | No |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(n²) | Yes |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n log n) | Yes |

---

### (e) Main Method Organization

The `main()` function serves as the interface:
1. **Seed**: Calls `srand(time(NULL))` to ensure different random numbers on each run.
2. **Input**: Reads `n` from the user and fills `arr[]` with `n` random integers in range `[1, 1000]` using `(rand() % 1000) + 1`.
3. **Print Before**: Displays the unsorted array.
4. **Menu**: Presents the four sorting algorithm choices and reads the user's selection.
5. **Sort**: Calls the chosen algorithm — all algorithms operate on the global `arr[]` and update the global counters.
6. **Print After**: Displays the sorted array.
7. **Statistics**: Prints total comparisons and total swaps (or moves for Merge Sort).

---

### (f) Sample Output / Test Cases

All four algorithms tested on the same array `[767, 435, 688, 393, 224, 884, 86, 841, 391, 402]` with N=10:

**Bubble Sort:**
```text
Enter value of N (number of integers) : 10

Array before sorting:
767 435 688 393 224 884 86 841 391 402

Choose a sorting algorithm:
1. Bubble Sort
2. Selection Sort
3. Insertion Sort
4. Merge Sort
Enter choice (1-4) : 1

Using Bubble Sort...

Array after sorting:
86 224 391 393 402 435 688 767 841 884

--- Statistics ---
Total Comparisons : 45
Total Swaps       : 27
```

**Selection Sort:**
```text
Using Selection Sort...

Array after sorting:
86 224 391 393 402 435 688 767 841 884

--- Statistics ---
Total Comparisons : 45
Total Swaps       : 7
```

**Insertion Sort:**
```text
Using Insertion Sort...

Array after sorting:
86 224 391 393 402 435 688 767 841 884

--- Statistics ---
Total Comparisons : 36
Total Swaps       : 27
```

**Merge Sort:**
```text
Using Merge Sort...

Array after sorting:
86 224 391 393 402 435 688 767 841 884

--- Statistics ---
Total Comparisons : 21
Total Moves (copy): 34
```

---

### (g) Observations from Test Results (N=10)

| Algorithm | Comparisons | Swaps/Moves |
| :--- | :--- | :--- |
| Bubble Sort | 45 | 27 |
| Selection Sort | 45 | 7 |
| Insertion Sort | 36 | 27 |
| Merge Sort | 21 | 34 |

* **Selection Sort** makes the fewest swaps (`7`) — it only swaps once per pass to place the minimum
* **Merge Sort** makes the fewest comparisons (`21`) — its O(n log n) nature shines even at small N
* **Bubble and Selection Sort** tie on comparisons (`45`) — both do n*(n-1)/2 comparisons in the worst case
* **Merge Sort** has the most moves (`34`) due to copying elements between `arr[]` and `temp[]`