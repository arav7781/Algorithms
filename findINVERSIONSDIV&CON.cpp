#include <stdio.h>
#include <stdlib.h>

// Function to merge two halves and count inversions
int mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted
    int inv_count = 0;

    // Conditions are checked to ensure that i doesn't exceed mid and j doesn't exceed right
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // There are mid - i inversions, because all the remaining elements in the left subarray (arr[i] to arr[mid]) 
            // are greater than arr[j]
            inv_count += (mid - i + 1);
        }
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy the remaining elements of right subarray, if any
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy the sorted subarray into Original array
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

// Function to use divide and conquer approach to count inversions
int mergeSortAndCount(int arr[], int temp[], int left, int right) {
    int mid, inv_count = 0;
    if(left < right){
        // Divide the array into two parts
        mid = (right + left) / 2;

        // Count inversions in left part
        inv_count += mergeSortAndCount(arr, temp, left, mid);

        // Count inversions in right part
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        // Count inversions while merging
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Function to count inversions in the array
int countInversions(int arr[], int n) {
    int *temp = (int *)malloc(sizeof(int) * n);
    return mergeSortAndCount(arr, temp, 0, n - 1);
}

int main() {
    int arr[] = {1, 20, 6, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int inv_count = countInversions(arr, n);
    printf("Number of inversions are %d\n", inv_count);
    return 0;
}
