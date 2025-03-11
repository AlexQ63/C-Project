#ifndef PIECE_H
#define PIECE_H

typedef enum {
    EMPTY,
    WHITE_PAWN,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_BISHOP,
    WHITE_KNIGHT,
    WHITE_ROOK,

    BLACK_PAWN,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_BISHOP,
    BLACK_KNIGHT,
    BLACK_ROOK,
} Piece;

typedef enum {
    WHITE_TEAM,
    BLACK_TEAM,
    NO_TEAM
} Team;

char pieceToString(Piece piece);

#endif //PIECE_H