#ifndef EVALUATE_ONE_H
#define EVALUATE_ONE_H

#include "../../../Utils/move.h"
#include "../../../Utils/player.h"
#include "evaluationFunction.h"
#include "oneParams.h"
#include <vector>

class EvaluateOne : public EvaluationFunction
{
public:
    double Evaluate(const board::Checkerboard&, const std::vector<Move>& availableMoves) const override;

private:
    double GetDistanceValue(int y, const player::Player&) const;
    double CountWeights(const oneParams::OneParams&) const;
};

#endif
