#ifndef GAME_H
#define GAME_H

#include "board.h"

_Bool blackKingIsAlive(PieceInBoard **board);

_Bool whiteKingIsAlive(PieceInBoard **board);

_Bool definePlayerWin(PieceInBoard **pieceBoard);

void gamePlay();

#endif //GAME_H
