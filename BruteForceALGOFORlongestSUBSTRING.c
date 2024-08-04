#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to check if all characters in a substring are unique
bool areAllCharactersUnique(char* s, int start, int end) {
    bool charSet[128] = { false };  // Assuming ASCII characters

    for (int i = start; i <= end; i++) {
        if (charSet[(int)s[i]]) {
            return false;  // Character already seen in this substring
        }
        charSet[(int)s[i]] = true;
    }

    return true;
}

// Function to find the length of the longest substring without repeating characters
int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    int maxLength = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (areAllCharactersUnique(s, i, j)) {
                int currentLength = j - i + 1;
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                }
            }
        }
    }

    return maxLength;
}

int main() {
    char s[] = "abcabcbb";
    int result = lengthOfLongestSubstring(s);
    printf("The length of the longest substring without repeating characters is: %d\n", result);
    return 0;
}
