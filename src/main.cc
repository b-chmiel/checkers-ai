#include "Experiment/experiment.h"
#include "Experiment/timeEfficiency_impl.h"
#include "MoveInput/MinMax/alphaBeta.h"
#include "MoveInput/MinMax/minMax.h"
#include <cstdlib>

int main()
{
    auto params = experiment::Params {
        .RandomMoves = 8,
        .GameCount = 50,
        .Delta = 0.01,
        .MaxDepth = 4
    };

    if (std::getenv("TIME_EFFICIENCY_A"))
    {
        auto ex1A = TimeEfficiency(params);
        ex1A.Perform<minmax::MinMax>();
    }

    if (std::getenv("TIME_EFFICIENCY_B"))
    {
        auto ex1B = TimeEfficiency(params);
        ex1B.Perform<alpha_beta::AlphaBeta>();
    }

    return 0;
}
