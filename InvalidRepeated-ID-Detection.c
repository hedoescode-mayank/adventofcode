#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef __int128 i128;

// Print __int128 safely
void print128(i128 x) {
    if (x < 0) { putchar('-'); x = -x; }
    if (x >= 10) print128(x / 10);
    putchar((x % 10) + '0');
}

// Count digits in a large number
int digits(i128 x) {
    int d = 0;
    while (x > 0) { x /= 10; d++; }
    return d == 0 ? 1 : d;
}

// ceil(a / b) for __int128
i128 ceil_div(i128 a, i128 b) {
    return (a + b - 1) / b;
}

// Find all invalid IDs in [A, B]
i128 solve_range(i128 A, i128 B) {
    i128 sum = 0;

    int maxL = digits(B) / 2;

    for (int L = 1; L <= maxL; L++) {
        i128 K = 1;
        for (int i = 0; i < L; i++) K *= 10;

        i128 mult = K + 1;
        i128 fmin = (L == 1) ? 1 : K / 10;
        i128 fmax = K - 1;

        i128 low = ceil_div(A, mult);
        i128 high = B / mult;

        i128 left = (low > fmin) ? low : fmin;
        i128 right = (high < fmax) ? high : fmax;

        for (i128 first = left; first <= right; first++) {
            i128 num = first * mult;
            if (num >= A && num <= B) sum += num;
        }
    }

    return sum;
}
//
int main() {
    FILE *fp = fopen("ir.txt", "r");
    if (!fp) {
        printf("Error: Cannot open ir.txt\n");
        return 1;
    }

    char line[30000];
    fgets(line, sizeof(line), fp);
    fclose(fp);

    i128 total = 0;

    char *p = strtok(line, ",");
    while (p) {
        char *dash = strchr(p, '-');
        if (!dash) { p = strtok(NULL, ","); continue; }

        *dash = '\0';

        i128 A = atoll(p);
        i128 B = atoll(dash + 1);

        total += solve_range(A, B);

        p = strtok(NULL, ",");
    }

    printf("Final Sum = ");
    print128(total);
    printf("\n");

    return 0;
}
