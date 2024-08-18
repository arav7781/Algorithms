#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 1
#define MISMATCH -1
#define GAP -2

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    else if (b >= a && b >= c) return b;
    else return c;
}

void print_alignment(char *seq1, char *seq2, int **dp, int m, int n) {
    int i = m, j = n;
    char aligned_seq1[100], aligned_seq2[100];
    int index = 0;

    while (i > 0 && j > 0) {
        if (seq1[i-1] == seq2[j-1]) {
            aligned_seq1[index] = seq1[i-1];
            aligned_seq2[index] = seq2[j-1];
            i--; j--;
        } else if (dp[i-1][j-1] + MISMATCH == dp[i][j]) {
            aligned_seq1[index] = seq1[i-1];
            aligned_seq2[index] = seq2[j-1];
            i--; j--;
        } else if (dp[i-1][j] + GAP == dp[i][j]) {
            aligned_seq1[index] = seq1[i-1];
            aligned_seq2[index] = '-';
            i--;
        } else {
            aligned_seq1[index] = '-';
            aligned_seq2[index] = seq2[j-1];
            j--;
        }
        index++;
    }

    while (i > 0) {
        aligned_seq1[index] = seq1[i-1];
        aligned_seq2[index] = '-';
        i--; index++;
    }

    while (j > 0) {
        aligned_seq1[index] = '-';
        aligned_seq2[index] = seq2[j-1];
        j--; index++;
    }

    aligned_seq1[index] = '\0';
    aligned_seq2[index] = '\0';

    printf("Aligned Sequence 1: ");
    for (int k = index - 1; k >= 0; k--) printf("%c", aligned_seq1[k]);
    printf("\nAligned Sequence 2: ");
    for (int k = index - 1; k >= 0; k--) printf("%c", aligned_seq2[k]);
    printf("\n");
}

int** create_matrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void free_matrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void needleman_wunsch(char *seq1, char *seq2) {
    int m = strlen(seq1);
    int n = strlen(seq2);

    int **dp = create_matrix(m + 1, n + 1);

    for (int i = 0; i <= m; i++) dp[i][0] = i * GAP;
    for (int j = 0; j <= n; j++) dp[0][j] = j * GAP;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int match_mismatch = (seq1[i-1] == seq2[j-1]) ? MATCH : MISMATCH;
            dp[i][j] = max(dp[i-1][j-1] + match_mismatch,
                           dp[i-1][j] + GAP,
                           dp[i][j-1] + GAP);
        }
    }

    printf("Optimal Alignment Score: %d\n", dp[m][n]);

    print_alignment(seq1, seq2, dp, m, n);

    free_matrix(dp, m + 1);
}

int main() {
    char seq1[] = "ACGTAG";
    char seq2[] = "ACGTCG";

    needleman_wunsch(seq1, seq2);

    return 0;
}
