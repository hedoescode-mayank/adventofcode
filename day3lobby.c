#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024  // maximum length of a line in the file

int main(void) {
    FILE *fp = fopen("jk.txt", "r");  // change the file name
    if (fp == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    char line[MAX_LINE];
    long long total_joltage = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_number++;

        // Remove newline characters (\n or \r\n)
        size_t len = strcspn(line, "\r\n");
        line[len] = '\0';

        if (len == 0) {
            // Empty line, skip
            continue;
        }

        int max_two_digit = -1;

        // Find the maximum two-digit number from digits in order
        for (size_t i = 0; i < len; i++) {
            if (!isdigit((unsigned char)line[i])) {
                continue; // skip non-digit characters, just in case
            }
            int d1 = line[i] - '0';

            for (size_t j = i + 1; j < len; j++) {
                if (!isdigit((unsigned char)line[j])) {
                    continue;
                }
                int d2 = line[j] - '0';

                int val = d1 * 10 + d2;  // form the two-digit number

                if (val > max_two_digit) {
                    max_two_digit = val;
                }
            }
        }

        if (max_two_digit < 0) {
            fprintf(stderr,
                    "Warning: line %d does not contain at least two digits, skipping.\n",
                    line_number);
            continue;
        }

        // Add to the total joltage
        total_joltage += max_two_digit;
    }

    fclose(fp);

    printf("Total output joltage: %lld\n", total_joltage);

    return 0;
}
