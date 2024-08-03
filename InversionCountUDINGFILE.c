#include <stdio.h>
#include <stdlib.h>

// Merge function to merge two halves and count split inversions
long long mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left;    // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;    // Starting index to be sorted
    long long inv_count = 0;

    // Conditions are checked to ensure that i doesn't exceed mid and j doesn't exceed right
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1); // Number of inversions
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

// Recursive function to count inversions
long long mergeSortAndCount(int arr[], int temp[], int left, int right) {
    long long mid, inv_count = 0;
    if (right > left) {
        mid = (right + left) / 2;

        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

int main() {
    FILE *file = fopen("C:\\Users\\aravs\\Downloads\\_bcb5c6658381416d19b01bfc1d3993b5_IntegerArray.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int n = 100000;
    int *arr = (int *)malloc(n * sizeof(int));
    int *temp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &arr[i]);
    }

    fclose(file);

    long long inversion_count = mergeSortAndCount(arr, temp, 0, n - 1);
    printf("Number of inversions are %lld\n", inversion_count);

    free(arr);
    free(temp);
    return 0;
}
