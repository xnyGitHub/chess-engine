#ifndef MAGIC_CONSTANTS_H
#define MAGIC_CONSTANTS_H
#define U64 unsigned long long

class Constants {
public:
    static const U64 rook_magic[64];
    static const U64 bishop_magic[64];
    static const int bishop_relevant_bits[64];
    static const int rook_relevant_bits[64];
};
#endif //TEST_PROJECT_MAGIC_CONSTANTS_H
