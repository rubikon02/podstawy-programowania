#include <stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 2114
#define IP "127.0.0.23"

int main() {
    printf("Podlaczam sie do serwera %s:%d\n", IP, PORT);

    int gniazdo;
    ssize_t status;
    struct sockaddr_in ser;
    char buf[1024];
    char fileName[1024];

    ser.sin_family = AF_INET;
    ser.sin_port = htons(PORT);
    ser.sin_addr.s_addr = inet_addr(IP);

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1) {
        printf("blad socket\n");
        return 0;
    }

    status = connect(gniazdo, (struct sockaddr *) &ser, sizeof ser);
    if (status < 0) {
        printf("Nie znaleziono takiego serwera\n");
        return 0;
    }
    printf("Polaczono z serwerem\n");

    while (1) {
        printf("Podaj nazwe pliku ktory chcesz otrzymac:");
        scanf("%s", buf);
        strcpy(fileName, buf);
        status = send(gniazdo, buf, strlen(buf), 0);
        if (status < 0) {
            printf("blad wysylania wiadomosci\n");
            return 0;
        }
        if (strcmp(buf, "Q") == 0) break;

        printf("Czekam na plik...\n");
        status = recv(gniazdo, buf, (sizeof buf) - 1, 0);
        if (status < 0) {
            printf("blad otrzymywania wiadomosci\n");
            return 0;
        }
        buf[status] = '\0';
        if (strcmp(buf, "Q") == 0) break;
//        if (strcmp(buf))
        printf("----- Otrzymano plik -----\n");
        printf("%s\n", buf);
        printf("------ Koniec pliku ------\n");
        FILE *file = fopen(fileName, "w");
        size_t savedBytes = fwrite(buf, 1, status, file);
        fclose(file);
        printf("Zapisano %zu znaków do pliku %s\n", savedBytes, fileName);

    }
    printf("Rozlaczam gniazdo\n");
    close(gniazdo);
}
