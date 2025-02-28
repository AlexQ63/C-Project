#include "pieceMove.h"
#include "player.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY){
    pieceBoard[endX][endY] = pieceBoard[startX][startY];
	pieceBoard[startX][startY].type = EMPTY;
}

void pieceChangeState(PieceInBoard **pieceBoard, Column startX, int startY) {
	pieceBoard[startX][startY].hasMoved = TRUE;
}

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY) {
    if (!positionIsInTheBoard(endX, endY)) {
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

void pawnMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_PAWN || pieceBoard[startX][startY].type == BLACK_PAWN) {
		if (pawnCanMove(pieceBoard, startX, startY, endX, endY)) {
			if (pieceBoard[startX][startY].hasMoved == FALSE) {
				pieceChangeState(pieceBoard, startX, startY);
			}
			pieceMove(pieceBoard, startX, startY, endX, endY);
		}
    }
	else {
    	printf("Wrong position, try again from the start!\n");
      	playerPlay(player, pieceBoard);
	}
}

_Bool bishopCanMove(Column startX, int startY, Column endX, int endY) {
    if (!(positionIsInTheBoard(endX, endY))) {
    	return FALSE;
    }

    if (!(abs(endX - startX) == abs(endY - startY))) {
    	return FALSE;
    }

    return TRUE;
}

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
	if (pieceBoard[startX][startY].type == WHITE_BISHOP || pieceBoard[startX][startY].type == BLACK_BISHOP) {
    	if (bishopCanMove(startX, startY, endX, endY)) {
        	pieceMove(pieceBoard, startX, startY, endX, endY);
    	}
	}
    else {
    	printf("Wrong position, try again from the start!\n");
      	playerPlay(player, pieceBoard);
    }
}

_Bool kingCanMove(Column startX, int startY, Column endX, int endY) {
	if (!positionIsInTheBoard(endX, endY)) {
    	return FALSE;
  	}

    if (!(abs(endX - startX) == 1 && abs(endY - startY) == 1) || abs(endX - startY) == 1 && abs(endY - startX) == 1) {
     	return FALSE;
    }

    return TRUE;
}

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_KING || pieceBoard[startX][startY].type == BLACK_KING) {
        if (kingCanMove(startX, startY, endX, endY)) {
          	if (pieceBoard[startX][startY].hasMoved == FALSE) {
      	  		pieceChangeState(pieceBoard, startX, startY);
        	}
        	pieceMove(pieceBoard, startX, startY, endX, endY);
        }
    }
    else {
    	printf("why i'm the king");
    	printf("Wrong position, try again from the start!\n");
      	playerPlay(player, pieceBoard);
    }
}

void displayWhichPiece(PieceInBoard **pieceBoard, Column x, int y) {
    switch (pieceBoard[x][y].type) {
        case WHITE_PAWN:
            printf("You have select : WHITE_PAWN ");
            break;
        case WHITE_KING:
            printf("You have select : WHITE_KING ");
            break;
        case WHITE_QUEEN:
            printf("You have select : WHITE_QUEEN ");
            break;
        case WHITE_BISHOP:
            printf("You have select : WHITE_BISHOP ");
            break;
        case WHITE_KNIGHT:
            printf("You have select : WHITE_KNIGHT ");
            break;
        case WHITE_ROOK:
            printf("You have select : WHITE_ROOK ");
            break;
        case BLACK_PAWN:
            printf("You have select : BLACK_PAWN ");
            break;
        case BLACK_KING:
            printf("You have select : BLACK_KING ");
            break;
        case BLACK_QUEEN:
            printf("You have select : BLACK_QUEEN ");
            break;
        case BLACK_BISHOP:
            printf("You have select : BLACK_BISHOP ");
            break;
        case BLACK_KNIGHT:
            printf("You have select : BLACK_KNIGHT ");
            break;
        case BLACK_ROOK:
            printf("You have select : BLACK_ROOK ");
            break;
        default:
            printf("You have select : NOTHING ");
            break;
    }
}

void pieceIsPlaying(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
	switch (pieceBoard[startX][startY].type) {
	    case WHITE_PAWN:
        case BLACK_PAWN:
			pawnMove(pieceBoard, startX, startY, endX, endY, player);
			break;
		
        case WHITE_KING:
        case BLACK_KING:
        	kingMove(pieceBoard, startX, startY, endX, endY, player);
			break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
        	bishopMove(pieceBoard, startX, startY, endX, endY, player);
			break;

        case WHITE_QUEEN:
        case BLACK_QUEEN:

			break;
        case WHITE_KNIGHT:
		case BLACK_KNIGHT:

			break;
        case WHITE_ROOK:
        case BLACK_ROOK:

			break;
        default:
            printf("Wrong piece");
            return;
    }
}