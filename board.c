#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*// fonction qui va me permettre d'effacer les /n et les retours "ctrl+D" (stdin) des scanf que j'utilise.
void clearBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}*/

void deleteBoard(PieceInBoard **board) {
    // Free all row before board
    for (int y = 0; y < 8; y++) {
        free(board[y]);
        board[y] = NULL;
    }
    free(board);
    board = NULL;
}

void placePiece(PieceInBoard **board, Column x, int y, Piece piece) {
    board[x - 1][y - 1].type = piece;
}

char columnToString(Column column) {
    switch (column) {
        case A:
            return 'a';
        case B:
            return 'b';
        case C:
            return 'c';
        case D:
            return 'd';
        case E:
            return 'e';
        case F:
            return 'f';
        case G:
            return 'g';
        case H:
            return 'h';
        default:
            return '.';
    }
}

void displayBoard(PieceInBoard **board) {
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int i = 7; i >= 0; i--) {
        printf("%d |", i + 1);

        for (int j = 0; j < 8; j++) {
            printf("%c | ", pieceToString(board[j][i].type));
        }

        printf("\n  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    A   B   C   D   E   F   G   H\n");
}

void resetBoardPiece(PieceInBoard **board) {
    // Just placing at right position all pieces
    for (Column i = A; i <= H; i++) {
        placePiece(board, i, 7, BLACK_PAWN);
        placePiece(board, i, 2, WHITE_PAWN);
    }

    placePiece(board, A, 1, WHITE_ROOK);
    placePiece(board, H, 1, WHITE_ROOK);
    placePiece(board, A, 8, BLACK_ROOK);
    placePiece(board, H, 8, BLACK_ROOK);

    placePiece(board, B, 1, WHITE_KNIGHT);
    placePiece(board, G, 1, WHITE_KNIGHT);

    placePiece(board, B, 8, BLACK_KNIGHT);
    placePiece(board, G, 8, BLACK_KNIGHT);

    placePiece(board, C, 8, BLACK_BISHOP);
    placePiece(board, F, 8, BLACK_BISHOP);
    placePiece(board, C, 1, WHITE_BISHOP);
    placePiece(board, F, 1, WHITE_BISHOP);

    placePiece(board, D, 8, BLACK_QUEEN);
    placePiece(board, E, 8, BLACK_KING);
    placePiece(board, D, 1, WHITE_QUEEN);
    placePiece(board, E, 1, WHITE_KING);
}

PieceInBoard **generateEmptyBoard() {
    PieceInBoard **board = malloc(sizeof(PieceInBoard *) * 8);
    for (int i = 0; i < 8; i++) {
        PieceInBoard *row = malloc(sizeof(PieceInBoard) * 8);
        for (int j = 0; j < 8; j++) {
            row[j].type = EMPTY;
            row[j].hasMoved = FALSE;
            row[j].isAlive = TRUE;
        }
        board[i] = row;
    }
    return board;
}

void displayNewBoard(PieceInBoard **board) {
    printf("  +---+---+---+---+---+---+---+---+\n");

    for (int i = 7; i >= 0; i--) {
        printf("%d |", i + 1);

        for (int j = 0; j < 8; j++) {
            printf("%c | ", pieceToString(board[j][i].type));
        }

        printf("\n  +---+---+---+---+---+---+---+---+\n");
    }
    printf("    A   B   C   D   E   F   G   H\n");
}

_Bool positionIsInTheBoard(Column x, int y) {
    if (x < A - 1 || x > H - 1) {
        printf("x = %c is out of range\n", x);
        return FALSE;
    }

    if (y < 0 || y > 7) {
        printf("y = %d is out of range\n", y);
        return FALSE;
    }

    return TRUE;
}

void displayWhichPiece(PieceInBoard **pieceBoard, Column x, int y) {
    switch (pieceBoard[x][y].type) {
        case WHITE_PAWN:
            printf("You have select : WHITE_PAWN \n");
        break;

        case WHITE_KING:
            printf("You have select : WHITE_KING \n");
        break;

        case WHITE_QUEEN:
            printf("You have select : WHITE_QUEEN \n");
        break;

        case WHITE_BISHOP:
            printf("You have select : WHITE_BISHOP \n");
        break;

        case WHITE_KNIGHT:
            printf("You have select : WHITE_KNIGHT \n");
        break;

        case WHITE_ROOK:
            printf("You have select : WHITE_ROOK \n");
        break;

        case BLACK_PAWN:
            printf("You have select : BLACK_PAWN \n");
        break;

        case BLACK_KING:
            printf("You have select : BLACK_KING \n");
        break;

        case BLACK_QUEEN:
            printf("You have select : BLACK_QUEEN \n");
        break;
        case BLACK_BISHOP:
            printf("You have select : BLACK_BISHOP \n");
        break;

        case BLACK_KNIGHT:
            printf("You have select : BLACK_KNIGHT \n");
        break;

        case BLACK_ROOK:
            printf("You have select : BLACK_ROOK \n");
        break;

        default:
            printf("You have select : NOTHING \n");
        break;
        //TODO faire une vrai gestion d'erreur ici, car on peut selectionner NOTHING et jouer avec.
    }
}

Position kingIsHere(PieceInBoard **pieceBoard, Player player) {
    Position whiteKingPos;
    Position blackKingPos;
    if (player == PLAYER2){
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                if (pieceBoard[j][i].type == WHITE_KING) {
                    whiteKingPos.x = j;
                    whiteKingPos.y = i;
                    return whiteKingPos;
                }
           }
        }
    } else if (player == PLAYER1) {
        for (int i = 7; i >= 0; i--) {
            for (int j = 0; j < 8; j++) {
                if (pieceBoard[j][i].type == BLACK_KING) {
                    blackKingPos.x = j;
                    blackKingPos.y = i;
                    return blackKingPos;
                }
            }
        }
    }
}