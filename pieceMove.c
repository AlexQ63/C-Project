#include "pieceMove.h"
#include "player.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int definePieceTeam (PieceInBoard **pieceBoard, Column startX, int startY) {
    if (1 <= pieceBoard[startX][startY].type && pieceBoard[startX][startY].type <= 6 ) {
        return WHITE_TEAM;
    }
    if (7 <= pieceBoard[startX][startY].type && pieceBoard[startX][startY].type <= 12 ) {
        return BLACK_TEAM;
    }
    return 0;
}

int definePlayerTeam(Player player) {
    if (player == PLAYER1) {
        return WHITE_TEAM;
    }
    return BLACK_TEAM;
}

_Bool playerPlayHisPiece(PieceInBoard **pieceBoard, Column startX, int startY, Player player) {
    if (definePlayerTeam(player) == WHITE_TEAM) {
        if (definePieceTeam(pieceBoard, startX, startY) == WHITE_TEAM) {
            return TRUE;
        }
    }

    else {
        if (definePieceTeam(pieceBoard, startX, startY) == BLACK_TEAM) {
            return TRUE;
        }
    }
    printf("You can't play the another player piece's\n");
    return FALSE;
}

_Bool pieceIsEatable(PieceInBoard **pieceBoard, Column endX, int endY, Player player) {
    if (pieceBoard[endX][endY].type != EMPTY) {
        if (definePlayerTeam(player) == WHITE_TEAM) {
            if (definePieceTeam(pieceBoard, endX, endY) == BLACK_TEAM) {
                return TRUE;
            }
        } else {
            if (definePieceTeam(pieceBoard, endX, endY) == WHITE_TEAM) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int lastPawnMove (int startY, int endY) {
    return abs(endY-startY);
}

_Bool canEnPassantCapture(PieceInBoard **pieceBoard, Column startX, int startY, int endY) {
    static int resultBlack = 0;
    static int resultWhite = 0;
    if (pieceBoard[startX][startY].type == BLACK_PAWN) {
        if (lastPawnMove(startY, endY) == 2) {
            resultBlack = 2;
        } else {
            resultBlack = 1;
        }
    }

    if (pieceBoard[startX][startY].type == WHITE_PAWN) {
        if (lastPawnMove(startY, endY) == 2) {
            resultWhite = 2;
        } else {
            resultWhite = 1;
        }
    }

    printf("black : %d\n", resultBlack);
    printf("white : %d\n", resultWhite);

    if (resultWhite == 2 && resultBlack == 1) {
        if (startX + 1 > 1 && startX + 1 < 8) {
            if (pieceBoard[startX + 1][startY].type == WHITE_PAWN) {
                printf("TRUE - Black Pawn is adjacent on the right for En Passant\n");
                return TRUE;
            }
        }

        if (startX - 1 >= 0 && startX - 1 <= 8) {
            if (pieceBoard[startX - 1][startY].type == WHITE_PAWN) {
                printf("TRUE - Black Pawn is adjacent on the left for En Passant\n");
                return TRUE;
            }
        }

        printf("FALSE - No Black Pawn adjacent for En Passant\n");
        return FALSE;
    }

    if (resultBlack == 2 && resultWhite == 1) {
        if (startX + 1 > 1 && startX + 1 < 8) {
            if (pieceBoard[startX + 1][startY].type == BLACK_PAWN) {
                printf("TRUE - White Pawn is adjacent on the right for En Passant\n");
                return TRUE;
            }
        }

        if (startX - 1 >= 0 && startX - 1 <= 8) {  // Vérification pour la case à gauche
            if (pieceBoard[startX - 1][startY].type == BLACK_PAWN) {
                printf("TRUE - White Pawn is adjacent on the left for En Passant\n");
                return TRUE;
            }
        }

        printf("FALSE - No White Pawn adjacent for En Passant\n");
        return FALSE;
    }

    printf("FALSE - No En Passant possible\n");
    return FALSE;
}

void pawnEatWithEnPassant(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY) {
    printf("DEBUG: pieceBoard[%d][%d].type = %d (Expected: %d)\n", startX, startY, pieceBoard[startX][startY].type, WHITE_PAWN);
    if (pieceBoard[startX][startY].type == WHITE_PAWN) {
        printf("DEBUG: White Pawn is capturing via En Passant\n");
        pieceBoard[endX][endY - 1].type = EMPTY;
        pieceBoard[endX][endY - 1].isAlive = FALSE;
    }

    else if (pieceBoard[startX][startY].type == BLACK_PAWN) {
        printf("DEBUG: Black Pawn is capturing via En Passant\n");
        pieceBoard[endX][endY + 1].type = EMPTY;
        pieceBoard[endX][endY + 1].isAlive = FALSE;
    }

    else {
        printf("DEBUG: ERROR - The piece at (%d, %d) is not a pawn!\n", startX, startY);
    }
}

_Bool pawnCanEat(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (pieceIsEatable(pieceBoard, endX, endY, player) == FALSE) {
        return FALSE;
    }

    if (!abs(endY - startY) == 1 && abs(endX - startX) == 1){
        return FALSE;
    }

    return TRUE;
}

void pieceEat(PieceInBoard **pieceBoard, Column endX, int endY) {
        pieceBoard[endX][endY].isAlive = FALSE;
        pieceBoard[endX][endY].type = EMPTY;
}

_Bool pawnHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, int endY, Player player) {
    int newY = startY;

    if (pieceBoard[startX][newY].hasMoved == FALSE) {
        do {
            if (pieceBoard[startX][startY].type == WHITE_PAWN) {
                newY++;
            }
            else if (pieceBoard[startX][startY].type == BLACK_PAWN) {
                newY--;
            }

            if (pieceBoard[startX][newY].type != EMPTY) {
                printf("You can't move this way, something here.\n");
                return FALSE;
            }

        } while (newY != endY);
        return TRUE;
    }

    if (pieceBoard[startX][startY].type == WHITE_PAWN) {
        newY++;
    }
    else if (pieceBoard[startX][startY].type == BLACK_PAWN) {
        newY--;
    }

    if (pieceBoard[startX][newY].type != EMPTY) {
        printf("You can't move this way, something here.\n");
        return FALSE;
    }
    return TRUE;
}

_Bool specificPieceHasNoObstacle(PieceInBoard **pieceBoard, Column endX, int endY, Player player) {
    if (pieceBoard[endX][endY].type != EMPTY) {
        if (pieceIsEatable(pieceBoard, endX, endY, player) == FALSE) {
            printf("You can't move this way, something here.\n");
            return FALSE;
        }
    }
    return TRUE;
}

_Bool inLineHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    Column newX = startX;
    int newY = startY;

    if (abs(endX - newX) != 0 && endY - newY == 0) {
        do {

            if (newX < endX) {
                newX++;
            } else {
                newX--;
            }

            if (newX == endX) {
                if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                    return TRUE;
                }
            }

            if (pieceBoard[newX][startY].type != EMPTY) {
                printf("You can't move this way, something here.\n");
                return FALSE;
            }

        } while (newX != endX);
        return TRUE;
    }
    if (abs(endY - startY) != 0 && endX - startX ==0) {
        do {
            if (newY < endY) {
                newY++;
            } else {
                newY--;
            }

            if (newY == endY) {
                if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                    return TRUE;
                }
            }

            if (pieceBoard[startX][newY].type != EMPTY) {
                printf("You can't move this way, something here.\n");
                return FALSE;
            }

        } while (newY != endY);
    }
    return TRUE;
}


