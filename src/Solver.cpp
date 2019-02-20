//
// Created by jdeanton on 2/20/19.
//

#include "Solver.h"
#include "Utils/utils.h"

using std::vector;

Solver::Solver(vector<Clock *> allClocks, vector<Constraint *> allConstraintsButExclusions, vector<Constraint*> allExclusions)
 :clocks(allClocks), constraintsButExclusions(allConstraintsButExclusions), exclusions(allExclusions)
 {}

void Solver::solve() {
    for(Constraint* pt_r: constraintsButExclusions + exclusions) {
        pt_r->evaluate();
    }

    for(Clock* pt_c : clocks) {
        if (pt_c->status == POSSIBLY) {
            pt_c->chooseStatus();
//            cout << clocks <<endl;
            propagatesChoice();
        }
    }

    propagatesDeath();

    for(Clock* pt_c : clocks){
        if(pt_c->status == TRUE){
            pt_c->ticks();
        }
    }
}


void Solver::simulate(const unsigned int nbSteps) {
    for (unsigned int currentStep= 0; currentStep < nbSteps; currentStep++) {
        cout << "-------------step " << currentStep << endl;

        solve();

        for(Clock* pt_c: clocks) {
            cout << *pt_c <<endl;
        }

        for(Constraint* pt_r: constraintsButExclusions + exclusions) {
            pt_r->rewrite();
        }


        for(Clock* pt_c : clocks){
            pt_c->status = POSSIBLY;
        }
    }
}


void Solver::propagatesChoice() {
    bool fixPointReached = true;
    do{
        fixPointReached = true;
        for(Constraint* pt_c : exclusions + constraintsButExclusions){
            bool isStable = pt_c->propagatesChoice();
            fixPointReached = fixPointReached && isStable;
        }
    }while (! fixPointReached);
}

void Solver::propagatesDeath() {
    bool fixPointReached = true;
    do{
        fixPointReached = true;
        for(Constraint* pt_c : exclusions + constraintsButExclusions){
            bool isStable = pt_c->propagatesDeath();
            fixPointReached = fixPointReached && isStable;
        }
    }while (! fixPointReached);
}