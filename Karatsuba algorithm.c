#include <stdio.h>
#include <stdlib.h>

// Function to find the length of the number
int getLength(long long num) {
    int len = 0;
    while (num != 0) {
        len++;
        num /= 10;
    }
    return len;
}

// Function to calculate power of 10
long long power(int x) {
    long long result = 1;
    while (x > 0) {
        result *= 10;
        x--;
    }
    return result;
}

// Function to multiply two numbers using the Karatsuba algorithm
long long karatsuba(long long x, long long y) {
    // Base case for recursion
    if (x < 10 || y < 10) {
        return x * y;
    }
    
    // Find the length of the numbers
    int lenX = getLength(x);
    int lenY = getLength(y);
    int n = (lenX > lenY) ? lenX : lenY;
    int halfN = (n + 1) / 2;

    // Split the digit sequences in the middle
    long long power10 = power(halfN);
    long long xHigh = x / power10;
    long long xLow = x % power10;
    long long yHigh = y / power10;
    long long yLow = y % power10;

    // Perform three multiplications
    long long z0 = karatsuba(xLow, yLow);
    long long z1 = karatsuba(xLow + xHigh, yLow + yHigh);
    long long z2 = karatsuba(xHigh, yHigh);

    // Combine the results
    return (z2 * power(2 * halfN)) + ((z1 - z2 - z0) * power(halfN)) + z0;
}

int main() {
    long long x = 3141592653589793238LL;  // Use LL suffix for long long literals
    long long y = 2718281828459045235LL;  // Use LL suffix for long long literals
    
    long long result = karatsuba(x, y);
    printf("Result: %lld\n", result);  // Use %lld for long long
    
    return 0;
}
