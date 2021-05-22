#include "evaluateOne.h"
#include "../../../Board/board.h"
#include "../../../Board/constants.h"
#include "../../../Utils/move.h"
#include "../../../Utils/player.h"
#include "oneParams.h"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace oneParams;

double EvaluateOne::Evaluate(const board::Checkerboard& board, const std::vector<Move>& availableMoves, int moveCount) const
{
    if (availableMoves.size() == 0 || moveCount >= constants::DRAW_THRESHOLD)
    {
        return 0;
    }

    OneParams params;

    auto currentPlayer = board.CurrentPlayer;
    for (auto y = 0; y < constants::BOARD_HEIGHT; y++)
    {
        for (auto x = 1 - y % 2; x < constants::BOARD_WIDTH; x += 2)
        {
            auto& field = board.State[y][x];

            if (field.Player == currentPlayer)
            {
                params.PlayerPieces++;
                params.Distance += GetDistanceValue(y, field.Player);
            }
            else if (field.Player.Type != player::NONE)
            {
                params.OpponentPieces++;
            }
        }
    }

    auto result = CountWeights(params) + Noise();
    return std::min(std::max(0.0, result), 1.0);
}

double EvaluateOne::GetDistanceValue(int y, const player::Player& current) const
{
    return constants::BOARD_HEIGHT - 1 - std::abs(current.MaxY() - y);
}

double EvaluateOne::CountWeights(const OneParams& params) const
{
    double result = 0.0;
    result += params.PlayerPieces * OneWeights::PlayerPieces;
    result += params.OpponentPieces * OneWeights::OpponentPieces;
    result += params.Distance * OneWeights::Distance;

    return (result - OneMaxValues::MinValue) / (OneMaxValues::MaxValue - OneMaxValues::MinValue);
}