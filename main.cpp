#include <iostream>
void print_bitboard(int bitboard[]) {
    for (int bit = 0; bit < 64; bit++){
        std::cout << bitboard[bit] << " ";
        if ((bit+1) % 8 == 0) {
            std::cout << "\n";
        }
    }
}

void print_bitboard_squares() {
    for (int col = 0; col < 8; col++){
        for (int row = 0; row< 8; row++){
            std::cout << col * 8 + row;
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "First Chess Engine commit" << std::endl;

//  Creating Black bitboard
    int black_king_bitboard [64]   = {};
    int black_queen_bitboard [64]  = {};
    int black_rook_bitboard [64]   = {};
    int black_knight_bitboard [64] = {};
    int black_bishop_bitboard [64] = {};
    int black_pawn_bitboard [64]   = {};

//  Creating White bitboard
    int white_king_bitboard [64]   = {};
    int white_queen_bitboard [64]  = {};
    int white_rook_bitboard [64]   = {};
    int white_knight_bitboard [64] = {};
    int white_bishop_bitboard [64] = {};
    int white_pawn_bitboard [64]   = {};

//  Initialising bitboards
    black_king_bitboard[4]  = 1;
    white_king_bitboard[60] = 1;

    black_queen_bitboard[3]  = 1;
    white_queen_bitboard[59] = 1;


    black_rook_bitboard[0]  = 1;
    black_rook_bitboard[7]  = 1;
    white_rook_bitboard[56] = 1;
    white_rook_bitboard[63] = 1;

    black_knight_bitboard[1]  = 1;
    black_knight_bitboard[6 ] = 1;
    white_knight_bitboard[57] = 1;
    white_knight_bitboard[62] = 1;

    black_bishop_bitboard[2]  = 1;
    black_bishop_bitboard[5]  = 1;
    white_bishop_bitboard[58] = 1;
    white_bishop_bitboard[61] = 1;

    int pawn;
    for (pawn = 8; pawn < 16; pawn++) {
        black_pawn_bitboard[pawn] = 1;
        white_pawn_bitboard[pawn+40] = 1;
    }
    return 0;

}