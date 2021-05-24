#include "evaluateTwo.h"
#include "../../../Board/board.h"
#include "../../../Board/constants.h"
#include "../../../Utils/move.h"
#include "../../../Utils/player.h"
#include "twoParams.h"
#include <algorithm>
#include <cmath>
#include <vector>

using namespace twoParams;

EvaluateTwo::EvaluateTwo(double delta)
    : m_Delta(delta)
{
}

double EvaluateTwo::Evaluate(const board::Checkerboard& board, const std::vector<Move>& availableMoves, int moveCount) const
{
    if (availableMoves.size() == 0 || moveCount >= constants::DRAW_THRESHOLD)
    {
        return 0;
    }

    TwoParams params;

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

    auto result = CountWeights(params) + Noise(m_Delta);
    return std::min(std::max(0.0, result), 1.0);
}

double EvaluateTwo::GetDistanceValue(int y, const player::Player& current) const
{
    return constants::BOARD_HEIGHT - 1 - std::abs(current.MaxY() - y);
}

double EvaluateTwo::CountWeights(const TwoParams& params) const
{
    double result = 0.0;
    result += params.PlayerPieces * TwoWeights::PlayerPieces;
    result += params.OpponentPieces * TwoWeights::OpponentPieces;
    result += params.Distance * TwoWeights::Distance;

    return (result - TwoMaxValues::MinValue) / (TwoMaxValues::MaxValue - TwoMaxValues::MinValue);
}