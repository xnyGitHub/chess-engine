#include <iostream>
#include <bitset>
#include <cmath>
#include "../src/constants.h"
#include "../src/utils.h"
#include "../src/board.h"
#define U64 unsigned long long

// Right shift = closer to start
// Left shift = closer to end

enum { white, black };
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

U64 BishopMask[64];
U64 RookMask[64];
U64 QueenMask[64];
U64 BishopAttacks[64][512]; // 256 K
U64 RookAttacks[64][4096]; // 2048K

U64 set_bit(U64 bitboard, int tile) {
    return bitboard | (1ULL << tile);
}

int get_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? 1 : 0;
}

U64 del_bit(U64 bitboard, int tile) {
    return bitboard & (1ULL << tile) ? bitboard ^ (1ULL << tile) : 0;
}

int get_bit_count(U64 bitboard) {
    std::bitset<64> board(bitboard);
    int number = (int) board.count();
    return number;
};

int get_lsb_index(U64 bitboard) {
    return get_bit_count((bitboard & -bitboard)-1);
}

int hash_into_key(U64 blockers, U64 magic, int bit_count) {
    blockers *= magic;
    blockers >>= (64- bit_count);
    return (int) blockers;
}

U64 generate_pawn_attack_mask(int square, int color){
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // White pawn
    if (!color) {
        attacks =  attacks | (Constants::not_a_bitboard & bitboard) >> 9;
        attacks =  attacks | (Constants::not_h_bitboard & bitboard) >> 7;
    } else {
        attacks = attacks | (Constants::not_a_bitboard & bitboard) << 7;
        attacks = attacks | (Constants::not_h_bitboard & bitboard) << 9;
    }
    return attacks;
}

U64 generate_knight_attack_mask(int square){
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Top- left
    attacks =  attacks | (Constants::not_a_bitboard & bitboard) >> 17;
    attacks =  attacks | (Constants::not_ab_bitboard & bitboard) >> 10;
    // Top right
    attacks =  attacks | (Constants::not_gh_bitboard & bitboard) >> 6;
    attacks =  attacks | (Constants::not_h_bitboard & bitboard) >> 15;
    // Bottom-left
    attacks =  attacks | (Constants::not_ab_bitboard & bitboard) << 6;
    attacks =  attacks | (Constants::not_a_bitboard & bitboard) << 15;
    // Bottom-right
    attacks =  attacks | (Constants::not_gh_bitboard & bitboard) << 10;
    attacks =  attacks | (Constants::not_h_bitboard & bitboard) << 17;

    return attacks;
}

U64 generate_king_attack_mask(int square){
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    bitboard = set_bit(bitboard, square);

    // Right shifts
    attacks =  attacks | (Constants::not_a_bitboard & bitboard) >> 9;
    attacks =  attacks | bitboard >> 8;
    attacks =  attacks | (Constants::not_h_bitboard & bitboard) >> 7;
    attacks =  attacks | (Constants::not_a_bitboard & bitboard) >> 1;
    // Left shifts
    attacks =  attacks | (Constants::not_h_bitboard & bitboard) << 1;
    attacks =  attacks | (Constants::not_a_bitboard & bitboard) << 7;
    attacks =  attacks | bitboard << 8;
    attacks =  attacks | (Constants::not_h_bitboard & bitboard) << 9;

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

        BishopMask[square] = attacks;
        QueenMask[square] |= attacks;
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

        RookMask[square] = attacks;
        QueenMask[square] |= attacks;
    }

}

U64 get_permutation(U64 attack_mask, int permutation) {
    U64 board = 0ULL;
    int number_of_bits_in_mask = get_bit_count(attack_mask);

    for (int count = 0; count < number_of_bits_in_mask; count++) {
        int bit_index = get_lsb_index(attack_mask);
        attack_mask  = del_bit(attack_mask,bit_index);
        if (permutation & (1 << count)) {
            board |= (1ULL << bit_index);
        }
    }
    return board;
}

U64 get_bishop_attack(U64 blockers, board_tiles square) {
    blockers &= BishopMask[square];
    blockers *= Constants::BishopMagic[square];
    blockers >>= (64- get_bit_count(BishopMask[square]));
    return BishopAttacks[square][blockers];
}

