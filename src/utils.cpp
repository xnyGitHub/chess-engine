#include <iostream>
#include "../src/constants.h"
#include "utils.h"

void Utils::print_bitboard(U64 bitboard) {
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

void Utils::print_two_bitboard(U64 bitboard, U64 second_board, int tile) {
    std::cout << "   blocker            attacks      " << Constants::square_tiles[tile] << "\n";
    for (int rank = 0; rank < 8; rank++){
        std::cout << -(rank-8) << "  ";
        for (int file = 0; file < 8; file++){
            int square  = rank * 8 + file;
            int check = (bitboard & (1ULL << square) ) ? 1:0 ;
            std::cout << check << " ";
        }
        std::cout << "   ";
        for (int file = 0; file < 8; file++){
            int square  = rank * 8 + file;
            int check = (second_board & (1ULL << square) ) ? 1:0 ;
            std::cout << check << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h";
    std::cout << "    a b c d e f g h" << "\n\n";
}