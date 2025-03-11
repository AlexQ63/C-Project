#ifndef PLAYER_H
#define PLAYER_H

typedef enum {
    PLAYER1,
    PLAYER2
} Player;

char * defineNextPlay();

_Bool compareCharWithList(char * selectPiece, char * list);

#endif //PLAYER_H
