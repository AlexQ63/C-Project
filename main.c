#include "board.h"

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    PieceInBoard **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);
    deleteBoard(board);

    Player p1 = PLAYER1;
    Player p2 = PLAYER2;

    playerPlay(p1, board);
    playerPlay(p2, board);

    return 0;
}
