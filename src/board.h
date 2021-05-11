#ifndef BOARD_H
#define BOARD_H

namespace board {
const int WIDTH = 8;
const int HEIGHT = 8;

enum BoardState {
    EMPTY,
    PLAYER1,
    PLAYER2,
    PLAYER1_KING,
    PLAYER2_KING
};

class Checkerboard {
public:
    BoardState state[HEIGHT][WIDTH];
    Checkerboard();
    void Show();
};
}

#endif