#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array around a pivot
int partition(int arr[], int left, int right, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[right]);  // Move pivot to end
    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            swap(&arr[i], &arr[storeIndex]);
            storeIndex++;
        }
    }
    swap(&arr[storeIndex], &arr[right]);  // Move pivot to its final place
    return storeIndex;
}

// Function to perform randomized selection
int randomizedSelect(int arr[], int left, int right, int k) {
    if (left == right) {  // If the array contains only one element
        return arr[left];
    }

    // Select a pivotIndex between left and right
    int pivotIndex = left + rand() % (right - left + 1);
    pivotIndex = partition(arr, left, right, pivotIndex);

    // The pivot is in its final sorted position
    int length = pivotIndex - left + 1;

    if (length == k) {
        return arr[pivotIndex];
    } else if (k < length) {
        return randomizedSelect(arr, left, pivotIndex - 1, k);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, right, k - length);
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;  // We want to find the 3rd smallest element

    if (k > 0 && k <= n) {
        int result = randomizedSelect(arr, 0, n - 1, k);
        printf("The %d-th smallest element is %d.\n", k, result);
    } else {
        printf("Invalid value of k.\n");
    }

    return 0;
}
