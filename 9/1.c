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

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if(status==-1) {printf("blad bind\n"); return 0;}

    status = listen(gniazdo,10);
    if(status==-1) {printf("blad listen\n"); return 0;}

        dlugosc = sizeof cli;
        printf("Czekam na wiadomosc\n");
        gniazdo2=accept(gniazdo, (struct sockaddr*)&cli,  (socklen_t *) &dlugosc);
        if (gniazdo2==-2) {printf("blad accept\n"); return 0;}

    while (end){
        status = recv(gniazdo2, buf, sizeof(buf), 0); //sprawdzic status
        printf("status z recv %d\n", status);
//        if (status>0) {
//            printf("buf przed zmiana: #%s#\n", buf);
//        buf[status-2] = 0;
        buf[status-1] = 0;
        printf("OTRZYMANO: #%s#\n", buf);

        printf("Podaj wiadomosc do wyslania:\n");
        scanf("%s", buf);
//        fgets(buf, sizeof buf, stdin);

        status = send(gniazdo2, buf, strlen(buf), 0);
        printf("status z send %d\n", status);

//        printf("zamykam gniazdo\n");
//        close(gniazdo2);
    }
    close(gniazdo);
//    close(gniazdo2);


}

