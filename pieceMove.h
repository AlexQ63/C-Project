#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include "piece.h"
#include "player.h"

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

typedef enum {
    FALSE,
    TRUE
  } Bool;

typedef struct {
    Piece type;
    Bool hasMoved;
} PieceInBoard;

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY);

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY);

void pawnMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool bishopCanMove(Column startX, int startY, Column endX, int endY);

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool kingCanMove(Column startX, int startY, Column endX, int endY);

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void displayWhichPiece(PieceInBoard **pieceBoard, Column x, int y);

void pieceIsPlaying(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

#endif //PIECEMOVE_H