_Bool diagonalHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    Column newX = startX;
    int newY = startY;

    do {

        if (newX < endX) {
            newX++;
        } else {
            newX--;
        }

        if (newY < endY) {
            newY++;
        } else {
            newY--;
        }

        if (newX == endX && newY == endY) {
            if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                return TRUE;
            }
        }

        if (pieceBoard[newX][newY].type != EMPTY) {
            printf("You can't move this way, something here.\n");
            return FALSE;
        }

    } while (newX != endX && newY != endY);

    return TRUE;
}

_Bool pieceHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    switch (pieceBoard[startX][startY].type) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            return pawnHasNoObstacle(pieceBoard, startX, startY, endY, player);

        case WHITE_KING:
        case BLACK_KING:
            return specificPieceHasNoObstacle(pieceBoard, endX, endY, player);

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            return diagonalHasNoObstacle(pieceBoard, startX, startY, endX, endY, player);

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            return inLineHasNoObstacle(pieceBoard, startX, startY, endX, endY, player) || diagonalHasNoObstacle(pieceBoard, startX, startY, endX, endY, player);

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            return specificPieceHasNoObstacle(pieceBoard, endX, endY, player);

        case WHITE_ROOK:
        case BLACK_ROOK:
            return inLineHasNoObstacle(pieceBoard, startX, startY, endX, endY, player);
        //TODO Attention, prévoir pour les roques
        default:
            printf("Wrong piece\n");
            return FALSE;
    }
}

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player){
    if (pieceIsEatable(pieceBoard, endX, endY, player)) {
        pieceEat(pieceBoard, endX, endY);
    }
    pieceBoard[endX][endY] = pieceBoard[startX][startY];
	pieceBoard[startX][startY].type = EMPTY;
}

