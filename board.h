#ifndef BOARD_H
#define BOARD_H

#include "pieceMove.h"

typedef enum {
    A = 1,
    B,
    C,
    D,
    E,
    F,
    G,
    H
} Column;

typedef struct {
    Column x;
    int y;
} Position;

void deleteBoard(PieceInBoard **board);

PieceInBoard **generateEmptyBoard();

void placePiece(PieceInBoard **board, Column x, int y, Piece piece);

char columnToString(Column column);

void resetBoardPiece(PieceInBoard **board);

void displayBoard(PieceInBoard **board);

Position playerAskPosition();

_Bool positionIsInTheBoard(int x, int y);

void playerPlay(Player player, PieceInBoard **pieceBoard);

#endif //BOARD_H
