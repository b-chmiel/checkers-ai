#ifndef EVALUATION_FUNCTION_H
#define EVALUATION_FUNCTION_H

#include "../../../DrawBoard/board.h"
#include <random>

class EvaluationFunction
{
public:
    virtual double Evaluate(const board::Checkerboard&) const = 0;
    double Noise() const
    {
        auto delta = std::getenv("DELTA");
        if (delta == NULL)
        {
            return 0;
        }

        std::random_device rd;
        double d = std::stod(delta);
        std::uniform_real_distribution<> dis(-d, d);
        return dis(rd);
    };
};

#endif
