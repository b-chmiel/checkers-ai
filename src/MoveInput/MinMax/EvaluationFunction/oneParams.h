#ifndef FUNCTION_ONE_PARAMS_H
#define FUNCTION_ONE_PARAMS_H

#include "../../../Board/constants.h"

namespace oneParams
{
constexpr int PlayerPiecesCount = constants::BOARD_WIDTH / 2 * (constants::BOARD_HEIGHT / 2 - 1);

struct OneParams
{
    int PlayerPieces = 0;
    int OpponentPieces = 0;
    int Distance = 0;
};

struct OneWeights
{
    static constexpr double PlayerPieces = 1;
    static constexpr double OpponentPieces = -1;
    static constexpr double Distance = 0;
};

struct OneMaxValues
{
    static constexpr double MaxPlayerPieces = OneWeights::PlayerPieces * PlayerPiecesCount;
    static constexpr double MaxOpponentPieces = OneWeights::OpponentPieces * PlayerPiecesCount;
    static constexpr double MaxDistance = OneWeights::Distance * (constants::BOARD_WIDTH / 2 * (2 * constants::BOARD_HEIGHT - 1));
    static constexpr double MinValue = MaxOpponentPieces;
    static constexpr double MaxValue = MaxPlayerPieces + MaxDistance;
};
}

#endif
