#include "board.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*// fonction qui va me permettre d'effacer les /n et les retours "ctrl+D" (stdin) des scanf que j'utilise.
void clearBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF)
    {
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

void **displayNewBoard(PieceInBoard ** board) {
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
        //TODO faire une vrai gestion d'erreur ici, car on peut selectionner NOTHING et jouer avec.
    }
}

_Bool positionIsInTheBoard(Column x, int y) {
    if (!( A - 1 <= x && x <= H - 1)) {
        printf("x = %c est hors limites\n", x);
        return FALSE;
    }

    if (!(0 <= y && y <= 7)) {
        printf("y = %d est hors limites\n", y);
        return FALSE;
    }

    return TRUE;
}

void uppercase(char *string){
    int i = 0;

    while (string[i] != '\0')
    {
        if (string[i]  >= 97 &&  string[i] <= 122)
            string[i] = string[i] - 32;
        i++;
    }
}

Position playerAskPosition() {
    char coordonate[3];
    printf("Enter Position Column and Row (ex : C5) : ");
    scanf("%2s", coordonate);
    uppercase(coordonate);
    /*clearBuffer();*/
    Position pos;
    pos.x = coordonate[0] - 'A';
    pos.y = coordonate[1] - '1';
    return pos;
}

void playerPlay(Player player, PieceInBoard **pieceBoard) {
    if (player == PLAYER1) {
        printf("Player 1 turn, let's play.\n");
    }
    else if (player == PLAYER2) {
        printf("Player 2 turn, let's play.\n");
    }

    Position start = playerAskPosition();
    Column startX = start.x;
    int startY = start.y;

    if (positionIsInTheBoard(startX, startY)) {
        if (playerPlayHisPiece(pieceBoard, startX, startY, player) == FALSE) {
            printf("You have to play again. \n");
            // Voir pour reset le start.x et le start.y car cela fait planter le programme.
            playerPlay(player, pieceBoard);
        }
        displayWhichPiece(pieceBoard, startX, startY);
    }

    else {
        printf("Invalid position\n, put another position in A - H and 1 - 8");
        if (player == PLAYER1 || player == PLAYER2) {
            playerPlay(player, pieceBoard);
        }
        else {
            printf("You only can be the Player 1 or the Player 2");
            return;
        }
    }
    char *answer = defineNextPlay();
    if (strcmp(answer, "no") == 0) {
        printf("You have to play again, from the start. Select the first coordinate : ");
        playerPlay(player, pieceBoard);
    }
    free(answer);
    Position end = playerAskPosition();
    Column endX = end.x;
    int endY = end.y;

    pieceIsPlaying(pieceBoard, startX, startY, endX, endY, player);
}

