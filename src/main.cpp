#include <iostream>
#include <bitset>
#include "../src/magic_constants.h"
#define U64 unsigned long long

// Right shift = closer to start
// Left shift = closer to end
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

U64 bishop_mask[64];
U64 rook_mask[64];
U64 queen_mask[64];

const U64 not_a_bitboard = 18374403900871474942ULL;
const U64 not_h_bitboard = 9187201950435737471ULL;
const U64 not_ab_bitboard = 18229723555195321596ULL;
const U64 not_gh_bitboard = 4557430888798830399ULL;

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

    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // White pawn
    if (!color) {
        attacks =  attacks | (not_a_bitboard & bitboard) >> 9;
        attacks =  attacks | (not_h_bitboard & bitboard) >> 7;
    } else {
        attacks = attacks | (not_a_bitboard & bitboard) << 7;
        attacks = attacks | (not_h_bitboard & bitboard) << 9;
    }
    return attacks;
}

U64 generate_knight_attack_mask(int square, int color){
    // Knight movements from Top left -> Bottom right
    // 17,15 ,10 ,6, -6, -10, -15, -17


    // White pawn
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Top- left
    attacks =  attacks | (not_a_bitboard & bitboard) >> 17;
    attacks =  attacks | (not_ab_bitboard & bitboard) >> 10;
    // Top right
    attacks =  attacks | (not_gh_bitboard & bitboard) >> 6;
    attacks =  attacks | (not_h_bitboard & bitboard) >> 15;
    // Bottom-left
    attacks =  attacks | (not_ab_bitboard & bitboard) << 6;
    attacks =  attacks | (not_a_bitboard & bitboard) << 15;
    // Bottom-right
    attacks =  attacks | (not_gh_bitboard & bitboard) << 10;
    attacks =  attacks | (not_h_bitboard & bitboard) << 17;

    return attacks;
}

U64 generate_king_attack_mask(int square, int color){
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Right shifts
    attacks =  attacks | (not_a_bitboard & bitboard) >> 9;
    attacks =  attacks | bitboard >> 8;
    attacks =  attacks | (not_h_bitboard & bitboard) >> 7;
    attacks =  attacks | (not_a_bitboard & bitboard) >> 1;

    attacks =  attacks | (not_h_bitboard & bitboard) << 1;
    attacks =  attacks | (not_a_bitboard & bitboard) << 7;
    attacks =  attacks | bitboard << 8;
    attacks =  attacks | (not_h_bitboard & bitboard) << 9;

    return attacks;
}

void generate_bishop_rays() {
    // Loop through all the tiles
    for (int square = 0; square < 64; square++) {
        U64 attacks = 0ULL;

        int trow = square / 8;
        int tfile = square % 8;
        int row,file;

        // South-East mask
        for (row = trow+1, file = tfile +1; row<=6 && file <= 6; row++, file++) attacks |= (1ULL << (row * 8 +file));
        // South-West mask
        for (row = trow+1, file = tfile -1; row<=6 && file >= 1; row++, file--) attacks |= (1ULL << (row * 8 +file));
        // North-West mask
        for (row = trow-1, file = tfile -1; row>=1 && file >= 1; row--, file--) attacks |= (1ULL << (row * 8 +file));
        // North-East mask
        for (row = trow-1, file = tfile +1; row>=1 && file <= 6; row--, file++) attacks |= (1ULL << (row * 8 +file));
        bishop_mask[square] = attacks;
        queen_mask[square] |= attacks;
    }

}

void generate_rook_rays() {
    // Loop through all the tiles
    for (int square = 0; square < 64; square++) {
        U64 attacks = 0ULL;

        int actual_row = square / 8;
        int actual_file = square % 8;
        int row,file;

        // North mask
        for (row = actual_row-1; row>=1; row--) attacks |= (1ULL << (row * 8 +actual_file));

        // East mask
        for (file = actual_file+1; file<=6; file++) attacks |= (1ULL << (actual_row * 8 +file));

        // South mask
        for (row = actual_row+1; row<=6; row++) attacks |= (1ULL << (row * 8 +actual_file));
        // West mask

        for (file = actual_file-1; file>=1; file--) attacks |= (1ULL << (actual_row * 8 +file));

        rook_mask[square] = attacks;
        queen_mask[square] |= attacks;
    }

}

U64 BishopAttacks[64][512]; // 256 K
U64 RookAttacks  [64][4096]; // 2048K

int get_bit_count(U64 bitboard) {
    std::bitset<64> board(bitboard);
    int number = board.count();
    return number;

};
void generate_rook_move_permutations() {

}

void generate_bishop_move_permutations() {

}

int main() {
    U64 new_bitboard = 0ULL;
    generate_bishop_rays();
    generate_rook_rays();
//    new_bitboard = generate_king_attack_mask(h8,  white);
//    print_bitboard(new_bitboard);
    print_bitboard(MagicConstants::bishop_magic[0]);
    print_bitboard(rook_mask[0]);
    return 0;
}