U64 get_rook_attack(U64 blockers, board_tiles square) {
    blockers &= RookMask[square];
    blockers *= Constants::RookMagic[square];
    blockers >>= (64- get_bit_count(RookMask[square]));
    return RookAttacks[square][blockers];
}

U64 get_queen_move(U64 blocker, int square) {
    U64 rook_board, bishop_board;

    rook_board = blocker & RookMask[square];
    rook_board *= Constants::RookMagic[square];
    rook_board >>= (64- get_bit_count(RookMask[square]));
    rook_board = RookAttacks[square][rook_board];

    bishop_board = blocker & BishopMask[square];
    bishop_board *= Constants::BishopMagic[square];
    bishop_board >>= (64- get_bit_count(BishopMask[square]));
    bishop_board = BishopAttacks[square][bishop_board];

    return rook_board | bishop_board;
}
void generate_rook_move_permutations() {

    for (int square = 0; square < 64; square ++) {
        U64 mask = RookMask[square];
        int permutations = pow(2,get_bit_count(mask));

        for(int i = 0; i < permutations; i++ ){
            U64 attacks = 0ULL;
            U64 blockers = get_permutation(mask, i);

            int row = square / 8;
            int file = square % 8;
            int r,f;

            // North mask
            for (r = row-1; r>=0; r--) {
                attacks |= (1ULL << (r * 8 +file));
                if ((1ULL << (r * 8 + file)) & blockers) break;
            }

            // East mask
            for (f = file+1; f<=7; f++) {
                attacks |= (1ULL << (row * 8 +f));
                if ((1ULL << (row * 8 + f)) & blockers) break;
            }

            // South mask
            for (r = row+1; r<=7; r++) {
                attacks |= (1ULL << (r * 8 +file));
                if ((1ULL << (r * 8 + file)) & blockers) break;
            }

            // West mask
            for (f = file-1; f>=0; f--) {
                attacks |= (1ULL << (row * 8 +f));
                if ((1ULL << (row * 8 + f)) & blockers) break;
            }

            int key = hash_into_key(blockers,Constants::RookMagic[square],get_bit_count(mask));
            RookAttacks[square][key] = attacks;
        }
    }
}

void generate_bishop_move_permutations() {
    for (int square = 0; square < 64; square ++) {
        U64 mask = BishopMask[square];
        int permutations = pow(2,get_bit_count(mask));

        for(int i = 0; i < permutations; i++ ){
            U64 attacks = 0ULL;
            U64 blockers = get_permutation(mask, i);

            int rank = square / 8;
            int file = square % 8;
            int r,f;

            for (r = rank+1, f = file+1; r <= 7 && f <= 7; r++, f++){
                attacks |= (1ULL << (r * 8 + f));
                if ((1ULL << (r * 8 + f)) & blockers) break;
            }

            for (r = rank-1, f = file+1; r >= 0 && f <= 7; r--, f++){
                attacks |= (1ULL << (r * 8 + f));
                if ((1ULL << (r * 8 + f)) & blockers) break;
            }

            for (r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--){
                attacks |= (1ULL << (r * 8 + f));
                if ((1ULL << (r * 8 + f)) & blockers) break;
            }

            for (r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--){
                attacks |= (1ULL << (r * 8 + f));
                if ((1ULL << (r * 8 + f)) & blockers) break;
            }

            int key = hash_into_key(blockers,Constants::BishopMagic[square],get_bit_count(mask));
            BishopAttacks[square][key] = attacks;
        }
    }
}


int main() {
    generate_bishop_rays();
    generate_rook_rays();
    generate_bishop_move_permutations();
    generate_rook_move_permutations();

    U64 blockers = RookMask[b5];
    U64 move = get_queen_move(blockers,e3);

    Utils::print_bitboard(blockers);
    Utils::print_bitboard(move);

    Board board;
    U64 black_board = board.get_black_board();
    U64 white_board = board.get_white_board();
    Utils::print_bitboard(black_board);
    Utils::print_bitboard(white_board);
    Utils::print_bitboard(board.get_board());
    return 0;
}