#include <iostream>
#include <sstream>
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

U64 Utils::parse_fen(std::string fen_string){

    std::istringstream streamed_string(fen_string);
    std::string stream_string;
    streamed_string >> stream_string;

    int position = 0;
    U64 board = 0ULL;
    for (char const character: stream_string){
        switch (character) {
            case 'r': board |= (1ULL << position); position++; break;
            case 'n': board |= (1ULL << position); position++; break;
            case 'b': board |= (1ULL << position); position++; break;
            case 'q': board |= (1ULL << position); position++; break;
            case 'k': board |= (1ULL << position); position++; break;
            case 'p': board |= (1ULL << position); position++; break;
            case '/': break;
            case 'R': board |= (1ULL << position); position++; break;
            case 'N': board |= (1ULL << position); position++; break;
            case 'B': board |= (1ULL << position); position++; break;
            case 'Q': board |= (1ULL << position); position++; break;
            case 'K': board |= (1ULL << position); position++; break;
            case 'P': board |= (1ULL << position); position++; break;
            default : position += character - '0';
        }
    }

    streamed_string >> stream_string;
    std::string player_to_move = stream_string;
    std::cout << player_to_move << " player move \n";

    int wQ = 0;
    int wK = 0;
    int bQ = 0;
    int bK = 0;
    streamed_string >> stream_string;
    if (stream_string != "-") {
        for (char const character: stream_string){
            switch (character) {
                case 'K': wK = 1; break;
                case 'Q': wQ = 1; break;
                case 'k': bK = 1; break;
                case 'q': bK = 1; break;
            }
        }
    }
    streamed_string >> stream_string;
    std::string en_passant_square = stream_string;
    std::cout << en_passant_square << " e.p square  \n";

    streamed_string >> stream_string;
    int half_clock = std::stoi(stream_string);
    std::cout << half_clock << " half  \n";

    streamed_string >> stream_string;
    int full_clock = std::stoi(stream_string);
    std::cout << full_clock << " full  \n";
    return board;

}
