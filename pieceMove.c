#include "pieceMove.h"
#include "player.h"
#include "board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game.h"

Team definePieceTeam (PieceInBoard **pieceBoard, Column startX, int startY) {
    if (1 <= pieceBoard[startX][startY].type && pieceBoard[startX][startY].type <= 6 ) {
        return WHITE_TEAM;
    }

    if (7 <= pieceBoard[startX][startY].type && pieceBoard[startX][startY].type <= 12 ) {
        return BLACK_TEAM;
    }

    if (pieceBoard[startX][startY].type == 0) {
        return NO_TEAM;
    }

    return NO_TEAM;
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

void pieceChangeState(PieceInBoard **pieceBoard, Column startX, int startY) {
    pieceBoard[startX][startY].hasMoved = TRUE;
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

_Bool hubPieceHasNoObstacle(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
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

        default:
            printf("Wrong piece\n");
            return FALSE;
    }
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

void pieceEat(PieceInBoard **pieceBoard, Column endX, int endY) {
    pieceBoard[endX][endY].isAlive = FALSE;
    pieceBoard[endX][endY].type = EMPTY;
}

void pieceMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player){
    if (pieceIsEatable(pieceBoard, endX, endY, player)) {
        pieceEat(pieceBoard, endX, endY);
    }
    pieceBoard[endX][endY] = pieceBoard[startX][startY];
	pieceBoard[startX][startY].type = EMPTY;
}

_Bool pawnCanEat(Column startX, int startY, Column endX, int endY) {
    if (!(abs(endY - startY) == 1 && abs(endX - startX) == 1)) {
        return FALSE;
    }

    return TRUE;
}

_Bool pawnCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (canEnPassantCapture(pieceBoard, startX, startY, endY)) {
        pawnEatWithEnPassant(pieceBoard, startX, startY, endX, endY, player);
        return TRUE;
    }

    if (pieceIsEatable(pieceBoard, endX, endY, player)) {
        if (pawnCanEat(startX, startY, endX, endY)) {
            pieceEat(pieceBoard, endX, endY);
            return TRUE;
        }
    }

    if (pieceBoard[startX][startY].hasMoved == FALSE) {
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

    if (hubPieceHasNoObstacle(pieceBoard, startX, startY, endX, endY, player) == FALSE) {
        return FALSE;
    }

    if (player == PLAYER2) {
        if (startY - endY == 1 && endY - startY != 0 && endX == startX) {
            return TRUE;
        }
    } else {
        if (startY - endY <= 2 && startY - endY != 0 && endX == startX) {
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
		    if (canPromotePawn(pieceBoard, endY)) {
		        promotePawn(pieceBoard,endX, endY, player);
		    }
		}
    } else {
    	printf("Wrong position, try again from the start!\n");
	}
}

_Bool bishopCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (abs(endX - startX) != abs(endY - startY)) {
    	return FALSE;
    }

    return TRUE;
}

void bishopMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
	if (pieceBoard[startX][startY].type == WHITE_BISHOP || pieceBoard[startX][startY].type == BLACK_BISHOP) {
    	if (bishopCanMove(pieceBoard,startX, startY, endX, endY, player)) {
    	    if (hubPieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player)) {
    	        pieceMove(pieceBoard, startX, startY, endX, endY, player);
    	    }
    	} else {
    	    printf("Wrong position, try again from the start!\n");
    	}
	}
}

_Bool rookCanMove(Column startX, int startY, Column endX, int endY) {
    if (!((startX == endX && startY != endY) || (startY == endY && startX != endX))) {
        return FALSE;
    }

    return TRUE;
}

void rookMove(Column startX, int startY, Column endX, int endY , PieceInBoard **pieceBoard, Player player) {
    if (pieceBoard[startX][startY].type == WHITE_ROOK || pieceBoard[startX][startY].type == BLACK_ROOK) {
        if (rookCanMove(startX, startY, endX, endY)) {
            if (hubPieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player)) {
                if (pieceBoard[startX][startY].hasMoved == FALSE) {
                    pieceChangeState(pieceBoard, startX, startY);
                }
                pieceMove(pieceBoard, startX, startY, endX, endY, player);
            }
        } else {
            printf("Wrong position, try again from the start!\n");
        }
    }
}


