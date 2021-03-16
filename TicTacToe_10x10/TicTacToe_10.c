#include <stdio.h>
#define WIN 100000
#define LOST -100000
#define SIZE 10
int ifwin(char board[SIZE][SIZE]) {

    int xcounter;
    int ocounter;
    int xmax;
    int omax;

    for (int z = 0; z <= SIZE / 2; z++) {
        for (int x = 0; x <= SIZE / 2; x++) {
            xcounter = 0;
            ocounter = 0;
            omax = 0;
            xmax = 0;
            for (int y = 0; y < SIZE / 2; y++) {
                if (board[x + y][y + z] == 'o') {
                    xcounter = 0;
                    ocounter++;
                    if (omax < ocounter) omax = ocounter;
                } else if (board[x + y][y + z] == 'x') {
                    ocounter = 0;
                    xcounter++;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter = 0;
                    ocounter = 0;
                }
            }
            if (omax > 4) return LOST;
            if (xmax > 4) return WIN;
        }
    }
    for (int z = 0; z <= SIZE / 2; z++) {
        for (int x = 0; x <= SIZE / 2; x++) {
            xcounter = 0;
            ocounter = 0;
            omax = 0;
            xmax = 0;
            for (int y = SIZE - 1; y >= SIZE / 2; y--) {
                if (board[x + 9 - y][y - z] == 'o') {
                    xcounter = 0;
                    ocounter++;
                    if (omax < ocounter) omax = ocounter;
                } else if (board[x + 9 - y][y - z] == 'x') {
                    ocounter = 0;
                    xcounter++;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter = 0;
                    ocounter = 0;
                }
            }
            if (omax > 4) return LOST;
            if (xmax > 4) return WIN;
        }
    }

        for (int x = 0; x < SIZE; x++) {
            xcounter = 0;
            ocounter = 0;
            omax = 0;
            xmax = 0;
            for (int y = 0; y < SIZE; y++) {
                if (board[x][y] == 'o') {
                    ocounter++;
                    xcounter=0;
                    if (omax < ocounter) omax = ocounter;
                } else if (board[x][y] == 'x') {
                    ocounter=0;
                    xcounter++;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter = 0;
                    ocounter = 0;
                }
            }
            if (omax > 4) return LOST;
            if (xmax > 4) return WIN;
        }

        for (int y = 0; y < SIZE; y++) {
            xcounter = 0;
            ocounter = 0;
            omax = 0;
            xmax = 0;
            for (int x = 0; x < SIZE; x++) {
                if (board[x][y] == 'o') {
                    xcounter = 0;
                    ocounter++;
                    if (omax < ocounter) omax = ocounter;
                } else if (board[x][y] == 'x') {
                    ocounter = 0;
                    xcounter++;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter=0;
                    ocounter=0;
                }
            }
            if (omax > 4) return LOST;
            if (xmax > 4) return WIN;
        }

    return 0;
}

