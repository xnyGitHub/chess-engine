# include "../src/rotations.h"

U64 Rotate::flip_vertically(U64 bitboard) {
    const U64 k1 = 0x00FF00FF00FF00FF;
    const U64 k2 = 0x0000FFFF0000FFFF;

    bitboard = ((bitboard >>  8) & k1) | ((bitboard & k1) <<  8);
    bitboard = ((bitboard >> 16) & k2) | ((bitboard & k2) << 16);
    bitboard = ( bitboard >> 32)       | ( bitboard       << 32);
    return bitboard;
};

U64 Rotate::flip_horizontally(U64 bitboard) {
    const U64 k1 = 0x5555555555555555;
    const U64 k2 = 0x3333333333333333;
    const U64 k4 = 0x0f0f0f0f0f0f0f0f;

    bitboard = ((bitboard >> 1) & k1) | ((bitboard & k1) << 1);
    bitboard = ((bitboard >> 2) & k2) | ((bitboard & k2) << 2);
    bitboard = ((bitboard >> 4) & k4) | ((bitboard & k4) << 4);
    return bitboard;
};

U64 Rotate::flip_diagonally_A1H8(unsigned long long bitboard)  {return 0ULL;};

U64 Rotate::flip_diagonally_A8H1(unsigned long long bitboard) {return 0ULL;};

U64 Rotate::rotate_left(unsigned long long bitboard) {return 0ULL;};

U64 Rotate::rotate_right(unsigned long long bitboard) {return 0ULL;};
