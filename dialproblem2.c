#include <stdio.h>
#include <stdlib.h>

int main() {
    char s[50];
    long long count = 0;
    long long pos = 50;  // starting position

    while (scanf("%s", s) != EOF) {

        char dir = s[0];
        long long dist = atoll(s + 1);

        if (dir == 'L') {

            long long full = dist / 100;  
            count += full;               // full cycles hit 0 exactly 'full' times

            long long steps = dist % 100;

            for (long long i = 0; i < steps; i++) {
                pos--;
                if (pos < 0) pos = 99;
                if (pos == 0) count++;
            }
        }

        else if (dir == 'R') {

            long long full = dist / 100;
            count += full;

            long long steps = dist % 100;

            for (long long i = 0; i < steps; i++) {
                pos++;
                if (pos >= 100) pos = 0;
                if (pos == 0) count++;
            }
        }
    }

    printf("%lld\n", count);
    return 0;
}