_Bool knightCanMove(PieceInBoard **pieceBoard,Column startX, int startY, Column endX, int endY, Player player) {
    if (!(abs(startX - endX) == 2 && abs(startY - endY) == 1 || (abs(startX - endX) == 1 && abs(startY - endY) == 2))) {
        return FALSE;
    }
    return TRUE;
}

void knightMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (pieceBoard[startX][startY].type == WHITE_KNIGHT || pieceBoard[startX][startY].type == BLACK_KNIGHT) {
        if (knightCanMove(pieceBoard,startX, startY,endX, endY, player)) {
            if (hubPieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player)) {
                pieceMove(pieceBoard,startX, startY,endX, endY, player);
            }
        } else {
            printf("Wrong position, try again from the start!\n");
        }
    }
}

_Bool queenCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (!(rookCanMove(startX, startY, endX, endY) || bishopCanMove(pieceBoard, startX, startY, endX, endY, player))) {
        return FALSE;
    }
    return TRUE;
}

void queenMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    if (pieceBoard[startX][startY].type == WHITE_QUEEN || pieceBoard[startX][startY].type == BLACK_QUEEN) {
        if (queenCanMove(pieceBoard,startX, startY,endX, endY, player)) {
            if (hubPieceHasNoObstacle(pieceBoard,startX, startY,endX, endY, player)) {
                pieceMove(pieceBoard,startX, startY,endX, endY, player);
            }
        } else {
            printf("Wrong position, try again from the start!\n");
        }
    }
}

_Bool kingCanMove(PieceInBoard **pieceBoard,Column startX, int startY, Column endX, int endY, Player player) {
    if (abs(endX - startX) != 1 && abs(endY - startY) != 1 || abs(endX - startX) != 0 && abs(endY - startY) != 0) {
     	return FALSE;
    }

    return TRUE;
}

void kingMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
  	if (pieceBoard[startX][startY].type == WHITE_KING || pieceBoard[startX][startY].type == BLACK_KING) {
        if (kingCanMove(pieceBoard,startX, startY, endX, endY, player)) {
            if (hubPieceHasNoObstacle(pieceBoard,startX,startY,endX,endY, player)) {
                if (pieceBoard[startX][startY].hasMoved == FALSE) {
                    pieceChangeState(pieceBoard, startX, startY);
                }
                pieceMove(pieceBoard, startX, startY, endX, endY, player);
            }
        } else {
            printf("Wrong position, try again from the start!\n");
        }
    }
}

