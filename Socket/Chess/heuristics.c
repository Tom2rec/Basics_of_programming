#define LOST -100000
#define WIN 100000
int heuristics[13][8][8] = {
        // KING
        {
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
                {LOST, LOST, LOST, LOST, LOST, LOST, LOST,LOST},
        },
        // QUEEEN
        {
                {-176, -178, -178, -179, -179, -178, -178, -176},
                {-178, -180, -180, -180, -180, -180, -180, -178},
                {-178, -180, -181, -181, -181, -181, -180, -178},
                {-179, -180, -181, -181, -181, -181, -180, -179},
                {-180, -180, -181, -181, -181, -181, -180, -179},
                {-178, -181, -181, -181, -181, -181, -180, -178},
                {-178, -180, -181, -180, -180, -180, -180, -178},
                {-176, -178, -178, -179, -179, -178, -178, -176},
        },
        // ROOK
        {       {-100, -100, -100, -100, -100, -100, -100, -100},
                {-101, -102, -102, -102, -102, -102, -102, -101},
                {-99, -100, -100, -100, -100, -100, -100, -99},
                {-99, -100, -100, -100, -100, -100, -100, -99},
                {-99, -100, -100, -100, -100, -100, -100, -99},
                {-99, -100, -100, -100, -100, -100, -100, -99},
                {-99, -100, -100, -100, -100, -100, -100, -99},
                {-100, -100, 100, -101, -101, -100, -100, -100},
        },
        // BISHOP 
        {
                {-56, -58, -58, -58, -58, -58, -58, -56},
                {-58, -60, -60, -60, -60, -60, -60, -58},
                {-58, -60, -61, -62, -62, -61, -60, -58},
                {-58, -61, -61, -62, -62, -61, -61, -58},
                {-58, -60, -62, -62, -62, -62, -60, -58},
                {-58, -62, -62, -62, -62, -62, -62, -58},
                {-58, -61, -60, -60, -60, -60, -61, -58},
                {-56, -58, -58, -58, -58, -58, -58, -56},
        },
        // KNIGHT (S)
        {
                {-50, -52, -54, -54, -54, -54, -52, -50},
                {-52, -56, -60, -60, -60, -60, -56, -52},
                {-54, -60, -62, -63, -63, -62, -60, -54},
                {-54, -61, -63, -64, -64, -63, -61, -54},
                {-54, -60, -63, -64, -64, -63, -60, -54},
                {-54, -61, -62, -63, -63, -62, -61, -54},
                {-52, -56, -60, -61, -61, -60, -56, -52},
                {-50, -52, -54, -54, -54, -54, -52, -50},
        },
        // PAWN 
        {
                {-20, -20, -20, -20, -20, -20, -20, -20},
                {-30, -30, -30, -30, -30, -30, -30, -30},
                {-22, -22, -24, -26, -26, -24, -22, -22},
                {-21, -21, -22, -25, -25, -22, -21, -21},
                {-20, -20, -20, -24, -24, -20, -20, -20},
                {-21, -19, -18, -20, -20, -18, -19, -21},
                {-21, -22, -22, -16, -16, -22, -22, -21},
                {-20, -20, -20, -20, -20, -20, -20, -20},
        },
        // oKing
        {
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
                {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN}
        },
        // oQueen
        {
                {176, 178, 178, 179, 179, 178, 178, 176},
                {178, 180, 180, 180, 180, 180, 180, 178},
                {178, 180, 181, 181, 181, 181, 180, 178},
                {179, 180, 181, 181, 181, 181, 180, 179},
                {180, 180, 181, 181, 181, 181, 180, 179},
                {178, 181, 181, 181, 181, 181, 180, 178},
                {178, 180, 181, 180, 180, 180, 180, 178},
                {176, 178, 178, 179, 179, 178, 178, 176},
        },
        // oRook
        {       {100, 100, 100, 101, 101, 100, 100, 100},
                {99, 100, 100, 100, 100, 100, 100, 99},
                {99, 100, 100, 100, 100, 100, 100, 99},
                {99, 100, 100, 100, 100, 100, 100, 99},
                {99, 100, 100, 100, 100, 100, 100, 99},
                {99, 100, 100, 100, 100, 100, 100, 99},
                {101, 102, 102, 102, 102, 102, 102, 101},
                {100, 100, 100, 100, 100, 100, 100, 100},
        },
        // oBishop
        {
                {56, 58, 58, 58, 58, 58, 58, 56},
                {58, 61, 60, 60, 60, 60, 61, 58},
                {58, 62, 62, 62, 62, 62, 62, 58},
                {58, 60, 62, 62, 62, 62, 60, 58},
                {58, 61, 61, 62, 62, 61, 61, 58},
                {58, 60, 61, 62, 62, 61, 60, 58},
                {58, 60, 60, 60, 60, 60, 60, 58},
                {56, 58, 58, 58, 58, 58, 58, 56},
        },
        // oKnight (s)
        {
                {50, 52, 54, 54, 54, 54, 52, 50},
                {52, 56, 60, 60, 60, 60, 56, 52},
                {54, 60, 62, 63, 63, 62, 60, 54},
                {54, 61, 63, 64, 64, 63, 61, 54},
                {54, 60, 63, 64, 64, 63, 60, 54},
                {54, 61, 62, 63, 63, 62, 61, 54},
                {52, 56, 60, 61, 61, 60, 56, 52},
                {50, 52, 54, 54, 54, 54, 52, 50},
        },
        // oPawn
        {
                {20, 20, 20, 20, 20, 20, 20, 20},
                {21, 22, 22, 16, 16, 22, 22, 21},
                {21, 19, 18, 20, 20, 18, 19, 21},
                {20, 20, 20, 24, 24, 20, 20, 20},
                {21, 21, 22, 25, 25, 22, 21, 21},
                {22, 22, 24, 26, 26, 24, 22, 22},
                {30, 30, 30, 30, 30, 30, 30, 30},
                {20, 20, 20, 20, 20, 20, 20, 20}
        },
        // EMPTY
        {
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
                {0,0,0,0,0,0,0,0},
        }

};