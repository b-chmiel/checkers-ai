#ifndef EVALUATE_TWO_H
#define EVALUATE_TWO_H

#include "../../../Utils/move.h"
#include "../../../Utils/player.h"
#include "evaluationFunction.h"
#include "twoParams.h"
#include <vector>

class EvaluateTwo : public EvaluationFunction
{
public:
    EvaluateTwo(double delta);

    double Evaluate(const board::Checkerboard&, const std::vector<Move>& availableMoves, int moveCount) const override;

private:
    double m_Delta;
    double GetDistanceValue(int y, const player::Player&) const;
    double CountWeights(const twoParams::TwoParams&) const;
};

#endif
