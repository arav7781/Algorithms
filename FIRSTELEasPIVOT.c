#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function as described in the video lectures
int partition(int* arr, int left, int right, int* comparisons) {
    int pivot = arr[left];
    int i = left + 1;

    for (int j = left + 1; j <= right; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[left], &arr[i - 1]);
    
    *comparisons += (right - left);
    return i - 1;
}

// QuickSort function
void quickSort(int* arr, int left, int right, int* comparisons) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right, comparisons);
        quickSort(arr, left, pivotIndex - 1, comparisons);
        quickSort(arr, pivotIndex + 1, right, comparisons);
    }
}

// Function to read integers from a file into an array
int* readFile(char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    int* arr = malloc(10000 * sizeof(int)); // Allocate memory for 10000 integers
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    *size = 0;
    while (fscanf(file, "%d", &arr[*size]) != EOF) {
        (*size)++;
    }

    fclose(file);
    return arr;
}

int main() {
    char filename[] = "C:\\Users\\aravs\\Downloads\\_32387ba40b36359a38625cbb397eee65_QuickSort.txt";
    int size;
    int* arr = readFile(filename, &size);

    int comparisons = 0;
    quickSort(arr, 0, size - 1, &comparisons);

    printf("Total number of comparisons: %d\n", comparisons);

    free(arr);
    return 0;
}
