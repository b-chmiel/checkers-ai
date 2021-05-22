#include "Board/board.h"
#include "Experiment/experiment.h"
#include "Experiment/timeEfficiency.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluateOne.h"
#include "MoveInput/MinMax/EvaluationFunction/evaluationFunction.h"
#include "MoveInput/MinMax/alphaBeta.h"
#include "MoveInput/MinMax/minMax.h"
#include "MoveInput/User/userInput.h"
#include "MoveInput/availableMoves.h"
#include "Utils/move.h"
#include "Utils/player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    auto params = experiment::Params {
        .IsMoveTiming = true,
        .IsGameTiming = true,
        .RandomMoves = 0,
        .GameCount = 100,
        .Delta = 0.01,
        .AlphaBeta = false,
        .MaxDepth = 3
    };

    auto ex = TimeEfficiency(params);
    ex.Perform();

    return 0;
}
