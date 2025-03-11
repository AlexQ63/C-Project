#ifndef GAME_H
#define GAME_H

#include "board.h"

void uppercase(char *string);

Position playerAskPosition();

_Bool validMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY);

void playerPlay(Player player, PieceInBoard **pieceBoard) ;

_Bool blackKingIsAlive(PieceInBoard **board);

_Bool whiteKingIsAlive(PieceInBoard **board);

_Bool definePlayerWin(PieceInBoard **pieceBoard);

_Bool playerBeingStalemate(PieceInBoard **pieceBoard, Player player);

void gamePlay();

#endif //GAME_H
