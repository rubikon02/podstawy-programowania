#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2114
#define IP "127.0.0.23"

int main() {
    printf("Uruchamiam serwer na %s:%d\n", IP, PORT);

    struct sockaddr_in ser, cli;
    int gniazdo, gniazdo2, dlugosc = sizeof cli;
    ssize_t status;
    char buf[1024];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("Błąd socket\n");
        return 0;
    }

    status = bind(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status == -1) {
        printf("Nie można przypisać portu %d\n", PORT);
        return 0;
    }

    status = listen(gniazdo, 10);
    if (status == -1) {
        printf("Błąd listen\n");
        return 0;
    }

    printf("Oczekuję na połączenie...\n");
    while ((gniazdo2 = accept(gniazdo, (struct sockaddr *) &cli, (socklen_t *) &dlugosc)) >= 0) {
        if (gniazdo2 == -2) {
            printf("Błąd accept\n");
            return 0;
        }
        printf("Nowy klient podłączył się\n");

        while (1) {
            printf("Czekam na wiadomość...\n");
            status = recv(gniazdo2, buf, sizeof(buf) - 1, 0);
            if (status <= 0) {
                printf("Błąd otrzymywania wiadomości\n");
                break;
            }
            buf[status] = '\0';
            printf("OTRZYMANO: #%s#\n", buf);
            if (strcmp(buf, "Q") == 0) break;

            printf("Odczytuję plik %s:\n", buf);
            FILE *file = fopen(buf, "r");
            if (!file) {
                printf("Nie ma takiego pliku\n");
                strcpy(buf, "Nie ma takiego pliku");
            } else {
                size_t recivedBytes = fread(buf, 1, sizeof buf - 1, file);
                fclose(file);
                buf[recivedBytes] = '\0';
                printf("%s\n", buf);
                printf("Wysyłam plik\n");
            }
            status = send(gniazdo2, buf, strlen(buf), 0);
            if (status <= 0) {
                printf("Błąd wysyłania wiadomości\n");
                break;
            }
        }
        printf("Klient rozłączył się\n");
        close(gniazdo2);
        printf("Oczekuję na połączenie...\n");
    }
    printf("Rozłączam gniazdo główne\n");
    close(gniazdo);
}