int check(char board[SIZE][SIZE]) {

    int values = 5;
    int values5 = values * values * values * values * values - 1;
    int xcounter;
    int ocounter;
    int xmax;
    int omax;
    int xglobMax = 0;
    int oglobMax = 0;
    int sw; // if full col or row

    // finding xs and os diagonaly right
    for (int z = 0; z <= SIZE / 2; z++) {
        for (int x = 0; x <= SIZE / 2; x++) {
            xcounter = 1;
            ocounter = -1;
            omax = 0;
            xmax = 0;
            for (int y = 0; y < SIZE / 2; y++) {
                if (board[x + y][y + z] == 'o') {
                    xcounter = 1;
                    ocounter *= values;
                    if (omax > ocounter) omax = ocounter;
                } else if (board[x + y][y + z] == 'x') {
                    ocounter = -1;
                    xcounter *= values;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter = 1;
                    ocounter = -1;
                }
            }
            if (omax < -values5) return LOST;
            if (xmax > values5) return WIN;

            if (xmax > xglobMax) {
                xglobMax = xmax;
            }
            if (omax < oglobMax) {
                oglobMax = omax;
            }
        }
    }
    // finding xs and os diagonaly left
    for (int z = 0; z <= SIZE / 2; z++) {
        for (int x = 0; x <= SIZE / 2; x++) {
            xcounter = 1;
            ocounter = -1;
            omax = 0;
            xmax = 0;
            for (int y = SIZE - 1; y >= SIZE / 2; y--) {
                if (board[x + 9 - y][y - z] == 'o') {
                    xcounter = 1;
                    ocounter *= values;
                    if (omax > ocounter) omax = ocounter;
                } else if (board[x + 9 - y][y - z] == 'x') {
                    ocounter = -1;
                    xcounter *= values;
                    if (xmax < xcounter) xmax = xcounter;
                } else {
                    xcounter = 1;
                    ocounter = -1;
                }
            }
            if (omax < -values5) return LOST;
            if (xmax > values5) return WIN;

            if (xmax > xglobMax) {
                xglobMax = xmax;
            }
            if (omax < oglobMax) {
                oglobMax = omax;
            }
        }
    }

    // Finding xs and os in a row
    for (int x = 0; x < SIZE; x++) {
        xcounter = 1;
        ocounter = -1;
        omax = 0;
        xmax = 0;
        sw = 1;
        for (int y = 0; y < SIZE; y++) {
            if (board[x][y] == 'o') {
                ocounter *= values;
                xcounter = 1;
                if (omax > ocounter) omax = ocounter;
            } else if (board[x][y] == 'x') {
                ocounter = -1;
                xcounter *= values;
                if (xmax < xcounter) xmax = xcounter;
            } else {
                xcounter = 1;
                ocounter = -1;
                sw = 1;
            }
            if (omax < -values5) return LOST;
            if (xmax > values5) return WIN;
            if (sw) xmax = omax = 0;
        }

        if (xmax > xglobMax) {
            xglobMax = xmax;
        }
        if (omax < oglobMax) {
            oglobMax = omax;
        }
    }

    // Finding xs and os in a col

    for (int y = 0; y < SIZE; y++) {
        xcounter = 1;
        ocounter = -1;
        omax = 0;
        xmax = 0;
        sw = 1;
        for (int x = 0; x < SIZE; x++) {
            if (board[x][y] == 'o') {
                xcounter = 1;
                ocounter *= values;
                if (omax > ocounter) omax = ocounter;
            } else if (board[x][y] == 'x') {
                ocounter = -1;
                xcounter *= values;
                if (xmax < xcounter) xmax = xcounter;
            } else {
                xcounter = 1;
                ocounter = -1;
            }
            if (omax < -values5) return LOST;
            if (xmax > values5) return WIN;
            if (sw) xmax = omax = 0;
        }

        if (xmax > xglobMax) {
            xglobMax = xmax;
        }
        if (omax < oglobMax) {
            oglobMax = omax;
        }
    }
    return (xglobMax + oglobMax);
}
// return 0 if nothing nearby
// return 1 if somthing nearby
int nearby(char b[SIZE][SIZE], int px, int py){
    for(int x = px - 1; x <= px+1;x++){
        for(int y = py - 1;y <= py+1;y++ ){
            if(y < 0 || x < 0 || y > 9 || x > 9) continue;
            if(b[x][y] != ' ') return 1;
        }
    }
    return 0;
}
void showBoard(char b[SIZE][SIZE])
{
    printf("   0   1   2   3   4   5   6   7   8   9 \n");
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d ",i);
        for(int j = 0; j < SIZE; j++)
        {
            printf(" %c",b[i][j]);
            if(j != (SIZE - 1)) printf(" |");
        }
        printf("\n");
        if(i != (SIZE - 1)) printf("  ---|---|---|---|---|---|---|---|---|---\n");
    }
    printf("\n");
}

int freeSpaces(char b[SIZE][SIZE])
{
    int freeSpaces = 0;

    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            if(b[i][j] == ' ')
                freeSpaces++;
        }
    }
    return freeSpaces;
}

int bestMove(char board[SIZE][SIZE],int mode, int *x, int *y)
{
    int result, mx, min, px, py, nx, ny, noMoves = 1;
    result = check(board);
    if(mode <= 0 || result == WIN || result == LOST ) return result;
    if(mode%2 == 0)
    {
        for(px = 0, mx = 2 * LOST; px < SIZE; px++)
        {
            for(py = 0; py < SIZE; py++)
            {
                if(board[px][py] == ' ' && nearby(board,px,py))
                {
                    board[px][py] = 'x';
                    result = bestMove(board, mode - 1, &nx, &ny);
                    board[px][py] = ' ';
                    if (result > mx)
                    {
                        mx = result;
                        *x = px;
                        *y = py;
                    }
                    noMoves = 0;
                }
            }
        }
        if(noMoves)
        {
            return 0;
        } else {
            return mx;
        }

    } else {
        for(px = 0, min = 2 * WIN; px < SIZE; px++){
            for(py = 0; py < SIZE; py++)
            {
                if(board[px][py] == ' ' && nearby(board,px,py))
                {
                    board[px][py] = 'o';
                    result = bestMove(board, mode - 1, &nx, &ny);
                    board[px][py] = ' ';

                    if (result < min)
                    {
                        min = result;
                        *x = px;
                        *y = py;
                    }
                    noMoves = 0;
                }
            }
        }

        if(noMoves)
        {
            return 0;
        } else {
            return min;
        }
    }

}

int main()
{
    char board[SIZE][SIZE];
    int x, y, result;

    for (x = 0; x < SIZE; x++)
        for (y = 0; y < SIZE; y++)
            board[x][y] = ' ';
    x = y = 4;

    while (1)
    {
        if (!freeSpaces(board))
        {
            printf("Nobody wins :(");
            return 0;
        }

        bestMove(board,4,&x,&y);


        board[x][y] = 'x';
        showBoard(board);
        result = ifwin(board);

        if (result)
        {
            if(result == WIN) {
                printf("\nX wins !!!");
                return 0;
            }
            if (result == LOST){
                printf("\nO wins!!!");
                return 0;
            }
        }
        do
        {
            printf("Type next correct move[row][col]:\n");
            scanf("%d %d", &x, &y);
        }while(board[x][y]  != ' ');

        board[x][y] = 'o';
        result = ifwin(board);

        if (result)
        {
            showBoard(board);
            if(result == WIN) {
                printf("\nX wins !!!");
                return 0;
            }
            if (result == LOST){
                printf("\nO wins!!!");
                return 0;
            }
        }
    }
}