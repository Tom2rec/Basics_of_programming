#include <stdio.h>
#include "heuristics.c"
#define LOST -100000
#define WIN 100000
#define EMPTY 12
int MAX_DIRECTION[13]={8,8,4,4,8,3,8,8,4,4,8,3,0};
int MAX_DISTANCE[13]={2,8,8,8,2,2,2,8,8,8,2,2,0};
int WECTOR_X[12][8]={{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{1,1,1},{-1,-1,0,1,1,1,0,-1},{-1,-1,0,1,1,1,0,-1},{-1,0,1,0},{-1,1,1,-1},{-2,-1,1,2,2,1,-1,-2},{-1,-1,-1}};
int WECTOR_Y[12][8]={{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1},{0,1,1,1,0,-1,-1,-1},{0,1,1,1,0,-1,-1,-1},{0,1,0,-1},{1,1,-1,-1},{1,2,2,1,-1,-2,-2,-1},{-1,0,1}};
// 0 - King, 1 - Queen, 2 - Rook, 3 - Bishop, 4 - Knight, 5 - Pawn
// 6 - oKing, 7 - oQueen, 8 - oRook, 9 - oBishop, 10 - oKnight, 11 -oPawn
// 12 - emptyField

int evalute(int board[8][8])
{
    int x,y,result = 0;
//    int evaluation[]={LOST,-9,-5,-4,-3,-1,WIN,9,5,4,3,1,0};
    for(x = 0; x < 8; x++)
        for(y = 0; y < 8; y++)
            result += heuristics[board[x][y]][x][y];
    return result;
}

void showBoard(int b[8][8])
{

    char figures[]={'K','Q','R','B','S','P','k','q','r','b','s','p',' '};
    printf("    a   b   c   d   e   f   g   h \n");
    printf("   ------------------------------- \n");
    for(int i = 0; i < 8; i++)
    {
        printf("%d",i);
        for(int j = 0; j < 8; j++)
        {
            printf(" | %c",figures[b[i][j]]);
            if(j == 7 )printf(" |");
        }
        printf("\n");
        if(i != 7 ) printf("  |---|---|---|---|---|---|---|---|\n");
    }
    printf("   --- --- --- --- --- --- --- --- \n");

    printf("\n");
}

void printBoard(int b[8][8])
{

    char figures[]={'K','Q','R','B','S','P','k','q','r','b','s','p',' '};
    printf("    a   b   c   d   e   f   g   h \n");
    printf("   ------------------------------- \n");
    for(int i = 0; i < 8; i++)
    {
        printf("%d",i);
        for(int j = 0; j < 8; j++)
        {
            printf(" | %c",figures[b[i][j]]);
            if(j == 7 )printf(" |");
        }
        printf("\n");
        if(i != 7 ) printf("  |---|---|---|---|---|---|---|---|\n");
    }
    printf("   --- --- --- --- --- --- --- --- \n");

    printf("\n");
}

int bestMove(int board[8][8], int mode, int *x, int *y,  int *dir, int *dist){
    int pompx, pompy, pomdir, pomdist, px, py, dx, dy, direction, distance;
    int result, maxr, minr, move, beat;
    result = evalute(board);
    if(!mode || 2*result > WIN || 2*result < LOST ) return result;
    if(mode % 2 == 0){
        for(px = 0, maxr = 100 * LOST; px < 8; px++){
            for(py = 0; py < 8; py++){
                if(board[px][py]>=6 && board[px][py]< 12){
                    for(direction = 0; direction < MAX_DIRECTION[board[px][py]]; direction++){
                        for(distance = 1; distance < MAX_DISTANCE[board[px][py]]; distance++){
                            dx = (distance-1)*WECTOR_X[board[px][py]][direction];
                            dy = (distance-1)*WECTOR_Y[board[px][py]][direction];

                            if(distance > 1 && board[px+dx][py+dy] != EMPTY) break;

                            dx = distance * WECTOR_X[board[px][py]][direction];
                            dy = distance * WECTOR_Y[board[px][py]][direction];
                            if(px+dx >= 0 && px+dx < 8 && py+dy >=0 && py+dy <8){
                                if(board[px+dx][py+dy] < 6 || board[px+dx][py+dy] == EMPTY){
                                    if((board[px][py] != 11) || (board[px+dx][py+dy] == EMPTY && dy==0) || (board[px+dx][py+dy] != EMPTY && dy!=0)){
                                        move = board[px][py];
                                        beat = board[px+dx][py+dy];
                                        board[px+dx][py+dy] = board[px][py];
                                        board[px][py] = EMPTY;

                                        if(board[px+dx][py+dy] == 11 && px+dx == 0){
                                            board[px+dx][py+dy] = 7;
                                        }
                                        result = bestMove(board,mode - 1,&pompx,&pompy,&pomdir,&pomdist);
                                        board[px][py] = move;
                                        board[px+dx][py+dy] = beat;
                                        if(result >= maxr){
                                            maxr=result;
                                            *x=px;
                                            *y=py;
                                            *dir = direction;
                                            *dist = distance;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return maxr;
    } else {
        for(px = 0, minr = 100 * WIN; px < 8; px++){
            for(py = 0; py < 8; py++){
                if(board[px][py]<6){
                    for(direction = 0; direction < MAX_DIRECTION[board[px][py]];direction++ ){
                        for(distance = 1; distance < MAX_DISTANCE[board[px][py]]; distance++){
                            dx = (distance-1)*WECTOR_X[board[px][py]][direction];
                            dy = (distance-1)*WECTOR_Y[board[px][py]][direction];

                            if(distance > 1 && board[px+dx][py+dy] != EMPTY) break;

                            dx = distance * WECTOR_X[board[px][py]][direction];
                            dy = distance * WECTOR_Y[board[px][py]][direction];
                            if(px+dx >= 0 && px+dx < 8 && py+dy >=0 && py+dy <8){
                                if(board[px+dx][py+dy] == EMPTY || board[px+dx][py+dy] >= 6){
                                    if((board[px][py] != 5) || (board[px+dx][py+dy] == EMPTY && dy==0) || (board[px+dx][py+dy] != EMPTY && dy!=0)){
                                        move = board[px][py];
                                        beat = board[px+dx][py+dy];
                                        board[px+dx][py+dy] = board[px][py];
                                        board[px][py] = EMPTY;

                                        if(board[px+dx][py+dy] == 5 && px+dx == 7){
                                            board[px+dx][py+dy] = 1;
                                        }
                                        result = bestMove(board,mode - 1,&pompx,&pompy,&pomdir,&pomdist);
                                        board[px][py] = move;
                                        board[px+dx][py+dy] = beat;
                                        if(result <= minr){
                                            minr=result;
                                            *x=px;
                                            *y=py;
                                            *dir = direction;
                                            *dist = distance;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return minr;
    }

}

void moveAI(int board[8][8],int x, int y, int direction, int distance){
    int dx = (distance)*WECTOR_X[board[x][y]][direction];
    int dy = (distance)*WECTOR_Y[board[x][y]][direction];
    board[x+dx][y+dy] = board[x][y];
    board[x][y] = EMPTY;
}

int move(int board[8][8], int playerX, char playerY, int playerDX, char playerDY){
   int x = playerX;
   int dx = playerDX;
   int y = playerY - 97;
   int dy = playerDY - 97;

    if(x > 8 || x < 0 || y > 8 || y < 0) {
        return 0;
    }

    if(board[x][y]<6){
        for(int direction = 0; direction <= MAX_DIRECTION[board[x][y]]; direction++){
            for(int dist = 1; dist <= MAX_DISTANCE[board[x][y]]; dist++) {
                int wX = (dist - 1) * WECTOR_X[board[x][y]][direction];
                int wY = (dist - 1) * WECTOR_Y[board[x][y]][direction];
                if (dist > 1 && board[x + wX][y + wY] != EMPTY) break;

                wX = (dist) * WECTOR_X[board[x][y]][direction];
                wY = (dist) * WECTOR_Y[board[x][y]][direction];
                if ((x+wX != dx || y+wY != dy)) continue;
                if (dx >= 0 && dx < 8 && dy >= 0 && dy < 8) {
                    if (board[dx][dy] == EMPTY || board[dx][dy] >= 6) {
                        if ((board[x][y] != 5) || (board[dx][dy] == EMPTY && wY == 0) ||
                            (board[dx][dy] != EMPTY && wY != 0)) {
                            board[dx][dy] = board[x][y];
                            board[x][y] = EMPTY;
                            if (board[dx][dy] == 5 && dx == 7) {
                                board[dx][dy] = 1;
                            }
                            return 1;
                        }
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            }
        }
    } else {
        return 0;
    }
    return 0;
}

int ifwin(int board[8][8]){
    int result=0; // 3 - still playing, 1 - player won, 2 - computer won
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(board[x][y] == 6) result += 2;
            if(board[x][y] == 0) result += 1;
        }
    }
    return result;
}

//int main(){
//    int board[8][8]={{2,4,3,1,0,3,4,2},{5,5,5,5,5,5,5,5},{12,12,12,12,12,12,12,12},{12,12,12,12,12,12,12,12},{12,12,12,12,12,12,12,12},{12,12,12,12,12,12,12,12},{11,11,11,11,11,11,11,11},{8,10,9,7,6,9,10,8}};
//    int x,y,direction,distance, playerX, playerDX;
//    char playerY, playerDY;
//    while(1){
//        bestMove(board,4,&x,&y,&direction,&distance);
//        moveAI(board,x,y,direction,distance);
//        showBoard(board);
//        switch (ifwin(board)) {
//            case 1:
//                printf("You won!");
//                return 0;
//            case 2:
//                printf("Computer won :(");
//                return 0;
//        }
//
//        do{
//            printf("Type correct figure's position and destination - format: row col row col\n");
//            scanf("%d %c %d %c",&playerX,&playerY,&playerDX,&playerDY);
//        } while(!move(board,playerX,playerY,playerDX,playerDY));
//        showBoard(board);
//
//        switch (ifwin(board)) {
//            case 1:
//                printf("You won!");
//                return 0;
//            case 2:
//                printf("Computer won :(");
//                return 0;
//        }
//    }
//}