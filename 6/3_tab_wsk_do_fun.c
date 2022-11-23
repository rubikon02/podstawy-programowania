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
    void (*fun[100])(int);
    for (int i = 0; i < 100; i++) {
        switch (i % 3) {
            case 0: fun[i] = fun1; break;
            case 1: fun[i] = fun2; break;
            case 2: fun[i] = fun3; break;
        }
    }
    for (int i = 0; i < 100; i++) {
        fun[i](i % 20);
    }
}
