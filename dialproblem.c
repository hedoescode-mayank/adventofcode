#include <stdio.h>
#include <stdlib.h>

int main() {
    char s[50];
    long long count = 0;
    long long pos = 50;    

    while (scanf("%s", s) != EOF) {

        char dir = s[0];
        long long dist = atoll(s + 1);

        if (dir == 'L')
            pos = (pos - dist) % 100;
        else
            pos = (pos + dist) % 100;

        if (pos < 0) pos += 100;

        if (pos == 0)
            count++;
    }

    printf("%lld\n", count);
    return 0;
}
