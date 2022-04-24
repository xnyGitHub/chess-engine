
#define U64 unsigned long long
#ifndef BOARD_H
#define BOARD_H
class Board {
public:
    Board();
    U64 get_white_board() const;
    U64 get_black_board() const;
    U64 get_board()       const;
private:
    U64 whitePawns = 0ULL;
    U64 whiteKnights = 0ULL;
    U64 whiteBishops = 0ULL;
    U64 whiteRooks = 0ULL;
    U64 whiteQueens = 0ULL;
    U64 whiteKing = 0ULL;

    U64 blackPawns = 0ULL;
    U64 blackKnights = 0ULL;
    U64 blackBishops = 0ULL;
    U64 blackRooks = 0ULL;
    U64 blackQueens = 0ULL;
    U64 blackKing = 0ULL;
};
#endif //BOARD_H
