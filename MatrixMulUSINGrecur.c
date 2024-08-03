#include <stdio.h>
#define N 3

void multiplyRecursive(int A[N][N], int B[N][N], int C[N][N], int i, int j, int k) {
    // Base case: If we have traversed all elements of result matrix
    if (i >= N)
        return;

    // If we have reached the end of row, go to the next row
    if (j >= N)
        multiplyRecursive(A, B, C, i + 1, 0, 0);

    // If we have reached the end of column, go to the next column
    if (k >= N)
        multiplyRecursive(A, B, C, i, j + 1, 0);

    // Calculate value for C[i][j]
    C[i][j] += A[i][k] * B[k][j];

    // Go to the next element in the current row
    multiplyRecursive(A, B, C, i, j, k + 1);
}

void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N]) {
    // Initialize the result matrix to zero
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i][j] = 0;

    // Call recursive function
    multiplyRecursive(A, B, C, 0, 0, 0);
}

void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int C[N][N]; // Result matrix

    multiplyMatrices(A, B, C);

    printf("Result matrix is:\n");
    printMatrix(C);

    return 0;
}
a