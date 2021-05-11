#include "board.h"
#include <iostream>
#include <string>

using namespace board;

Checkerboard::Checkerboard()
{
    auto currentPlayer = BoardState::PLAYER2;
    for (auto i = 0; i < HEIGHT; i++) {
        if (i > 3) {
            currentPlayer = BoardState::PLAYER1;
        }

        for (auto j = 0; j < WIDTH; j++) {
            if (i == 3 || i == 4) {
                Checkerboard::state[i][j] = BoardState::EMPTY;
            } else if (i % 2 == j % 2) {
                Checkerboard::state[i][j] = BoardState::EMPTY;
            } else {
                Checkerboard::state[i][j] = currentPlayer;
            }
        }
    }
}

void Checkerboard::Show()
{
    const char* fields[5] = { "   ", " ⛀ ", " ⛂ ", " ⛁ ", " ⛃ " };
    const char* colorA = "\e[0;44;43m";
    const char* colorB = "\e[0;30;44m";
    const char* cancelEffects = "\e[0m";

    for (auto i = 0; i < HEIGHT; i++) {
        for (auto j = 0; j < WIDTH; j++) {
            const char* field = fields[Checkerboard::state[i][j]];
            if (i % 2 == j % 2) {
                printf("%s", colorA);
            } else {
                printf("%s", colorB);
            }

            printf("%s", field);
        }
        printf("%s", cancelEffects);
        printf("\n");
    }

    printf("%s", cancelEffects);
}