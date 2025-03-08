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

void displayNewBoard(PieceInBoard ** board);

void placePiece(PieceInBoard **board, Column x, int y, Piece piece);

char columnToString(Column column);

void resetBoardPiece(PieceInBoard **board);

void displayBoard(PieceInBoard **board);

_Bool positionIsInTheBoard(Column x, int y);

void displayWhichPiece(PieceInBoard **pieceBoard, Column x, int y);

#endif //BOARD_H
