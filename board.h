#ifndef BOARD_H
#define BOARD_H

#include "pieceMove.h"

typedef struct {
    Column x;
    int y;
} Position;

void clearBuffer();

void deleteBoard(PieceInBoard **board);

PieceInBoard **generateEmptyBoard();

void placePiece(PieceInBoard **board, Column x, int y, Piece piece);

char columnToString(Column column);

void resetBoardPiece(PieceInBoard **board);

void displayBoard(PieceInBoard **board);

void **displayNewBoard(PieceInBoard ** board);

Position playerAskPosition();

void uppercase (char *string);

_Bool positionIsInTheBoard(Column x, int y);

void playerPlay(Player player, PieceInBoard **pieceBoard);

#endif //BOARD_H
