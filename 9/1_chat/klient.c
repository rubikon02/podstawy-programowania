#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2112
#define IP "127.0.0.23"

int main() {
    printf("Uruchamiam klienta i nawiązuję połączenie z %s:%d\n", IP, PORT);

    int gniazdo;
    ssize_t status;
    struct sockaddr_in ser;
    char buf[200];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("Błąd socket\n");
        return 0;
    }

    status = connect(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status < 0) {
        printf("Błąd connect\n");
        return 0;
    }

    printf("Podłączono do serwera\n");

    while (1) {
        printf("Podaj wiadomosć do wysłania:");
        scanf("%s", buf);
        status = send(gniazdo, buf, strlen(buf), 0);
        if (status <= 0) {
            printf("Błąd wysyłania wiadomosci\n");
            return 0;
        }
        if (strcmp(buf, "Q") == 0) break;

        printf("Czekam na wiadomosc...\n");
        status = recv(gniazdo, buf, (sizeof buf) - 1, 0);
        if (status <= 0) {
            printf("Błąd otrzymywania wiadomości\n");
            return 0;
        }
        buf[status] = '\0';
        printf("OTRZYMANO: #%s#\n", buf);
        if (strcmp(buf, "Q") == 0) break;
    }
    printf("Rozłączam gniazdo\n");
    close(gniazdo);
}
