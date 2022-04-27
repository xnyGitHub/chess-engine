#ifndef MOVE_H
#define MOVE_H
#include <string>

class Move {
public:
    // Constructor
    Move(unsigned int start, unsigned int stop, unsigned int flags);

    // Getters
    unsigned int get_start();
    unsigned int get_stop();
    unsigned int get_flags();
    std::string get_string_move();

    // Flags to identify move type
    enum flag {
        quiet,
        double_pawn_push,
        king_castle,
        queen_castle,
        captures,
        ep_capture,
        knight_promotion,
        bishop_promotion,
        rook_promotion,
        queen_promotion,
        knight_promotion_capture,
        bishop_promotion_capture,
        rook_promotion_capture,
        queen_promotion_capture,
    };
private:
    // The move
    unsigned int _move;

    // Constants to convert move bits to string
    const static char RANKS[8];
    const static char FILES[8];
};

#endif //MOVE_H
