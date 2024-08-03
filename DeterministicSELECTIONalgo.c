#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Standard partition process of QuickSort. It considers the last element as pivot and moves all smaller elements to the left of it and all greater elements to the right.
int partition(int arr[], int left, int right, int x) {
    int i;
    for (i = left; i < right; i++) {
        if (arr[i] == x) {
            break;
        }
    }
    swap(&arr[i], &arr[right]);

    int pivot = arr[right];
    int storeIndex = left;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            swap(&arr[storeIndex], &arr[j]);
            storeIndex++;
        }
    }
    swap(&arr[storeIndex], &arr[right]);
    return storeIndex;
}

// A simple function to find the median of an array
int findMedian(int arr[], int n) {
    if (n == 0) return INT_MIN;
    qsort(arr, n, sizeof(int), (int (*)(const void *, const void *)) (int (*)(const int *, const int *)) ((int (*)(const void *, const void *)) strcmp));
    return arr[n / 2];
}

// Returns the k-th smallest element in the array arr[left...right]
int deterministicSelect(int arr[], int left, int right, int k) {
    if (k > 0 && k <= right - left + 1) {
        int n = right - left + 1;
        int i, median[(n + 4) / 5]; // There will be ceil(n/5) groups

        for (i = 0; i < n / 5; i++) {
            median[i] = findMedian(arr + left + i * 5, 5);
        }
        if (i * 5 < n) {
            median[i] = findMedian(arr + left + i * 5, n % 5);
            i++;
        }

        int medOfMed = (i == 1) ? median[i - 1] : deterministicSelect(median, 0, i - 1, i / 2);

        int pos = partition(arr, left, right, medOfMed);

        if (pos - left == k - 1) {
            return arr[pos];
        }
        if (pos - left > k - 1) {
            return deterministicSelect(arr, left, pos - 1, k);
        }
        return deterministicSelect(arr, pos + 1, right, k - pos + left - 1);
    }
    return INT_MAX;
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;  // We want to find the 3rd smallest element

    if (k > 0 && k <= n) {
        int result = deterministicSelect(arr, 0, n - 1, k);
        printf("The %d-th smallest element is %d.\n", k, result);
    } else {
        printf("Invalid value of k.\n");
    }

    return 0;
}
