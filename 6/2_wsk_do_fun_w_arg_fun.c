#include <stdio.h>

void fun1(int w) {
    printf("Jestem funkcja 1 z parametrem %d\n", w);
}

void fun2(int w) {
    printf("Jestem funkcja 2 z parametrem %d\n", w);
}

void fun3(int w) {
    printf("Jestem funkcja 3 z parametrem %d\n", w);
}

double ff(void (*wsk)(int w), int a) {
    wsk(a);
}

int main() {
    ff(fun1, 8);
    ff(fun2, 33);
    ff(fun3, 22);
}
