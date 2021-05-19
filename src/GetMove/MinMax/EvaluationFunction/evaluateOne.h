#ifndef EVALUATE_ONE_H
#define EVALUATE_ONE_H

#include "../../../Utils/player.h"
#include "evaluationFunction.h"
#include "oneParams.h"

class EvaluateOne : public EvaluationFunction
{
public:
    double Evaluate(const board::Checkerboard&) const override;

private:
    double GetDistanceValue(int y, const player::Player&) const;
    double CountWeights(const oneParams::OneParams&) const;
};

#endif
