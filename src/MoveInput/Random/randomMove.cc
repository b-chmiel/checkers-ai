#include "randomMove.h"
#include "../../Board/board.h"
#include "../../Utils/move.h"
#include "../availableMoves.h"
#include <optional>
#include <random>
#include <vector>

std::optional<Move> RandomMove::ProcessMove(const board::Checkerboard& board, int)
{
    auto availableMoves = AvailableMoves::GetAvailableMoves(board, board.CurrentPlayer.Type);

    if (availableMoves.size() == 0)
    {
        return std::nullopt;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> distribution(0, availableMoves.size() - 1);

    auto index = distribution(rng);
    return availableMoves[index];
}