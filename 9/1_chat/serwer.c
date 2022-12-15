#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2112
#define IP "127.0.0.23"

int main() {
    printf("Uruchamiam serwer na %s:%d\n", IP, PORT);

    struct sockaddr_in ser,cli;
    int gniazdo, gniazdo2, dlugosc = sizeof cli;
    ssize_t status;
    char buf[200];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) { printf("blad socket\n"); return 0; }

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status == -1) { printf("blad bind\n"); return 0; }

    status = listen(gniazdo,10);
    if (status == -1) { printf("blad listen\n"); return 0; }

    printf("Oczekuje na polaczenie...\n");
    gniazdo2 = accept(gniazdo, (struct sockaddr*) &cli, (socklen_t *) &dlugosc);
    if (gniazdo2 == -2) { printf("blad accept\n"); return 0; }

    while (1){
        printf("Czekam na wiadomosc...\n");
        status = recv(gniazdo2, buf, sizeof(buf) - 1, 0);
        if (status < 0) { printf("blad otrzymywania wiadomosci\n"); return 0; }
        buf[status] = '\0';
        printf("OTRZYMANO: #%s#\n", buf);
        if (strcmp(buf, "Q") == 0) break;

        printf("Podaj wiadomosc do wyslania:");
        scanf("%s", buf);
        status = send(gniazdo2, buf, strlen(buf), 0);
        if (status < 0) { printf("blad wysylania wiadomosci\n"); return 0; }
        if (strcmp(buf, "Q") == 0) break;
    }
    printf("Rozlaczam gniazda\n");
    close(gniazdo);
    close(gniazdo2);
}

