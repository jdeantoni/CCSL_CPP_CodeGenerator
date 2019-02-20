//
// Created by jdeanton on 6/2/17.
//

#include "Concatenation.h"
#include "iostream"

using std::cout;
using std::endl;

Concatenation::Concatenation(Clock& lc, Clock& rc, string name):leftClock(lc), rightClock(rc), Clock(name)  {
    if (dynamic_cast<Constraint*>(&lc) != nullptr){
        leftIsAConstraint = true;
    }
    if (dynamic_cast<Constraint*>(&rc) != nullptr){
        rightIsAConstraint = true;
    }

    if (&rightClock == this){
        isRecursive = true;
    }

}

Concatenation::~Concatenation() {
}

bool Concatenation::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }

    if(followLeft && rightIsAConstraint  && &rightClock != &leftClock  && !isRecursive){
        rightClock.status = FALSE;
    }
    return false;
}

void Concatenation::rewrite() {
    if (leftClock.isDead && isRecursive){
        leftClock.isDead = false;
        leftClock.reset();
    }
    if (leftClock.isDead && followLeft){
        followLeft = false;
        if(&rightClock == &leftClock){
            rightClock.reset();
        }
    }
    if (!followLeft && rightClock.isDead){
        isDead = true;
    }
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Concatenation::propagatesChoice() {
    if(followLeft){ //follow left
        if (leftClock.status != POSSIBLY && this->status == POSSIBLY){
            this->status = leftClock.status;
            return false;
        }
        if (leftClock.status == POSSIBLY && this->status != POSSIBLY){
            leftClock.status = this->status;
            return false;
        }
    }else{ //follow right
        if (rightClock.status != POSSIBLY && this->status == POSSIBLY){
            this->status = rightClock.status;
            return false;
        }
        if (rightClock.status == POSSIBLY && this->status != POSSIBLY){
            rightClock.status = this->status;
            return false;
        }
    }

    return true;
}

void Concatenation::reset(){
    Constraint::reset();
    Clock::reset();
    followLeft = true;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Concatenation::propagatesDeath(){
    if (!followLeft && rightClock.isDead && !isDead){
        isDead = true;
        return false;
    }
    return true;
}