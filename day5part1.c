#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_RANGES 10000
#define MAX_LINE   256

typedef struct {
    long long start;
    long long end;
} Range;

int main(void) {
    FILE *fp = fopen("input.txt", "r");   // your puzzle input
    if (!fp) {
        perror("Error opening input.txt");
        return 1;
    }

    char line[MAX_LINE];

    Range ranges[MAX_RANGES];
    int range_count = 0;

    // ---------- READ RANGES (until blank line) ----------
    while (fgets(line, sizeof(line), fp)) {
        // strip newline
        size_t len = strcspn(line, "\r\n");
        line[len] = '\0';

        // blank line -> end of ranges section
        if (len == 0) {
            break;
        }

        if (range_count >= MAX_RANGES) {
            fprintf(stderr, "Too many ranges, increase MAX_RANGES.\n");
            return 1;
        }

        long long a, b;
        if (sscanf(line, "%lld-%lld", &a, &b) != 2) {
            fprintf(stderr, "Invalid range line: '%s'\n", line);
            return 1;
        }

        if (a > b) { // just in case, swap
            long long tmp = a;
            a = b;
            b = tmp;
        }

        ranges[range_count].start = a;
        ranges[range_count].end   = b;
        range_count++;
    }

    long long fresh_count = 0;

    // ---------- READ IDS (after blank line) ----------
    while (fgets(line, sizeof(line), fp)) {
        // strip newline
        size_t len = strcspn(line, "\r\n");
        line[len] = '\0';

        if (len == 0)
            continue; // skip accidental empty lines

        long long id;
        if (sscanf(line, "%lld", &id) != 1) {
            fprintf(stderr, "Invalid ID line: '%s'\n", line);
            continue;
        }

        int is_fresh = 0;
        for (int i = 0; i < range_count; i++) {
            if (id >= ranges[i].start && id <= ranges[i].end) {
                is_fresh = 1;
                break;
            }
        }

        if (is_fresh) {
            fresh_count++;
        }
    }

    fclose(fp);

    printf("Number of fresh ingredient IDs: %lld\n", fresh_count);
    return 0;
}
