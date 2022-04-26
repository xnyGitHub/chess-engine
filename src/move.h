#ifndef MOVE_H
#define MOVE_H
#include <string>

class move {
public:
    move(int start, int stop, int type);
    std::string get_string_move();
    enum flag {
        normal,
        capture,
        castle
    };
private:
    int _move;


};


#endif //MOVE_H
