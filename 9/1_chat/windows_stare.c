#include <winsock2.h>
#include <stdio.h>
#include<stdio.h>
//#include<arpa/inet.h>
#include<string.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

int main() {
    WSADATA wsaData;
    if (WSAStartup( MAKEWORD( 2, 0 ), &wsaData )){
        return 0;/*blad*/
    }

    int status, dlugosc, nr=0, end=1;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in ser,cli;
    char buf[200];
    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo==-1) {printf("blad socket\n"); return 0;}

    ser.sin_family = AF_INET;
    ser.sin_port = htons(23);
//    ser.sin_addr.s_addr = inet_addr("127.0.0.23");
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if(status==-1) {printf("blad bind\n"); return 0;}

    status = listen(gniazdo,10);
    if(status==-1) {printf("blad listen\n"); return 0;}

    while (end){
        dlugosc = sizeof cli;
        printf("Czekam na wiadomosc\n");
        gniazdo2=accept(gniazdo, (struct sockaddr*)&cli, &dlugosc);
        fflush(stdin);
        if (gniazdo2==-2) {printf("blad accept\n"); return 0;}
        status = recv(gniazdo2, buf, sizeof(buf), 0); //sprawdzic status
//        if (status>0) {
//            printf("buf przed zmiana: #%s#\n", buf);
//            buf[status-2] = 0;
        printf("OTRZYMANO: #%s#\n", buf);

//        printf("Podaj wiadomosc do wyslania:\n");
//        fgets(buf, sizeof buf, stdin);
//
//        status = send(gniazdo2, buf, strlen(buf), 0);
//            if (buf[0]=='Q') {sprintf(buf, "OK, SERWER KONCZY PRACE");
//                end=0;}
//            else if (buf[0]=='N') sprintf(buf, "Jestes klientem nr %d", nr++);
//            else sprintf(buf, "Nie rozuniem pytania");
//            status = send(gniazdo2, buf, strlen(buf), 0); //sprawdzic status
//        }
        closesocket(gniazdo2);
    }
    closesocket(gniazdo);
    closesocket(gniazdo2);

    WSACleanup();

}

