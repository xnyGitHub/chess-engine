#include <iostream>
#define U64 unsigned long long

enum board_tiles {
    a8,b8,c8,d8,e8,f8,g8,h8,
    a7,b7,c7,d7,e7,f7,g7,h7,
    a6,b6,c6,d6,e6,f6,g6,h6,
    a5,b5,c5,d5,e5,f5,g5,h5,
    a4,b4,c4,d4,e4,f4,g4,h4,
    a3,b3,c3,d3,e3,f3,g3,h3,
    a2,b2,c2,d2,e2,f2,g2,h2,
    a1,b1,c1,d1,e1,f1,g1,h1,
    };

enum { white, black };

const U64 not_a_bitboard = 18374403900871474942ULL;
/*
8  0 1 1 1 1 1 1 1
7  0 1 1 1 1 1 1 1
6  0 1 1 1 1 1 1 1
5  0 1 1 1 1 1 1 1
4  0 1 1 1 1 1 1 1
3  0 1 1 1 1 1 1 1
2  0 1 1 1 1 1 1 1
1  0 1 1 1 1 1 1 1

   a b c d e f g h
 */

const U64 not_h_bitboard = 9187201950435737471ULL;
/*
8  1 1 1 1 1 1 1 0
7  1 1 1 1 1 1 1 0
6  1 1 1 1 1 1 1 0
5  1 1 1 1 1 1 1 0
4  1 1 1 1 1 1 1 0
3  1 1 1 1 1 1 1 0
2  1 1 1 1 1 1 1 0
1  1 1 1 1 1 1 1 0
   a b c d e f g h

 */
void print_bitboard(U64 bitboard) {
    for (int rank = 0; rank < 8; rank++){
        std::cout << -(rank-8) << "  ";
        for (int file = 0; file < 8; file++){
            int square  = rank * 8 + file;
            int check = (bitboard & (1ULL << square) ) ? 1:0 ;
            std::cout << check << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h" << "\n\n";
}

U64 set_bit(U64 bitboard, int tile) {
    return bitboard | (1ULL << tile);
}

int get_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? 1 : 0;
}

U64 del_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? bitboard ^ (1ULL << tile) : 0;
}

U64 generate_pawn_attack_mask(int square, int color){
    // Important constants


    // White pawn
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);
    if (!color) {
        attacks =  attacks | (not_a_bitboard & bitboard) >> 9;
        attacks =  attacks | (not_h_bitboard & bitboard) >> 7;
    } else {
        attacks = attacks | (not_a_bitboard & bitboard) << 7;
        attacks = attacks | (not_h_bitboard & bitboard) << 9;
    }
    return attacks;
}
int main() {
    U64 new_bitboard = 0ULL;
    new_bitboard = generate_pawn_attack_mask(h8,  black);
    print_bitboard(new_bitboard);
    return 0;
}