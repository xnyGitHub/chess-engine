// Move implementation file
#include "move.h"

const char Move::RANKS[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char Move::FILES[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Move::Move(unsigned int start, unsigned int stop, unsigned int flags) {
    // Each move is represented using 16-bits
    // The first 6-bits(values 0-63) are for representing the start index
    // The next 6-bits(values 0-63) are for representing the end index
    // The last 4-bits(values 0-15) are for flags for the move. e.g Castle, Capture, Promotion etc.
    _move = ((flags & 0xf)<<12) | ((start & 0x3f)<<6) | (stop & 0x3f);
}

unsigned int Move::get_start() {
    // Return the start move index
    return (_move >> 6) & 0x3f;
}

unsigned int Move::get_stop() {
    // Return the end move index
    return _move & 0x3f;
}

unsigned int Move::get_flags() {
    // Return the move flag
    return (_move >> 12) & 0x0f;
}

std::string Move::get_string_move() {
    // Return a string representation of the move
    // To-do
    if (get_flags() == Move::king_castle){
        return "0-0";
    } else if (get_flags() == Move::queen_castle) {
        return "0-0-0";
    }

    std::string move_notation;
    int start = get_start();
    int   end = get_stop();

    if  (get_flags() == Move::quiet){
        return convert_to_fen(start) + convert_to_fen(end);
    } else if  (get_flags() == Move::double_pawn_push){
        return  convert_to_fen(start)+ convert_to_fen(end);
    } else if (get_flags() == Move::captures) {
        return convert_to_fen(start) + 'x' + convert_to_fen(end);
    } else if  (get_flags() == Move::ep_capture){
        return  convert_to_fen(start) + 'x' + convert_to_fen(end) + " e.p";
    } else if  (get_flags() == Move::knight_promotion){
        return  convert_to_fen(end) + "=N";
    } else if  (get_flags() == Move::bishop_promotion){
        return  convert_to_fen(end) + "=B";
    } else if  (get_flags() == Move::rook_promotion){
        return  convert_to_fen(end) + "=R";
    } else if  (get_flags() == Move::queen_promotion){
        return  convert_to_fen(end) + "=Q";
    }  else if  (get_flags() == Move::knight_promotion_capture){
        return  convert_to_fen(end) + "x=N";
    } else if  (get_flags() == Move::bishop_promotion_capture){
        return  convert_to_fen(end) + "x=B";
    } else if  (get_flags() == Move::rook_promotion_capture){
        return  convert_to_fen(end) + "x=R";
    } else if  (get_flags() == Move::queen_promotion_capture){
        return  convert_to_fen(end) + "x=Q";
    }

}

std::string Move::convert_to_fen(int index) {
    return std::string({FILES[index%8], RANKS[index/8]});
}