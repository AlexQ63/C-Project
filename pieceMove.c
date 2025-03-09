#include "pieceMove.h"
#include "player.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

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

    if (resultWhite == 2 && resultBlack == 1) {
        if (startX + 1 >= 1 && startX + 1 <= 8) {
            if (pieceBoard[startX + 1][startY].type == WHITE_PAWN) {
                return TRUE;
            }
        }

        if (startX - 1 >= 0 && startX - 1 <= 8) {
            if (pieceBoard[startX - 1][startY].type == WHITE_PAWN) {
                return TRUE;
            }
        }

        return FALSE;
    }

    if (resultBlack == 2 && resultWhite == 1) {
        if (startX + 1 >= 1 && startX + 1 <= 8) {
            if (pieceBoard[startX + 1][startY].type == BLACK_PAWN) {
                return TRUE;
            }
        }

        if (startX - 1 >= 0 && startX - 1 <= 8) {
            if (pieceBoard[startX - 1][startY].type == BLACK_PAWN) {
                return TRUE;
            }
        }

        return FALSE;
    }

    return FALSE;
}

void pawnEatWithEnPassant(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (player == PLAYER1) {
        pieceBoard[endX][endY - 1].type = EMPTY;
        pieceBoard[endX][endY - 1].isAlive = FALSE;
    }

    else if (player == PLAYER2) {
        pieceBoard[endX][endY + 1].type = EMPTY;
        pieceBoard[endX][endY + 1].isAlive = FALSE;
    }
}

_Bool pawnCanEat(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (pieceIsEatable(pieceBoard, endX, endY, player) == FALSE) {
        return FALSE;
    }

    if (abs(endY - startY) != 1 && abs(endX - startX) != 1){
        return FALSE;
    }

    return TRUE;
}

void pieceEat(PieceInBoard **pieceBoard, Column endX, int endY) {
        pieceBoard[endX][endY].isAlive = FALSE;
        pieceBoard[endX][endY].type = EMPTY;
}

