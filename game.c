#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool canGoNextMove = FALSE;

void uppercase(char *string) {
    int i = 0;

    while (string[i] != '\0') {
        if (string[i]  >= 97 &&  string[i] <= 122)
            string[i] = string[i] - 32;
        i++;
    }
}

Position playerAskPosition() {
    // TODO si les coordonnés ne font pas 2s ça crash (après une erreur)
    char coordonate[3];
    printf("Enter Position Column and Row (ex : C5) : ");
    scanf("%2s", coordonate);
    uppercase(coordonate);
    /*clearBuffer();*/
    Position pos;
    pos.x = coordonate[0] - 'A';
    pos.y = coordonate[1] - '1';
    return pos;
}

_Bool validMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY) {
    if (pieceBoard[startX][startY].type != EMPTY) {
        return FALSE;
    }

    if (pieceBoard[endX][endY].type == EMPTY) {
        return FALSE;
    }
    return TRUE;
}

void playerPlay(Player player, PieceInBoard **pieceBoard) {
    if (player == PLAYER1) {
        printf("Player 1 turn, let's play.\n");
    }
    else if (player == PLAYER2) {
        printf("Player 2 turn, let's play.\n");
    }

    Position start = playerAskPosition();
    Column startX = start.x;
    int startY = start.y;

    while (!positionIsInTheBoard(startX, startY)) {
        printf("Invalid position\n, put another position in A - H and 1 - 8\n");
        start = playerAskPosition();
        startX = start.x;
        startY = start.y;
    }

    while (playerPlayHisPiece(pieceBoard, startX, startY, player) == FALSE) {
        printf("You have to play again. \n");
        start = playerAskPosition();
        startX = start.x;
        startY = start.y;
    }

    displayWhichPiece(pieceBoard, startX, startY);

    char *answer = defineNextPlay();
    if (strcmp(answer, "no") == 0) {
        printf("You have to play again, from the start. Select the first coordinate : ");
        return;
    }
    free(answer);
    Position end = playerAskPosition();
    Column endX = end.x;
    int endY = end.y;

    pieceIsPlaying(pieceBoard, startX, startY, endX, endY, player);
    if (validMove(pieceBoard, startX, startY, endX, endY)) {
        canGoNextMove = TRUE;
        lastPawnMove(startY, endY);
    }
}

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
        while (canGoNextMove == FALSE) {
            playerPlay(p1, board);
            displayNewBoard(board);
        }
        canGoNextMove = FALSE;
        if (definePlayerWin(board) == FALSE) {
            break;
        }

        while (canGoNextMove == FALSE) {
            playerPlay(p2, board);
            displayNewBoard(board);
        }
        canGoNextMove = FALSE;
    }
}