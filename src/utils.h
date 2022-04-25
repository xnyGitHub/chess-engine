#ifndef TEST_PROJECT_UTILS_H
#define TEST_PROJECT_UTILS_H
#define U64 unsigned long long
class Utils {
public:
    static void print_bitboard(U64 bitboard);
    static void print_two_bitboard(U64 blocker, U64 attack, int square);
    static U64 parse_fen(std::string fen_string);
};
#endif //TEST_PROJECT_UTILS_H
