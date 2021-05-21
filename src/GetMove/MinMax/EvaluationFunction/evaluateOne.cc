#include "evaluateOne.h"
#include "../../../DrawBoard/board.h"
#include "../../../DrawBoard/constants.h"
#include "../../../Utils/player.h"
#include "oneParams.h"
#include <cmath>

using namespace oneParams;

double EvaluateOne::Evaluate(const board::Checkerboard& board) const
{
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

    return CountWeights(params) + Noise();
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