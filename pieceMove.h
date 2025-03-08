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
    Bool isAlive;
} PieceInBoard;

int definePieceTeam(PieceInBoard **pieceBoard, Column startX, int startY);

int definePlayerTeam(Player player);

_Bool playerPlayHisPiece(PieceInBoard **pieceBoard, Column startX, int startY, Player player);

_Bool pieceIsEatable(PieceInBoard **pieceBoard, Column endX, int endY, Player player);

int lastPawnMove(int startY, int endY);

_Bool canEnPassantCapture(PieceInBoard **pieceBoard, Column startX, int startY, int endY);

void pawnEatWithEnPassant(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY);

_Bool pawnCanEat(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pieceEat(PieceInBoard **pieceBoard, Column endX, int endY);

_Bool pawnHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, int endY, Player player);

_Bool specificPieceHasNoObstacle(PieceInBoard **pieceBoard, Column endX, int endY, Player player);

_Bool inLineHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool diagonalHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool pieceHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pieceChangeState(PieceInBoard **pieceBoard, Column startX, int startY);

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pawnMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool bishopCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool kingCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pieceIsPlaying(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

#endif //PIECEMOVE_H