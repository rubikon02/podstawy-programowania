#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2112
#define IP "127.0.0.23"

int main() {
    printf("Uruchamiam klienta na %s:%d\n", IP, PORT);

    int gniazdo;
    ssize_t status;
    struct sockaddr_in ser;
    char buf[200];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo==-1) { printf("blad socket\n"); return 0; }

    status = connect(gniazdo, (struct sockaddr*)&ser, sizeof ser);
    if (status<0) { printf("blad connect\n"); return 0; }

    while (1) {
        printf("Podaj wiadomosc do wyslania:");
        scanf("%s", buf);
        status = send(gniazdo, buf, strlen(buf), 0);
        if (status < 0) { printf("blad wysylania wiadomosci\n"); return 0; }
        if (strcmp(buf, "Q") == 0) break;

        printf("Czekam na wiadomosc...\n");
        status = recv(gniazdo, buf, (sizeof buf) - 1, 0);
        if (status < 0) { printf("blad otrzymywania wiadomosci\n"); return 0; }
        buf[status]='\0';
        printf ("OTRZYMANO: #%s#\n", buf);
        if (strcmp(buf, "Q") == 0) break;
    }
    printf("Rozlaczam gniazdo\n");
    close(gniazdo);
}
