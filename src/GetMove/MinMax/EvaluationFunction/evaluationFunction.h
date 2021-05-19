#ifndef EVALUATION_FUNCTION_H
#define EVALUATION_FUNCTION_H

#include "../../../DrawBoard/board.h"

class EvaluationFunction
{
public:
    virtual double Evaluate(const board::Checkerboard&) const = 0;
};

#endif
