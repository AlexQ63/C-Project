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

typedef enum {
    WHITE_KING_SIDE_CASTLING,
    WHITE_QUEEN_SIDE_CASTLING,
    BLACK_KING_SIDE_CASTLING,
    BLACK_QUEEN_SIDE_CASTLING,
    NO_SIDE_CASTLING
} Castling;

Team definePieceTeam(PieceInBoard **pieceBoard, Column startX, int startY);

int definePlayerTeam(Player player);

_Bool playerPlayHisPiece(PieceInBoard **pieceBoard, Column startX, int startY, Player player);

void pieceChangeState(PieceInBoard **pieceBoard, Column startX, int startY);

_Bool pawnHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, int endY);

_Bool specificPieceHasNoObstacle(PieceInBoard **pieceBoard, Column endX, int endY, Player player);

_Bool inLineHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool diagonalHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool hubPieceHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool pieceIsEatable(PieceInBoard **pieceBoard, Column endX, int endY, Player player);

void pieceEat(PieceInBoard **pieceBoard, Column endX, int endY);

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool pawnCanEat(Column startX, int startY, Column endX, int endY);

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void pawnMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool bishopCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool rookCanMove(Column startX, int startY, Column endX, int endY);

void rookMove(Column startX, int startY, Column endX, int endY , PieceInBoard **pieceBoard, Player player);

_Bool knightCanMove(PieceInBoard **pieceBoard,Column startX, int startY, Column endX, int endY, Player player);

void knightMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool queenCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void queenMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool kingCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

void hubPieceIsPlaying(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool pieceCanEatKing(PieceInBoard **pieceBoard, Player player);

void displayIfInChest(PieceInBoard **pieceBoard, Player player);

_Bool hubPieceCanEatKing(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool hubPieceCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

_Bool canPromotePawn(PieceInBoard **pieceBoard, int endY);

void promotePawn(PieceInBoard **pieceBoard, Column endX, int endY, Player player);

int lastPawnMove(int startY, int endY);

_Bool canEnPassantCapture(PieceInBoard **pieceBoard, Column startX, int startY, int endY);

void pawnEatWithEnPassant(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player);

char * defineAnswerCastling();

_Bool canCastling(PieceInBoard **pieceBoard, Column startX, int startY, Player player);

Castling whichCastling(PieceInBoard **pieceBoard, Player player);

_Bool decideCastling(PieceInBoard **pieceBoard, Player player);

void castling(PieceInBoard **pieceBoard, Player player);

#endif //PIECEMOVE_H