#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2115
#define IP "127.0.0.23"

int main() {
    printf("Uruchamiam serwer na %s:%d\n", IP, PORT);

    struct sockaddr_in ser,cli;
    int gniazdo, gniazdo2, dlugosc = sizeof cli;
    ssize_t status;
    char buf[1024];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) { printf("blad socket\n"); return 0; }

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status == -1) { printf("Nie mozna przypisac portu %d\n", PORT); return 0; }

    status = listen(gniazdo,10);
    if (status == -1) { printf("blad listen\n"); return 0; }

    printf("Oczekuje na polaczenie...\n");
    gniazdo2 = accept(gniazdo, (struct sockaddr*) &cli, (socklen_t *) &dlugosc);
    if (gniazdo2 == -2) { printf("blad accept\n"); return 0; }
    printf("Klient podlaczyl sie\n");

    while (1){
        printf("Czekam na wiadomosc...\n");
        status = recv(gniazdo2, buf, sizeof(buf) - 1, 0);
        if (status < 0) { printf("blad otrzymywania wiadomosci\n"); return 0; }
        buf[status] = '\0';
        printf("OTRZYMANO: #%s#\n", buf);
        if (strcmp(buf, "Q") == 0) break;

        printf("Odczytuje plik %s:\n", buf);
        FILE *file = fopen(buf, "r");
        if (!file) {
            printf("Nie ma takiego pliku\n");
            strcpy(buf, "Nie ma takiego pliku");
        } else {
            size_t recivedBytes = fread(buf, 1, sizeof buf - 1, file);
            buf[recivedBytes] = '\0';
            printf("%s\n", buf);
            printf("Wysylam plik\n");
        }
        status = send(gniazdo2, buf, strlen(buf), 0);
        if (status < 0) { printf("blad wysylania wiadomosci\n"); return 0; }
    }
    printf("Rozlaczam gniazda\n");
    close(gniazdo);
    close(gniazdo2);
}

