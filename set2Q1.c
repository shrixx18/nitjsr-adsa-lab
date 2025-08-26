#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

//insertion sort

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//(ii) Bubble Sort


void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// (iii) Selection Sort

void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

/**
 * (iv) Shell Sort
 * An improvement over insertion sort, it allows the exchange of items that are far apart.
 * The gap between elements is gradually decreased.
 */
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

/**
 * (v) Quick Sort
 * A divide-and-conquer algorithm. It picks a 'pivot' element and partitions
 * the array around the pivot.
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * (vi) Merge Sort
 * A divide-and-conquer algorithm. It divides the array into two halves,
 * sorts them recursively, and then merges the two sorted halves.
 */
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/**
 * (vii) Heap Sort
 * A comparison-based sort that uses a binary heap data structure. It first builds
 * a max heap, then repeatedly extracts the maximum element and rebuilds the heap.
 */
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/**
 * (viii) Radix Sort
 * A non-comparative integer sorting algorithm that sorts data with integer keys
 * by grouping keys by individual digits which share the same significant position.
 */
void countSortForRadix(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };

    for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortForRadix(arr, n, exp);
}

/**
 * (ix) Counting Sort
 * An integer sorting algorithm that operates by counting the number of objects
 * that have each distinct key value.
 */
void countingSort(int arr[], int n) {
    int max = getMax(arr, n);
    int* output = (int*)malloc(n * sizeof(int));
    int* count = (int*)calloc(max + 1, sizeof(int));

    for (int i = 0; i < n; i++) count[arr[i]]++;
    for (int i = 1; i <= max; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
    free(count);
}

/**
 * (x) Bucket Sort
 * Works by distributing elements into a number of buckets. Each bucket is then
 * sorted individually. Good for uniformly distributed data.
 */
struct Node {
    int data;
    struct Node* next;
};

struct Node* insertionSortList(struct Node* list_head) {
    if (!list_head || !list_head->next) return list_head;
    struct Node* sorted = NULL;
    struct Node* current = list_head;
    while (current != NULL) {
        struct Node* next = current->next;
        if (!sorted || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

void bucketSort(int arr[], int n) {
    if (n <= 0) return;
    int max_val = getMax(arr, n);
    int num_buckets = n > 10 ? 10 : n; // Use n buckets or 10, for simplicity
    struct Node** buckets = (struct Node**)calloc(num_buckets, sizeof(struct Node*));

    for (int i = 0; i < n; i++) {
        int bucket_index = (long long)arr[i] * num_buckets / (max_val + 1);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = buckets[bucket_index];
        buckets[bucket_index] = newNode;
    }

    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = insertionSortList(buckets[i]);
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(buckets);
}

/**
 * (xi) Radix Exchange Sort
 * A bitwise, recursive version of Radix sort. It partitions the array based on the
 * most significant bit, then recursively sorts the two sub-arrays.
 */
void radixExchangeSortRec(int arr[], int l, int r, int b) {
    if (l >= r || b < 0) return;
    int i = l, j = r;
    int bit_mask = 1 << b;

    while (i <= j) {
        while (i <= j && (arr[i] & bit_mask) == 0) i++;
        while (i <= j && (arr[j] & bit_mask) != 0) j--;
        if (i < j) swap(&arr[i++], &arr[j--]);
    }
    radixExchangeSortRec(arr, l, j, b - 1);
    radixExchangeSortRec(arr, i, r, b - 1);
}

void radixExchangeSort(int arr[], int n) {
    int max_val = getMax(arr, n);
    int msb_pos = 0;
    // Find the position of the most significant bit in the largest number
    while ((1 << msb_pos) <= max_val && msb_pos < 31) {
        msb_pos++;
    }
    radixExchangeSortRec(arr, 0, n - 1, msb_pos - 1);
}

/**
 * (xii) Address Calculation Sort
 * A variation of Bucket Sort. It uses a function to calculate a probable
 * address (bucket) for each element.
 */
void addressCalculationSort(int arr[], int n) {
    if (n <= 0) return;
    int max_val = getMax(arr, n);
    int num_buckets = 10;
    int** buckets = (int**)malloc(num_buckets * sizeof(int*));
    for(int i=0; i<num_buckets; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int));
    }
    int* bucket_counts = (int*)calloc(num_buckets, sizeof(int));
    
    // Distribute elements into buckets based on an "address calculation"
    for (int i = 0; i < n; i++) {
        int bucket_index = (long long)arr[i] * num_buckets / (max_val + 1);
        buckets[bucket_index][bucket_counts[bucket_index]++] = arr[i];
    }

    // Sort each bucket and place back into the main array
    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        insertionSort(buckets[i], bucket_counts[i]);
        for (int j = 0; j < bucket_counts[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }

    for(int i=0; i<num_buckets; i++) free(buckets[i]);
    free(buckets);
    free(bucket_counts);
}

int main() {
    int n, choice;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: Number of elements must be positive.\n");
        return 1;
    }

    int* original_arr = (int*)malloc(n * sizeof(int));
    int* arr_to_sort = (int*)malloc(n * sizeof(int));

    if (original_arr == NULL || arr_to_sort == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d non-negative integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &original_arr[i]);
        if (original_arr[i] < 0) {
            printf("Error: Please enter only non-negative integers.\n");
            free(original_arr);
            free(arr_to_sort);
            return 1;
        }
    }

    do {
        // Use a fresh copy of the original array for each sorting operation
        copyArray(original_arr, arr_to_sort, n);

        printf("\n\n=============== Sorting Algorithms Menu ===============\n");
        printf(" 1. Insertion Sort            7. Heap Sort\n");
        printf(" 2. Bubble Sort               8. Radix Sort\n");
        printf(" 3. Selection Sort            9. Counting Sort\n");
        printf(" 4. Shell Sort               10. Bucket Sort\n");
        printf(" 5. Quick Sort               11. Radix Exchange Sort\n");
        printf(" 6. Merge Sort               12. Address Calculation Sort\n");
        printf(" 0. Exit\n");
        printf("=====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice != 0) {
            printf("\nArray before sorting: ");
            printArray(arr_to_sort, n);
        }

        switch (choice) {
            case 1:
                printf("\n--- Sorting with Insertion Sort ---\n");
                insertionSort(arr_to_sort, n);
                break;
            case 2:
                printf("\n--- Sorting with Bubble Sort ---\n");
                bubbleSort(arr_to_sort, n);
                break;
            case 3:
                printf("\n--- Sorting with Selection Sort ---\n");
                selectionSort(arr_to_sort, n);
                break;
            case 4:
                printf("\n--- Sorting with Shell Sort ---\n");
                shellSort(arr_to_sort, n);
                break;
            case 5:
                printf("\n--- Sorting with Quick Sort ---\n");
                quickSort(arr_to_sort, 0, n - 1);
                break;
            case 6:
                printf("\n--- Sorting with Merge Sort ---\n");
                mergeSort(arr_to_sort, 0, n - 1);
                break;
            case 7:
                printf("\n--- Sorting with Heap Sort ---\n");
                heapSort(arr_to_sort, n);
                break;
            case 8:
                printf("\n--- Sorting with Radix Sort ---\n");
                radixSort(arr_to_sort, n);
                break;
            case 9:
                printf("\n--- Sorting with Counting Sort ---\n");
                countingSort(arr_to_sort, n);
                break;
            case 10:
                printf("\n--- Sorting with Bucket Sort ---\n");
                bucketSort(arr_to_sort, n);
                break;
            case 11:
                printf("\n--- Sorting with Radix Exchange Sort ---\n");
                radixExchangeSort(arr_to_sort, n);
                break;
            case 12:
                printf("\n--- Sorting with Address Calculation Sort ---\n");
                addressCalculationSort(arr_to_sort, n);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                continue; // Skip printing for invalid choice
        }

        if (choice > 0 && choice <= 12) {
            printf("Array after sorting:  ");
            printArray(arr_to_sort, n);
        }

    } while (choice != 0);

    // Clean up allocated memory
    free(original_arr);
    free(arr_to_sort);

    return 0;
}





// --- Sorting Algorithm Implementations ---

/**
 * (i) Insertion Sort
 * Iterates through the array, and for each element, it finds its correct
 * position in the already sorted part of the array and inserts it there.
 */
