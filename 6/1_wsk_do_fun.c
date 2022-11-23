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

int main() {
    void (*wsk_do_fun)(int w);

    wsk_do_fun = fun1;
    wsk_do_fun(4);

    wsk_do_fun = fun2;
    wsk_do_fun(5);

    wsk_do_fun = fun3;
    wsk_do_fun(1);
}