#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Structure to store the result of the tournament
typedef struct {
    int max;
    int *defeated;
    int defeatedCount;
} TournamentResult;

// Helper function to perform the tournament and track defeated numbers
TournamentResult tournamentMax(int *arr, int left, int right) {
    if (left == right) {
        TournamentResult result;
        result.max = arr[left];
        result.defeated = (int *)malloc(0 * sizeof(int));
        result.defeatedCount = 0;
        return result;
    }

    int mid = left + (right - left) / 2;
    TournamentResult leftResult = tournamentMax(arr, left, mid);
    TournamentResult rightResult = tournamentMax(arr, mid + 1, right);

    if (leftResult.max > rightResult.max) {
        leftResult.defeated = (int *)realloc(leftResult.defeated, (leftResult.defeatedCount + 1) * sizeof(int));
        leftResult.defeated[leftResult.defeatedCount++] = rightResult.max;
        for (int i = 0; i < rightResult.defeatedCount; i++) {
            leftResult.defeated = (int *)realloc(leftResult.defeated, (leftResult.defeatedCount + 1) * sizeof(int));
            leftResult.defeated[leftResult.defeatedCount++] = rightResult.defeated[i];
        }
        free(rightResult.defeated);
        return leftResult;
    } else {
        rightResult.defeated = (int *)realloc(rightResult.defeated, (rightResult.defeatedCount + 1) * sizeof(int));
        rightResult.defeated[rightResult.defeatedCount++] = leftResult.max;
        for (int i = 0; i < leftResult.defeatedCount; i++) {
            rightResult.defeated = (int *)realloc(rightResult.defeated, (rightResult.defeatedCount + 1) * sizeof(int));
            rightResult.defeated[rightResult.defeatedCount++] = leftResult.defeated[i];
        }
        free(leftResult.defeated);
        return rightResult;
    }
}

// Function to find the second largest number in the array
int findSecondLargest(int *arr, int n) {
    TournamentResult result = tournamentMax(arr, 0, n - 1);
    int largest = result.max;

    // Find the maximum in the defeated array
    int secondLargest = INT_MIN;
    for (int i = 0; i < result.defeatedCount; i++) {
        if (result.defeated[i] > secondLargest) {
            secondLargest = result.defeated[i];
        }
    }

    free(result.defeated);
    return secondLargest;
}

// Driver program to test above functions
int main() {
    int arr[] = {3, 2, 1, 5, 4, 7, 6, 8}; // Example input array
    int n = sizeof(arr) / sizeof(arr[0]);
    int secondLargest = findSecondLargest(arr, n);
    printf("The second largest number is: %d\n", secondLargest);
    return 0;
}
