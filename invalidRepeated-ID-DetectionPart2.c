// sum_repeated_ids.c
// Compile: gcc -O2 sum_repeated_ids.c -o sum_repeated_ids
// Run: ./sum_repeated_ids < input.txt
//part 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

int is_repeated(const char *s) {
    int L = strlen(s);
    if (L <= 1) return 0; // single-digit can't be repeated >=2 times
    // try all block lengths d that divide L and are < L
    for (int d = 1; d <= L/2; ++d) {
        if (L % d != 0) continue;
        int k = L / d; // number of repeats, must be >=2 by construction
        int ok = 1;
        for (int i = 0; i < L; ++i) {
            if (s[i] != s[i % d]) { ok = 0; break; }
        }
        if (ok) return 1;
    }
    return 0;
}

int main(void) {
    unsigned long long total = 0ULL;
    char line[256];

    while (fgets(line, sizeof(line), stdin)) {
        // trim leading spaces
        char *p = line;
        while (*p && isspace((unsigned char)*p)) ++p;
        if (*p == '\0' || *p == '\n' || *p == '#') continue;
        unsigned long long a=0, b=0;
        if (sscanf(p, "%llu-%llu", &a, &b) != 2) {
            // try if separated by space
            if (sscanf(p, "%llu %llu", &a, &b) != 2) continue;
        }
        if (a > b) { unsigned long long tmp = a; a = b; b = tmp; }

        // iterate from a to b inclusive
        for (unsigned long long x = a; x <= b; ++x) {
            // convert to string
            char s[32];
            sprintf(s, "%llu", x);
            if (is_repeated(s)) total += x;
            // careful with possible infinite loops on extremely large ranges:
            if (x == ULLONG_MAX) break; // guard (practically won't occur)
        }
    }

    printf("%llu\n", total);
    return 0;
}
