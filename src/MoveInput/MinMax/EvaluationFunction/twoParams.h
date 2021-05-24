#ifndef FUNCTION_TWO_PARAMS_H
#define FUNCTION_TWO_PARAMS_H

#include "../../../Board/constants.h"

namespace twoParams
{
constexpr int PlayerPiecesCount = constants::BOARD_WIDTH / 2 * (constants::BOARD_HEIGHT / 2 - 1);

struct TwoParams
{
    int PlayerPieces = 0;
    int OpponentPieces = 0;
    int Distance = 0;
};

struct TwoWeights
{
    static constexpr double PlayerPieces = 0.8;
    static constexpr double OpponentPieces = -1;
    static constexpr double Distance = 0.1;
};

struct TwoMaxValues
{
    static constexpr double MaxPlayerPieces = TwoWeights::PlayerPieces * PlayerPiecesCount;
    static constexpr double MaxOpponentPieces = TwoWeights::OpponentPieces * PlayerPiecesCount;
    static constexpr double MaxDistance = TwoWeights::Distance * (constants::BOARD_WIDTH / 2 * (2 * constants::BOARD_HEIGHT - 1));
    static constexpr double MinValue = MaxOpponentPieces;
    static constexpr double MaxValue = MaxPlayerPieces + MaxDistance;
};
}

#endif
