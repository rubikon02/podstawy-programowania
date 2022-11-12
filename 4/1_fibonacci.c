#include <stdio.h>

int fib(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    return fib(n - 1) + fib(n - 2);
}

int fib2(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    int tmp, a = 1, b = 2;
    for (int i = 0; i < n - 2; i++) {
        tmp = a;
        a = b;
        b += tmp;
    }
    return b;
}

int main(void) {
    int n;
    scanf("%d", &n);
    printf("%d element ciagu to %d\n", n, fib2(n));
}