#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#include "Chess.c"

void sendBoard(int board[8][8], char buf[1024]) {
    char figures[] = {'K', 'Q', 'R', 'B', 'S', 'P', 'k', 'q', 'r', 'b', 's', 'p', ' '};
    sprintf(buf, "");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sprintf(buf + strlen(buf), "%c:", figures[board[i][j]]);
        }
    }
}


int main(void) {
    int status, dlugosc;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[1024];
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }

    int board[8][8] = {{2,  4,  3,  1,  0,  3,  4,  2},
                       {5,  5,  5,  5,  5,  5,  5,  5},
                       {12, 12, 12, 12, 12, 12, 12, 12},
                       {12, 12, 12, 12, 12, 12, 12, 12},
                       {12, 12, 12, 12, 12, 12, 12, 12},
                       {12, 12, 12, 12, 12, 12, 12, 12},
                       {11, 11, 11, 11, 11, 11, 11, 11},
                       {8,  10, 9,  7,  6,  9,  10, 8}};
    int x, y, direction, distance, playerX, playerDX;
    char playerY, playerDY;

    while (1) {
        //        Send board
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1) {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9001);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        bestMove(board, 4, &x, &y, &direction, &distance);
        moveAI(board, x, y, direction, distance);
        printf("AI move:\n");
        showBoard(board);
        sendBoard(board, buf);
        switch (ifwin(board)) {
            case 1:
                sprintf(buf, "You won!");
                return 0;
            case 2:
                sprintf(buf, "Computer won :(");
                return 0;
        }
        status = connect(gniazdo, (struct sockaddr *) &srv, sizeof srv);
        if (status < 0) {
            printf("Connect error!\n");
            return 0;
        }

        send(gniazdo, buf, strlen(buf), 0);
        closesocket(gniazdo);


        // Receive move
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1) {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        status = bind(gniazdo, (struct sockaddr *) &srv, sizeof srv);
        if (status == -1) {
            printf("Bind error!\n");
            return 0;
        }

        status = listen(gniazdo, 10);
        if (status == -1) {
            printf("Listen error\n");
            return 0;
        }

        dlugosc = sizeof cli;
        gniazdo2 = accept(gniazdo, (struct sockaddr *) &cli, (int *) &dlugosc);
        if (gniazdo2 == -1) {
            printf("Accept error!\n");
            return 0;
        }

        status = recv(gniazdo2, buf, sizeof buf, 0);
        buf[status] = '\0';
        printf("Move: %s", buf);
        sscanf(buf, "%d%c%d%c", &playerX, &playerY, &playerDX, &playerDY);
        move(board, playerX, playerY, playerDX, playerDY);
        showBoard(board);
        switch (ifwin(board)) {
            case 1:
                printf("You won!");
                return 0;
            case 2:
                printf("Computer won :(");
                return 0;
        }

        closesocket(gniazdo2);
        closesocket(gniazdo);

    }
}