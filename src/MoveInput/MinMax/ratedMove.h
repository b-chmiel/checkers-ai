#ifndef RATED_MOVE_H
#define RATED_MOVE_H

#include "../../Utils/move.h"

namespace rated_move
{
struct RatedMove
{
    double Key;
    Move MMove;
};

struct SortIncreasing final
{
    inline bool operator()(const RatedMove& left, const RatedMove& right) const
    {
        return left.Key < right.Key;
    }
};

using rated_move_set = std::set<rated_move::RatedMove, rated_move::SortIncreasing>;
}

#endif
