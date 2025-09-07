#include <stdio.h>

int main() {
    int n = 2, r, found = 0; // n >= 2 as per problem statement(are drawn twice)
    do {
        for (r = 1; r <= n; r++) {
            if ((n * (n - 1)) == 2 * (r * (r - 1))) {
                printf("n: %d, r: %d\n", n, r);
                if ((n - r) % 2 == 0) {
                    found = 1;
                    break;
                }
            }
        }
        n ++;
    } while (!found);
    return 0;
}