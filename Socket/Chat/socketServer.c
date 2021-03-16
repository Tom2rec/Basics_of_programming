#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

int main(void)
{
    int status, dlugosc;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[200];
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }

    while (1)
    {
//        Reciever
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        status = bind(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status == -1)
        {
            printf("Bind error!\n");
            return 0;
        }

        status = listen(gniazdo, 10);
        if (status == -1)
        {
            printf("Listen error\n");
            return 0;
        }

        dlugosc = sizeof cli;
        gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (int *)&dlugosc);
        if (gniazdo2 == -1)
        {
            printf("Accept error!\n");
            return 0;
        }
        status = recv(gniazdo2, buf, sizeof buf, 0);
        buf[status] = '\0';
        printf("Message: %s", buf);
        closesocket(gniazdo2);
        closesocket(gniazdo);

//        Sender
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9001);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        printf("Podaj tekst: ");
        fgets(buf, sizeof buf, stdin);

        status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status < 0)
        {
            printf("Connect error!\n");
            return 0;
        }

        send(gniazdo, buf, strlen(buf), 0);
        closesocket(gniazdo);
    }
    }