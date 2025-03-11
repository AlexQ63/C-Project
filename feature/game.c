#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool canGoNextMove = FALSE;

void uppercase(char *string) {
    int i = 0;

    while (string[i] != '\0') {
        if (string[i]  >= 97 &&  string[i] <= 122)
            string[i] = string[i] - 32;
        i++;
    }
}

Position playerAskPosition() {
    char coordonate[3];
    do {
        printf("Enter Position Column and Row (ex : C5) : ");
        scanf("%2s", coordonate);
        uppercase(coordonate);
        if (strlen(coordonate) != 2) {
            printf("Wrong Input, put another one\n");
        }

    } while (strlen(coordonate) != 2);
    Position pos;
    pos.x = coordonate[0] - 'A';
    pos.y = coordonate[1] - '1';
    return pos;
}

_Bool validMove(PieceInBoard **pieceBoard, Column startX, int startY, Column endX, int endY) {
    if (pieceBoard[startX][startY].type != EMPTY) {
        return FALSE;
    }

    if (pieceBoard[endX][endY].type == EMPTY) {
        return FALSE;
    }
    return TRUE;
}

void playerPlay(Player player, PieceInBoard **pieceBoard) {
    while (canGoNextMove == FALSE) {

        if (player == PLAYER1) {
            printf("Player 1 turn, let's play.\n");
        }
        else if (player == PLAYER2) {
            printf("Player 2 turn, let's play.\n");
        }

        Position start = playerAskPosition();
        Column startX = start.x;
        int startY = start.y;

        while (!positionIsInTheBoard(startX, startY)) {
            printf("Invalid position\n, put another position in A - H and 1 - 8\n");
            start = playerAskPosition();
            startX = start.x;
            startY = start.y;
        }

        while (playerPlayHisPiece(pieceBoard, startX, startY, player) == FALSE) {
            printf("You have to play again. \n");
            start = playerAskPosition();
            startX = start.x;
            startY = start.y;
        }

        while (pieceBoard[startX][startY].type == EMPTY) {
            if (hubPieceCanMove(pieceBoard, startX, startY, startX, startY, player) == FALSE) {
                printf("You can't play this type of piece. You have to select an real piece.\n");
                start = playerAskPosition();
                startX = start.x;
                startY = start.y;
            }
        }

        displayWhichPiece(pieceBoard, startX, startY);

        if (player == PLAYER1 && pieceBoard[startX][startY].type == WHITE_KING || pieceBoard[startX][startY].type == WHITE_ROOK) {
            if (canCastling(pieceBoard, startX, startY, player)) {
                char * answer = defineAnswerCastling();
                if (strcmp(answer, "YES") == 0) {
                    castling(pieceBoard, player);
                    canGoNextMove = TRUE;
                    break;
                } else {
                    free(answer);
                    continue;
                }
            }

        } else if (player == PLAYER2  && pieceBoard[startX][startY].type == BLACK_KING || pieceBoard[startX][startY].type == BLACK_ROOK) {
            if (canCastling(pieceBoard, startX, startY, player)) {
                char * answer = defineAnswerCastling();
                if (strcmp(answer, "YES") == 0) {
                    castling(pieceBoard, player);
                    canGoNextMove = TRUE;
                    break;
                } else {
                    free(answer);
                    return;
                }
            }
        }

        char *answer = defineNextPlay();
        if (strcmp(answer, "no") == 0) {
            printf("You have to play again, from the start. Select the first coordinate : ");
            free(answer);
            return;
        }
        free(answer);
        Position end = playerAskPosition();
        Column endX = end.x;
        int endY = end.y;

        while (!positionIsInTheBoard(startX, startY)) {
            printf("Invalid position\n, put another position in A - H and 1 - 8\n");
            end = playerAskPosition();
            endX = end.x;
            endY = end.y;
        }

        while (playerPlayHisPiece(pieceBoard, startX, startY, player) == FALSE) {
            printf("You have to play again. \n");
            end = playerAskPosition();
            endX = end.x;
            endY = end.y;
        }

        lastPawnMove(startY, endY);

        hubPieceIsPlaying(pieceBoard, startX, startY, endX, endY, player);

        displayIfInChest(pieceBoard, player);
        if (validMove(pieceBoard, startX, startY, endX, endY)) {
            canGoNextMove = TRUE;
        }
    }
}

_Bool blackKingIsAlive(PieceInBoard **board) {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[j][i].type == BLACK_KING) {
                return TRUE;
            }
        }
    }
    deleteBoard(board);
    return FALSE;
}

_Bool whiteKingIsAlive(PieceInBoard **board) {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            if (board[j][i].type == WHITE_KING) {
                return TRUE;
            }
        }
    }
    deleteBoard(board);
    return FALSE;
}

_Bool definePlayerWin(PieceInBoard **pieceBoard) {
    if (blackKingIsAlive(pieceBoard) == FALSE) {
        printf("Player 1 wins\n");
        printf("Congratulation, you are the best\n");
        return FALSE;
    }
    else if (whiteKingIsAlive(pieceBoard) == FALSE) {
        printf("Player 2 wins\n");
        printf("Congratulation, you are the best\n");
        return FALSE;
    }
    return TRUE;
}

_Bool playerBeingStalemate(PieceInBoard **pieceBoard, Player player) {
    static _Bool ableToMove = FALSE;
    for (int row = 7; row >= 0; row--) {
        for (int col = 0; col < 8; col++) {
            Column right = row+1;
            Column left = row-1;
            int up = col+1;
            int down = col-1;
            if (player == PLAYER1 && definePieceTeam(pieceBoard, row, col) == WHITE_TEAM) {
                if (hubPieceCanMove(pieceBoard, col, row, col, right, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, col, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col , row, up, row, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, down, row, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, down, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, down, right, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, up, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, up, right, player)) {
                    ableToMove = TRUE;

                } if (ableToMove == TRUE) {
                    return FALSE;
                }

            } else if (player == PLAYER2 && definePieceTeam(pieceBoard, col, row) == BLACK_TEAM) {
                if (hubPieceCanMove(pieceBoard, col, row, col, right, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, col, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col , row, down, row, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, up, row, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, up, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, down, right, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, down, left, player)) {
                    ableToMove = TRUE;

                } else if (hubPieceCanMove(pieceBoard, col, row, up, right, player)) {
                    ableToMove = TRUE;

                }  if (ableToMove == TRUE) {
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}

void gamePlay() {
    PieceInBoard **board = generateEmptyBoard();
    resetBoardPiece(board);
    displayBoard(board);

    Player p1 = PLAYER1;
    Player p2 = PLAYER2;

    while (definePlayerWin(board)) {
        while (canGoNextMove == FALSE) {
            playerPlay(p1, board);
            displayNewBoard(board);
            if (playerBeingStalemate(board, p1) == TRUE) {
                canGoNextMove = FALSE;
            }
        }
        canGoNextMove = FALSE;
        if (definePlayerWin(board) == FALSE) {
            break;
        }

        while (canGoNextMove == FALSE) {
            playerPlay(p2, board);
            displayNewBoard(board);
            if (playerBeingStalemate(board, p2) == TRUE) {
                canGoNextMove = FALSE;
            }
        }
        canGoNextMove = FALSE;
    }
}