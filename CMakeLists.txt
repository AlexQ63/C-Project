cmake_minimum_required(VERSION 3.30)
project(C-Project C)

set(CMAKE_C_STANDARD 11)

add_executable(C-Project
        player.c
        player.h
        pieceMove.c
        pieceMove.h
        main.c
        board.c
        board.h
        piece.c
        piece.h
)
