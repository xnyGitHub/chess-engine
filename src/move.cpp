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
    return "Not implemented";
}