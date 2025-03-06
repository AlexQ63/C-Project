#include "game.h"
#include <stdio.h>

_Bool blackKingIsAlive(PieceInBoard **board) {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[j][i].type == BLACK_KING) {
                return TRUE;
            }
        }
    }
    deleteBoard(board);
    return FALSE;
}
// TODO simplifier le code de ces 2 fonctions.
_Bool whiteKingIsAlive(PieceInBoard **board) {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[j][i].type == WHITE_KING) {
                return TRUE;
            }
        }
    }
    deleteBoard(board);
    return FALSE;
}

_Bool definePlayerWin(PieceInBoard **pieceBoard) {
    if (blackKingIsAlive(pieceBoard) == FALSE) {
        printf("Player 1 wins\n");
        printf("Congratulation, you are the best\n");
        return FALSE;
    }
    else if (whiteKingIsAlive(pieceBoard) == FALSE) {
        printf("Player 2 wins\n");
        printf("Congratulation, you are the best\n");
        return FALSE;
    }
    return TRUE;
}

void gamePlay() {
    PieceInBoard **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);

    Player p1 = PLAYER1;
    Player p2 = PLAYER2;

    while (definePlayerWin(board)) {
        playerPlay(p1, board);
        displayNewBoard(board);
        if (definePlayerWin(board) == FALSE) {
            break;
        }
        playerPlay(p2, board);
        displayNewBoard(board);
        if (definePlayerWin(board) == FALSE) {
            break;
        }
    }
}
