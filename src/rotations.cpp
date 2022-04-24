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

U64 Rotate::flip_diagonally_A8H1(U64 bitboard)  {
    U64 temp_board;
    const U64 k1 = 0x5500550055005500;
    const U64 k2 = 0x3333000033330000;
    const U64 k4 = 0x0f0f0f0f00000000;

    temp_board  = k4 & (bitboard ^ (bitboard << 28));
    bitboard ^= temp_board ^ (temp_board >> 28) ;
    temp_board  = k2 & (bitboard ^ (bitboard << 14));
    bitboard ^= temp_board ^ (temp_board >> 14) ;
    temp_board  = k1 & (bitboard ^ (bitboard << 7));
    bitboard ^= temp_board ^ (temp_board >> 7) ;

    return bitboard;
};

U64 Rotate::flip_diagonally_A1H8(U64 bitboard) {
    U64 temp_board;
    const U64 k1 = 0xaa00aa00aa00aa00;
    const U64 k2 = 0xcccc0000cccc0000;
    const U64 k4 = 0xf0f0f0f00f0f0f0f;

    temp_board  = bitboard ^ (bitboard << 36) ;
    bitboard ^= k4 & (temp_board ^ (bitboard >> 36));
    temp_board  = k2 & (bitboard ^ (bitboard << 18));
    bitboard ^= temp_board ^ (temp_board >> 18) ;
    temp_board  = k1 & (bitboard ^ (bitboard << 9));
    bitboard ^= temp_board ^ (temp_board >> 9) ;

    return bitboard;
};

U64 Rotate::rotate_left(U64 bitboard) {
    return flip_diagonally_A1H8 (flip_vertically (bitboard) );
};

U64 Rotate::rotate_right(U64 bitboard) {
    return flip_vertically (flip_diagonally_A1H8 (bitboard) );
};
