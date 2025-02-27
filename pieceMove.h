#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include "piece.h"
#include "player.h"

typedef enum {
    FALSE,
    TRUE
  } Bool;

typedef struct {
    Piece type;
    Bool hasMoved;
} PieceInBoard;

void pieceSetState(PieceInBoard **board);

void pieceMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY);

void pieceChangeState(PieceInBoard **pieceBoard, int startX, int startY);

_Bool pawnCanMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY);

void pawnMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player);

_Bool bishopCanMove(int startX, int startY, int endX, int endY);

void bishopMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player);

_Bool kingCanMove(int startX, int startY, int endX, int endY);

void kingMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player);

void displayWhichPiece(PieceInBoard **pieceBoard, int x, int y);

void pieceIsPlaying(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player);

#endif //PIECEMOVE_H