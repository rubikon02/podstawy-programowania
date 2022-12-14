#include <stdio.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>


int main() {

    int status, dlugosc, nr=0, end=1;
    int gniazdo, gniazdo2;
    struct sockaddr_in ser,cli;
    char buf[200];
    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo==-1) {printf("blad socket\n"); return 0;}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(2112);
    ser.sin_addr.s_addr = inet_addr("127.0.0.23");

    status = connect(gniazdo, (struct sockaddr*)&ser, sizeof ser);
    if (status<0) {printf("blad connect\n"); return 0;}
    while (end) {
        printf("Podaj tekst:");
        fgets(buf,sizeof buf, stdin);

        status = send(gniazdo, buf, strlen(buf), 0);
        printf("status z send %d\n", status);

        status = recv(gniazdo, buf, (sizeof buf) -1, 0);
        printf("status z recv %d\n", status);

        buf[status]='\0';
        printf ("Otrzymalem: %s\n",buf);

    }
    close(gniazdo);
}