void pieceChangeState(PieceInBoard **pieceBoard, Column startX, int startY) {
	pieceBoard[startX][startY].hasMoved = TRUE;
}

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (!positionIsInTheBoard(endX, endY)) {
    	return FALSE;
    }

    if (canEnPassantCapture(pieceBoard, startX, startY, endY)) {
        pawnEatWithEnPassant(pieceBoard, startX, startY, endX, endY);
        return TRUE;
    }

    if (pawnCanEat(pieceBoard, startX, startY, endX, endY, player)) {
        pieceEat(pieceBoard, endX, endY);
        return TRUE;
    }

    if (pieceBoard[startX][startY].hasMoved == FALSE) {
        if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == TRUE) {
            if (abs(endY - startY) <= 2 && abs(endY - startY) != 0 && endX == startX) {
                return TRUE;
            }
        }
    }

    if (abs(endY - startY) == 1 && endX == startX) {
        if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == TRUE) {
            return TRUE;
        }
    }
    return FALSE;
}

void pawnMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_PAWN || pieceBoard[startX][startY].type == BLACK_PAWN) {
		if (pawnCanMove(pieceBoard, startX, startY, endX, endY, player)) {
			if (pieceBoard[startX][startY].hasMoved == FALSE) {
				pieceChangeState(pieceBoard, startX, startY);
			}
			pieceMove(pieceBoard, startX, startY, endX, endY, player);
		}
    } else {
    	printf("Wrong position, try again from the start!\n");
	}
}

_Bool bishopCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (!positionIsInTheBoard(endX, endY)) {
    	return FALSE;
    }

    if (abs(endX - startX) != abs(endY - startY)) {
    	return FALSE;
    }

    if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == FALSE) {
        return FALSE;
    }
    return TRUE;
}

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
	if (pieceBoard[startX][startY].type == WHITE_BISHOP || pieceBoard[startX][startY].type == BLACK_BISHOP) {
    	if (bishopCanMove(pieceBoard,startX, startY, endX, endY, player)) {
        	pieceMove(pieceBoard, startX, startY, endX, endY, player);
    	} else {
    	    printf("Wrong position, try again from the start!\n");
    	}
	}
}

_Bool kingCanMove(PieceInBoard **pieceBoard,Column startX, int startY, Column endX, int endY, Player player) {
	if (!positionIsInTheBoard(endX, endY)) {
    	return FALSE;
  	}

    if (!(abs(endX - startX) == 1 && abs(endY - startY) == 1) || abs(endX - startY) == 1 && abs(endY - startX) == 1) {
     	return FALSE;
    }

    if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == FALSE) {
        return FALSE;
    }

    return TRUE;
}

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_KING || pieceBoard[startX][startY].type == BLACK_KING) {
        if (kingCanMove(pieceBoard,startX, startY, endX, endY, player)) {
          	if (pieceBoard[startX][startY].hasMoved == FALSE) {
      	  		pieceChangeState(pieceBoard, startX, startY);
        	}
        	pieceMove(pieceBoard, startX, startY, endX, endY, player);
        } else {
            printf("Wrong position, try again from the start!\n");
        }
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
            printf("Wrong piece. You have to plaiy again\n");
            break;
    }
}