_Bool pawnHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, int endY) {
    int newY = startY;

    if (pieceBoard[startX][newY].hasMoved == FALSE) {
        do {
            if (pieceBoard[startX][startY].type == WHITE_PAWN) {
                newY++;
                if (endY - startY > 2) {
                    printf("You can't go behind, play again \n");
                    return FALSE;
                }
            }
            else if (pieceBoard[startX][startY].type == BLACK_PAWN) {
                newY--;
                if (startY - endY > 2) {
                    printf("You can't go behind, play again \n");
                    return FALSE;
                }
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
        if (endY - startY != 1) {
            printf("You can't go behind, play again \n");
            return FALSE;
        }
    }

    else if (pieceBoard[startX][startY].type == BLACK_PAWN) {
        newY--;
        if (startY - endY != 1) {
            printf("You can't go behind, play again \n");
            return FALSE;
        }
    }

    if (pieceBoard[startX][newY].type != EMPTY) {
        printf("You can't move this way, something here.\n");
        return FALSE;
    }
    return TRUE;
}

_Bool specificPieceHasNoObstacle(PieceInBoard **pieceBoard, Column endX, int endY, Player player) {
    if (pieceIsEatable(pieceBoard, endX, endY, player) == FALSE && pieceBoard[endX][endY].type != EMPTY) {
        printf("You can't move this way, something here.\n");
        return FALSE;
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
            return pawnHasNoObstacle(pieceBoard, startX, startY, endY);

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
        pawnEatWithEnPassant(pieceBoard, startX, startY, endX, endY, player);
        return TRUE;
    }

    if (pawnCanEat(pieceBoard, startX, startY, endX, endY, player)) {
        pieceEat(pieceBoard, endX, endY);
        return TRUE;
    }

    if (pieceBoard[startX][startY].hasMoved == FALSE) {
        if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == TRUE) {
            if (player == PLAYER1) {
                if (endY - startY <= 2 && endY - startY != 0 && endX == startX) {
                    return TRUE;
                }
            } else {
                if (endY - startY <= 2 && startY - endY != 0 && endX == startX) {
                    return TRUE;
                }
            }
        }
    }

    if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == TRUE) {
        if (player == PLAYER2) {
            if (startY - endY == 1 && endY - startY != 0 && endX == startX) {
                return TRUE;
            }
        } else {
            if (startY - endY <= 2 && startY - endY != 0 && endX == startX) {
                return TRUE;
            }
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
		    if (canPromotePawn(pieceBoard, endY)) {
		        promotePawn(pieceBoard,endX, endY, player);
		    }
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

_Bool rookCanMove (PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (!positionIsInTheBoard(endX, endY)) {
        return FALSE;
    }
    if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == FALSE) {
        return FALSE;
    }
    if (startX != endX && startY != endY) {
        return FALSE;
    }
    return TRUE;
}

void rookMove (Column startX, int startY, Column endX, int endY , PieceInBoard **pieceBoard, Player player) {
    if (pieceBoard[startX][startY].type == WHITE_ROOK || pieceBoard[startX][startY].type == BLACK_ROOK) {
        if (rookCanMove(pieceBoard,startX, startY, endX, endY, player)) {
            if (pieceBoard[startX][startY].hasMoved == FALSE) {
                pieceChangeState(pieceBoard, startX, startY);
            }
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

    if (abs(endX - startX) != 1 && abs(endY - startY) != 1 || abs(endX - startX) != 0 && abs(endY - startY) != 0) {
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
            knightMove(pieceBoard, startX, startY,endX, endY, player);
			break;

        case WHITE_ROOK:
        case BLACK_ROOK:
            rookMove(startX, startY, endX, endY, pieceBoard, player);
			break;

        default:
            printf("Wrong piece. You have to play again\n");
            break;
    }
}

_Bool canPromotePawn(PieceInBoard **pieceBoard, int endY) {
    if (endY == 7 || endY == 0) {
        for (int i = A; i < H; i++) {
            if (pieceBoard[i][endY].type == WHITE_PAWN || pieceBoard[i][endY].type == BLACK_PAWN) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

_Bool compareCharWithList(char * selectPiece, char * list) {
    char * oneLetter;
    for (int i = 0; i < 4; i++) {
        oneLetter = &list[i];
        if (strcmp(oneLetter, &selectPiece[0])) {
            return TRUE;
        }
    }
    return FALSE;
}

void promotePawn(PieceInBoard **pieceBoard, Column endX, int endY, Player player) {
    while (pieceBoard[endX][endY].type == WHITE_PAWN || pieceBoard[endX][endY].type == BLACK_PAWN) {
        char selectPiece[2];
        printf("Congratulation. You can promote your pawn.\n");
        char list[4] = {'Q', 'B', 'R', 'K'};
        do {
            printf("Select your upgrade : Q : Queen - B : Bishop - R : Rook - K : Knight\n");
            scanf("%2s", selectPiece);
            uppercase(selectPiece);
            if (compareCharWithList(selectPiece, list)) {
                printf("Your promote can't be used. You have to choose in ( Q - B - R - K) not anything else.\n");
            }

            if (selectPiece[1] != '\0') {
                printf("Too long. Try again \n");
            }

        } while (strlen(selectPiece) == 2);
        if (player == PLAYER1) {
            if (strcmp(selectPiece, "Q") == 0) {
                pieceBoard[endX][endY].type = WHITE_QUEEN;
            }

            if (strcmp(selectPiece, "B") == 0) {
                pieceBoard[endX][endY].type = WHITE_BISHOP;
            }

            if (strcmp(selectPiece, "R") == 0) {
                pieceBoard[endX][endY].type = WHITE_ROOK;
            }

            if (strcmp(selectPiece, "K") == 0) {
                pieceBoard[endX][endY].type = WHITE_KNIGHT;
            }
        }else if (player == PLAYER2) {
            if (strcmp(selectPiece, "Q") == 0) {
                pieceBoard[endX][endY].type = BLACK_QUEEN;
            }

            if (strcmp(selectPiece, "B") == 0) {
                pieceBoard[endX][endY].type = BLACK_BISHOP;
            }

            if (strcmp(selectPiece, "R") == 0) {
                pieceBoard[endX][endY].type = BLACK_ROOK;
            }

            if (strcmp(selectPiece, "K") == 0) {
                pieceBoard[endX][endY].type = BLACK_KNIGHT;
            }
        } else {
            printf("Error - Not an available piece. Select another one");
            return;
        }
    }
}

_Bool knightCanMove (PieceInBoard **pieceBoard,Column startX, int startY, Column endX, int endY, Player player) {
    if (!positionIsInTheBoard(endX, endY)) {
        return FALSE;
    }
    printf("oui");
    if ((abs(startX - endX) != 2 && abs(startY - endY) != 1) || (abs(startX - endX) != 1 && abs(startY - endY) != 2)) {
        return FALSE;
    }

    printf("oui 2");
    if (pieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player) == FALSE) {
        return FALSE;
    }
    printf("oui 3");
    return TRUE;
}

void knightMove (PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (pieceBoard[startX][startY].type == WHITE_KNIGHT || pieceBoard[startX][startY].type == BLACK_KNIGHT) {
        printf("j'suis un cavalier");
        if (knightCanMove(pieceBoard,startX, startY,endX, endY, player)) {
            pieceMove(pieceBoard,startX, startY,endX, endY, player);
        } else {
            printf("Wrong position, try again from the start!\n");
        }
    }
}

_Bool canEatKing(PieceInBoard **pieceBoard, Column endX, int endY, Player player) {
    Position kingPos = kingIsHere(pieceBoard, player);
    Column kingCurrentPosX = kingPos.x;
    int kingCurrentPosY = kingPos.y;
    if (pieceCanEatKing(pieceBoard, endX, endY, kingCurrentPosX, kingCurrentPosY, player)) {
        printf("CHESS, you have to protect your king.\n");
        return TRUE;
    }
    return FALSE;
}

_Bool pieceCanEatKing(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    switch (pieceBoard[startX][startY].type) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            if (pawnCanEat(pieceBoard, startX, startY,endX, endY, player)) {
                return TRUE;
            }
            return FALSE;

        case WHITE_KING:
        case BLACK_KING:
            printf("King can't eat another King.\n");
            return FALSE;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                if (bishopCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
                }
            }
            return FALSE;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            /*if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                if (queenCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                    return TRUE;
                }
            }
            return FALSE;*/

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                if (knightCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                    return TRUE;
                }
            }
        return FALSE;

        case WHITE_ROOK:
        case BLACK_ROOK:
            if (pieceIsEatable(pieceBoard, endX, endY, player)) {
                if (rookCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                    return TRUE;
                }
            }
        return FALSE;

        default:
            printf("Wrong piece\n");
            return FALSE;
    }
}