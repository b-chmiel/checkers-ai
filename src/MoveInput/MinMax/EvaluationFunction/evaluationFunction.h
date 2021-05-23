#ifndef EVALUATION_FUNCTION_H
#define EVALUATION_FUNCTION_H

#include "../../../Board/board.h"
#include "../../../Utils/move.h"
#include <random>
#include <vector>

class EvaluationFunction
{
public:
    virtual double Evaluate(const board::Checkerboard&, const std::vector<Move>& availableMoves, int moveCount) const = 0;
    double Noise(double delta) const
    {
        std::random_device rd;
        std::uniform_real_distribution<> dis(-delta, delta);
        return dis(rd);
    };

    virtual ~EvaluationFunction() = default;
};

#endif
