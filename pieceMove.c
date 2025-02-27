#include "pieceMove.h"
#include "player.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pieceSetState(PieceInBoard **board){
   for (int i = 7; i >= 0; i--) {
   		for (int j = 0; j < 8; j++) {
        	if (board[i][j].type != EMPTY){
            	board[i][j].hasMoved = FALSE;
            }
        }
   }
}

void pieceMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY){
    pieceBoard[endX][endY] = pieceBoard[startX][startY];
	pieceBoard[startX][startY].type = EMPTY;
}

void pieceChangeState(PieceInBoard **pieceBoard, int startX, int startY) {
	pieceBoard[startX][startY].hasMoved = TRUE;
}

_Bool pawnCanMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY) {
    if (!(positionIsInTheBoard(endX, endY))) {
    	return FALSE;
    }

    if (pieceBoard[startX][startY].hasMoved == FALSE) {
        if (abs(endY - startY) <= 2 && abs(endY - startY) != 0 && endX == startX) {
    		return TRUE;
        }
    }

    if (abs(endY - startY) == 1 && endX == startX) {
      	return TRUE;
    }
    return FALSE;
}

void pawnMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_PAWN || pieceBoard[startX][startY].type == BLACK_PAWN) {
		if (pawnCanMove(pieceBoard, startX, startY, endX, endY)) {
      	  	if (pieceBoard[startX][startY].hasMoved == FALSE) {
      	  		pieceChangeState(pieceBoard, startX, startY);
        	}
			pieceMove(pieceBoard, startX, startY, endX, endY);
        }
    }
    else {
    	printf("Wrong position, try again!\n");
      	playerPlay(player, pieceBoard);
    }
}

_Bool bishopCanMove(int startX, int startY, int endX, int endY) {
    if (!(positionIsInTheBoard(endX, endY))) {
    	return FALSE;
    }

    if (!(abs(endX - startX) == abs(endY - startY))) {
    	return FALSE;
    }

    return TRUE;
}

void bishopMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player) {
	if (pieceBoard[startX][startY].type == WHITE_BISHOP || pieceBoard[startX][startY].type == BLACK_BISHOP) {
    	if (bishopCanMove(startX, startY, endX, endY)) {
        	pieceMove(pieceBoard, startX, startY, endX, endY);
    	}
	}

    else {
    	printf("Wrong position, try again!\n");
      	playerPlay(player, pieceBoard);
    }
}

_Bool kingCanMove(int startX, int startY, int endX, int endY) {
	if (!(positionIsInTheBoard(endX, endY))) {
    	return FALSE;
  	}

    if (!(abs(endX - startX) == 1 && abs(endY - startY) == 1) || abs(endX - startY) == 1 && abs(endY - startX) == 1) {
     	return FALSE;
    }

    return TRUE;
}

void kingMove(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_KING || pieceBoard[startX][startY].type == BLACK_KING) {
        if (kingCanMove(startX, startY, endX, endY)) {
          	if (pieceBoard[startX][startY].hasMoved == FALSE) {
      	  		pieceChangeState(pieceBoard, startX, startY);
        	}
        	pieceMove(pieceBoard, startX, startY, endX, endY);
        }
    }

    else {
    	printf("Wrong position, try again!\n");
      	playerPlay(player, pieceBoard);
    }
}

void displayWhichPiece(PieceInBoard **pieceBoard, int x, int y) {
    switch (pieceBoard[x][y].type) {
        case WHITE_PAWN:
            printf("%s", "You have select : WHITE_PAWN");
        case WHITE_KING:
            printf("%s", "You have select : WHITE_KING");
        case WHITE_QUEEN:
            printf("%s", "You have select : WHITE_QUEEN");
        case WHITE_BISHOP:
            printf("%s", "You have select : WHITE_BISHOP");
        case WHITE_KNIGHT:
            printf("%s", "You have select : WHITE_KNIGHT");
        case WHITE_ROOK:
            printf("%s", "You have select : WHITE_ROOK");
        case BLACK_PAWN:
            printf("%s", "You have select : BLACK_PAWN");
        case BLACK_KING:
            printf("%s", "You have select : BLACK_KING");
        case BLACK_QUEEN:
            printf("%s", "You have select : BLACK_QUEEN");
        case BLACK_BISHOP:
            printf("%s", "You have select : BLACK_BISHOP");
        case BLACK_KNIGHT:
            printf("%s", "You have select : BLACK_KNIGHT");
        case BLACK_ROOK:
            printf("%s", "You have select : BLACK_ROOK");
        default:
            printf("%s", "You have select : NOTHING");
    }
}

void pieceIsPlaying(PieceInBoard **pieceBoard, int startX, int startY, int endX, int endY, Player player) {
	switch (pieceBoard[startX][startY].type) {
	    case WHITE_PAWN:
        case BLACK_PAWN:
			pawnMove(pieceBoard, startX, startY, endX, endY, player);

        case WHITE_KING:
        case BLACK_KING:
        	kingMove(pieceBoard, startX, startY, endX, endY, player);

        case WHITE_BISHOP:
        case BLACK_BISHOP:
        	bishopMove(pieceBoard, startX, startY, endX, endY, player);

        case WHITE_QUEEN:
        case BLACK_QUEEN:


        case WHITE_KNIGHT:
		case BLACK_KNIGHT:


        case WHITE_ROOK:
        case BLACK_ROOK:

        default:
            printf("Wrong piece");
            return;
    }
}