#define U64 unsigned long long

#include <iostream>
#include "../src/board.h"
enum board_tiles {
    a8,b8,c8,d8,e8,f8,g8,h8,
    a7,b7,c7,d7,e7,f7,g7,h7,
    a6,b6,c6,d6,e6,f6,g6,h6,
    a5,b5,c5,d5,e5,f5,g5,h5,
    a4,b4,c4,d4,e4,f4,g4,h4,
    a3,b3,c3,d3,e3,f3,g3,h3,
    a2,b2,c2,d2,e2,f2,g2,h2,
    a1,b1,c1,d1,e1,f1,g1,h1
};

Board::Board() {
    blackRooks   |= (1ULL << a8);
    blackRooks   |= (1ULL << h8);
    blackKnights |= (1ULL << b8);
    blackKnights |= (1ULL << g8);
    blackBishops |= (1ULL << c8);
    blackBishops |= (1ULL << f8);
    blackQueens  |= (1ULL << d8);
    blackKing    |= (1ULL << e8);

    for (int i = 8; i < 16; i++){
        blackPawns |= (1ULL << i);
    }

    whiteRooks   |= (1ULL << a1);
    whiteRooks   |= (1ULL << h1);
    whiteKnights |= (1ULL << b1);
    whiteKnights |= (1ULL << g1);
    whiteBishops |= (1ULL << c1);
    whiteBishops |= (1ULL << f1);
    whiteQueens  |= (1ULL << d1);
    whiteKing    |= (1ULL << e1);

    for (int i = 48; i < 56; i++){
        whitePawns |= (1ULL << i);
    }
};

U64 Board::get_black_board() const {
    return blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;
}

U64 Board::get_white_board() const {
    return whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
}

U64 Board::get_board() const {
    return get_white_board() | get_black_board();
}