void hubPieceIsPlaying(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
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
            queenMove(pieceBoard, startX, startY, endX, endY, player);
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

_Bool pieceCanEatKing(PieceInBoard **pieceBoard, Player player) {
    Position kingPos = kingIsHere(pieceBoard, player);
    Column kingCurrentPosX = kingPos.x;
    int kingCurrentPosY = kingPos.y;
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {
            if (player == PLAYER1 && definePieceTeam(pieceBoard, col, row) == WHITE_TEAM && definePieceTeam(pieceBoard, col, row) != NO_TEAM) {
                if (hubPieceCanEatKing(pieceBoard, col, row, kingCurrentPosX, kingCurrentPosY, player) == TRUE) {
                    if (hubPieceHasNoObstacle(pieceBoard, col, row, kingCurrentPosX, kingCurrentPosY, player)) {
                        return TRUE;
                    }
                }
            } else if (player == PLAYER2 && definePieceTeam(pieceBoard, col, row) == BLACK_TEAM && definePieceTeam(pieceBoard, col, row) != NO_TEAM) {
                if (hubPieceCanEatKing(pieceBoard, col, row, kingCurrentPosX, kingCurrentPosY, player) == TRUE) {
                    if (hubPieceHasNoObstacle(pieceBoard, col, row, kingCurrentPosX, kingCurrentPosY, player)) {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

void displayIfInChest(PieceInBoard **pieceBoard,Player player) {
    if (pieceCanEatKing(pieceBoard, player)) {
        if (player == PLAYER1) {
            printf("Player 2 ! in Chess \n");
            printf("You have to move your King\n");
        } else {
            printf("Player 1 ! in Chess \n");
            printf("You have to move your King\n");
        }
    }
}

_Bool hubPieceCanEatKing(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    switch (pieceBoard[startX][startY].type) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            if (pawnCanEat(startX, startY,endX, endY)) {
                return TRUE;
            }
            return FALSE;

        case WHITE_KING:
        case BLACK_KING:
            return FALSE;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (bishopCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }
            return FALSE;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            if (queenCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }
            return FALSE;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if (knightCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }
        return FALSE;

        case WHITE_ROOK:
        case BLACK_ROOK:
                if (rookCanMove(startX, startY, endX, endY)) {
                    return TRUE;
            }
        return FALSE;

        case EMPTY:
            return FALSE;

        default:
            printf("You have to be a piece for try to eat the KING.\n");
            return FALSE;
    }
}

_Bool hubPieceCanMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY, Player player) {
    switch (pieceBoard[startX][startY].type) {
        case WHITE_PAWN:
        case BLACK_PAWN:
            if (pawnCanMove(pieceBoard, startX, startY,endX, endY, player)) {
                return TRUE;
            }

        return FALSE;

        case WHITE_KING:
        case BLACK_KING:
            if (kingCanMove(pieceBoard, startX, startY,endX, endY, player)) {
                return TRUE;
            }
        return FALSE;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            if (bishopCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }
        return FALSE;

        case WHITE_QUEEN:
        case BLACK_QUEEN:
            if (queenCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }

            return FALSE;

        case WHITE_KNIGHT:
        case BLACK_KNIGHT:
            if (knightCanMove(pieceBoard, startX, startY, endX, endY,player)) {
                return TRUE;
            }

        return FALSE;

        case WHITE_ROOK:
        case BLACK_ROOK:
            if (rookCanMove(startX, startY, endX, endY)) {
                return TRUE;
            }

        return FALSE;

        case EMPTY:
            return FALSE;

        default:
            printf("Wrong piece\n");
        return FALSE;
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
        if (startX - 1 >= 0 && startX - 1 <= 8) {
            if (startX - 1 < 1) {
                if (pieceBoard[startX - 1][startY].type == WHITE_PAWN) {
                    return TRUE;
                }
            } else {
                return FALSE;
            }
        } else if (startX + 1 > 7) {
            if (pieceBoard[startX + 1][startY].type == WHITE_PAWN) {
                return TRUE;
            }
        } else {
            return FALSE;
        }

        return FALSE;
    }

    if (resultBlack == 2 && resultWhite == 1) {
        if (startX - 1 >= 0 && startX - 1 <= 8) {
            if (startX - 1 < 1) {
                if (pieceBoard[startX - 1][startY].type == BLACK_PAWN) {
                    return TRUE;
                }
            } else {
                return FALSE;
            }
        } else if (startX + 1 > 7) {
            if (pieceBoard[startX + 1][startY].type == BLACK_PAWN) {
                return TRUE;
            }
        } else {
            return FALSE;
        }
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

char * defineAnswerCastling() {
    char * answer = malloc (3 * sizeof(char));
    while (strcmp(answer, "YES") != 0) {
        printf("You can castling your King with the near Rook. Do you want castling ? yes or no : \n");
        scanf(" %3s", answer);
        uppercase(answer);
        if (strcmp(answer, "NO") == 0) {
            return answer;
        }
    }
    return answer;
}

_Bool canCastling(PieceInBoard **pieceBoard, Column startX, int startY, Player player) {
    if (pieceCanEatKing(pieceBoard, player) == TRUE) {
        return FALSE;
    }

    if (player == PLAYER1) {
        if (pieceBoard[4][0].type != WHITE_KING && pieceBoard[4][0].hasMoved == TRUE) {
            return FALSE;
        }

        if (pieceBoard[0][0].type == WHITE_ROOK && pieceBoard[0][0].hasMoved == TRUE && pieceBoard[7][0].type == WHITE_ROOK && pieceBoard[7][0].hasMoved == TRUE) {
            return FALSE;
        }

        if (pieceBoard[0][0].type == WHITE_ROOK && pieceBoard[0][0].hasMoved == FALSE && pieceBoard[1][0].type == EMPTY && pieceBoard[2][0].type == EMPTY && pieceBoard[3][0].type == EMPTY && ((startX == 0 && startY == 0) || (startX == 4 && startY == 0))) {
                return TRUE;
        }

        if (pieceBoard[7][0].type == WHITE_ROOK && pieceBoard[7][0].hasMoved == FALSE && pieceBoard[6][0].type == EMPTY && pieceBoard[5][0].type == EMPTY && ((startX == 7 && startY == 0) || (startX == 4 && startY == 0))) {
                return TRUE;
        }

        return FALSE;
    }

    if (player == PLAYER2) {
        if (pieceBoard[4][7].type != BLACK_KING && pieceBoard[4][7].hasMoved == TRUE) {
            return FALSE;
        }

        if (pieceBoard[7][7].type == BLACK_ROOK && pieceBoard[7][7].hasMoved == TRUE && pieceBoard[0][7].type == BLACK_ROOK && pieceBoard[0][7].hasMoved == TRUE) {
            return FALSE;
        }

        if (pieceBoard[0][7].type == BLACK_ROOK && pieceBoard[0][7].hasMoved == FALSE && pieceBoard[1][7].type == EMPTY && pieceBoard[2][7].type == EMPTY && pieceBoard[3][7].type == EMPTY &&((startX == 0 && startY == 7) || (startX == 4 && startY == 7))) {
                return TRUE;
        }

        if (pieceBoard[7][7].type == BLACK_ROOK && pieceBoard[7][7].hasMoved == FALSE && pieceBoard[6][7].type == EMPTY && pieceBoard[5][7].type == EMPTY && ((startX == 7 && startY == 7) || (startX == 4 && startY == 7))) {
            return TRUE;
        }
    }
    return FALSE;
}

Castling whichCastling(PieceInBoard **pieceBoard, Player player) {
    if (player == PLAYER1) {
        if (pieceBoard[1][0].type == EMPTY && pieceBoard[2][0].type == EMPTY && pieceBoard[3][0].type == EMPTY) {
            return WHITE_QUEEN_SIDE_CASTLING;

        } else if (pieceBoard[6][0].type == EMPTY && pieceBoard[5][0].type == EMPTY) {
            return WHITE_KING_SIDE_CASTLING;

        }
    } else {
        if (pieceBoard[1][7].type == EMPTY && pieceBoard[2][7].type == EMPTY && pieceBoard[3][7].type == EMPTY) {
            return BLACK_QUEEN_SIDE_CASTLING;

        } else if (pieceBoard[6][7].type == EMPTY && pieceBoard[5][7].type == EMPTY) {
            return BLACK_KING_SIDE_CASTLING;
        }
    }
    return NO_SIDE_CASTLING;
}

_Bool decideCastling(PieceInBoard **pieceBoard, Player player) {
    if (whichCastling(pieceBoard, player) == NO_SIDE_CASTLING) {
        return FALSE;
    }
    return TRUE;
}

void castling(PieceInBoard **pieceBoard, Player player) {
    Castling howCastling = whichCastling(pieceBoard, player);
    if (decideCastling(pieceBoard, player)){
        if (howCastling == WHITE_QUEEN_SIDE_CASTLING) {
            pieceBoard[2][0].type = WHITE_KING;
            pieceBoard[2][0].hasMoved = TRUE;
            pieceBoard[3][0].type = WHITE_ROOK;
            pieceBoard[3][0].hasMoved = TRUE;
            pieceBoard[4][0].type = EMPTY;
            pieceBoard[0][0].type = EMPTY;

        } else if (howCastling == WHITE_KING_SIDE_CASTLING) {
            pieceBoard[6][0].type = WHITE_KING;
            pieceBoard[6][0].hasMoved = TRUE;
            pieceBoard[5][0].type = WHITE_ROOK;
            pieceBoard[5][0].hasMoved = TRUE;
            pieceBoard[4][0].type = EMPTY;
            pieceBoard[7][0].type = EMPTY;

        } else if (howCastling == BLACK_QUEEN_SIDE_CASTLING) {
            pieceBoard[2][7].type = BLACK_KING;
            pieceBoard[2][7].hasMoved = TRUE;
            pieceBoard[3][7].type = BLACK_ROOK;
            pieceBoard[3][7].hasMoved = TRUE;
            pieceBoard[4][7].type = EMPTY;
            pieceBoard[0][7].type = EMPTY;

        } else if (howCastling == BLACK_KING_SIDE_CASTLING) {
            pieceBoard[6][7].type = BLACK_KING;
            pieceBoard[6][7].hasMoved = TRUE;
            pieceBoard[5][7].type = BLACK_ROOK;
            pieceBoard[5][7].hasMoved = TRUE;
            pieceBoard[4][7].type = EMPTY;
            pieceBoard[0][7].type = EMPTY;
        }
    }
}