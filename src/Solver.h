//
// Created by jdeanton on 2/20/19.
//

#ifndef SRC_SOLVER_H
#define SRC_SOLVER_H


#include <vector>
#include <iostream>
#include "Clock.h"
#include "Constraints/Constraint.h"

using std::vector;
using std::cout;
using std::endl;

class Solver {

public:
    vector<Clock *> clocks;
    vector<Constraint *> constraintsButExclusions;
    vector<Constraint*> exclusions;

    Solver(vector<Clock *> allClocks, vector<Constraint *> allConstraintsButExclusions, vector<Constraint*> allExclusions);

    virtual void solve();
    virtual void simulate(const unsigned int nbSteps);
    virtual void propagatesChoice();
    virtual void propagatesDeath();

    virtual ~Solver() = default;
};


#endif //SRC_SOLVER_H
