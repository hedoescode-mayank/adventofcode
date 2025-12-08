#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_repeated(const char *s) {
    int L = strlen(s);
    if (L <= 1) return 0;

    for (int d = 1; d <= L / 2; ++d) {
        if (L % d != 0) continue;
        int ok = 1;
        for (int i = 0; i < L; ++i) {
            if (s[i] != s[i % d]) {
                ok = 0;
                break;
            }
        }
        if (ok) return 1;
    }
    return 0;
}

int main() {
    FILE *f = fopen("ok.txt", "r");
    if (!f) return 1;

    unsigned long long total = 0ULL;
    char buffer[20000];

    // read entire file as one big line
    while (fgets(buffer, sizeof(buffer), f)) {
        char *tok = strtok(buffer, ",");
        while (tok) {
            // trim spaces
            while (*tok == ' ') tok++;

            unsigned long long a, b;
            if (sscanf(tok, "%llu-%llu", &a, &b) == 2) {
                if (a > b) { unsigned long long t = a; a = b; b = t; }

                for (unsigned long long x = a; x <= b; x++) {
                    char s[32];
                    sprintf(s, "%llu", x);
                    if (is_repeated(s)) {
                        total += x;
                    }
                    if (x == b) break;
                }
            }

            tok = strtok(NULL, ",");
        }
    }

    fclose(f);

    printf("%llu\n", total);
    return 0;
}
