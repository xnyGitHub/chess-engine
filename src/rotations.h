#ifndef TEST_PROJECT_ROTATIONS_H
#define TEST_PROJECT_ROTATIONS_H
#define U64 unsigned long long

class Rotate {
public:
    static U64 flip_vertically(U64 bitboard);
    static U64 flip_horizontally(U64 bitboard);
    static U64 flip_diagonally_A1H8(U64 bitboard);
    static U64 flip_diagonally_A8H1(U64 bitboard);
    static U64 rotate_left(U64 bitboard);
    static U64 rotate_right(U64 bitboard);
};
#endif //TEST_PROJECT_ROTATIONS_H
