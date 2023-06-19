#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in serv_addr;
    char buffer[1024];
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket() error");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Ошибка подключения");
        exit(1);
    }
    while (1) {
        int str_len = read(sock, buffer, 1024);
        buffer[str_len] = '\0';
        if (strcmp(buffer, "The End") == 0) {
            break;
        }
        printf("Второй клиент получил сообщение: %s\n", buffer);
    }
    close(sock);
    return 0;
}