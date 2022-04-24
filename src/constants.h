#ifndef MAGIC_CONSTANTS_H
#define MAGIC_CONSTANTS_H
#define U64 unsigned long long
#include<string>
class Constants {
public:
    static const U64 RookMagic[64];
    static const U64 BishopMagic[64];
    static const int bishop_relevant_bits[64];
    static const int rook_relevant_bits[64];
    static const U64 not_a_bitboard;
    static const U64 not_h_bitboard;
    static const U64 not_ab_bitboard;
    static const U64 not_gh_bitboard;
    static const std::string square_tiles[64];
};
#endif
