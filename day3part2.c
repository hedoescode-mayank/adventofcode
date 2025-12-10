#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096   // max characters per line
#define PICK 12         // number of digits to select per bank (Part 2)

int main(void) {
    FILE *fp = fopen("jk.txt", "r");  // your puzzle input file
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    char line[MAX_LINE];
    unsigned long long total_joltage = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_number++;

        // Strip newline(s)
        size_t len = strcspn(line, "\r\n");
        line[len] = '\0';

        // Extract only digits into a separate buffer
        char digits[MAX_LINE];
        int dlen = 0;
        for (size_t i = 0; i < len; i++) {
            if (isdigit((unsigned char)line[i])) {
                digits[dlen++] = line[i];
            }
        }

        if (dlen == 0) {
            // no digits on this line
            continue;
        }

        if (dlen < PICK) {
            fprintf(stderr,
                    "Warning: line %d has only %d digits (need at least %d), skipping.\n",
                    line_number, dlen, PICK);
            continue;
        }

        int to_remove = dlen - PICK;   // how many digits we must remove
        char stack[MAX_LINE];
        int top = 0; // size of stack

        // Monotone stack to build max subsequence of length PICK
        for (int i = 0; i < dlen; i++) {
            char c = digits[i];

            while (top > 0 && to_remove > 0 && stack[top - 1] < c) {
                top--;      // pop smaller digit
                to_remove--; 
            }

            stack[top++] = c; // push current digit
        }

        // If we still must remove digits, remove from the end
        while (to_remove > 0 && top > 0) {
            top--;
            to_remove--;
        }

        // Now 'top' should be at least PICK; keep the first PICK digits
        if (top < PICK) {
            fprintf(stderr,
                    "Unexpected: line %d ended with only %d digits in stack, skipping.\n",
                    line_number, top);
            continue;
        }

        // Convert first PICK digits of stack to number
        unsigned long long value = 0;
        for (int i = 0; i < PICK; i++) {
            value = value * 10ULL + (unsigned long long)(stack[i] - '0');
        }

        total_joltage += value;
    }

    fclose(fp);

    printf("Total output joltage (Part 2): %llu\n", total_joltage);

    return 0;
}
