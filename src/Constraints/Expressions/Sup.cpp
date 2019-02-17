//
// Created by jdeanton on 2/17/19.
//

#include "Sup.h"

#include "iostream"

using std::cout;
using std::endl;

Sup::Sup(Clock& lc, Clock& rc, string name):leftClock(lc), rightClock(rc), Clock(name)  {
}

void Sup::reset(){
    Constraint::reset();
    Clock::reset();
    delta = 0;
}

bool Sup::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }
    return false;
}

void Sup::rewrite() {
    if(leftClock.status == TRUE){
        delta--;
    }
    if(rightClock.status == TRUE){
        delta++;
    }
    return;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Sup::propagate() {
    if(isDead){
        return true;
    }

    if (status == POSSIBLY && (leftClock.status == POSSIBLY && rightClock.status == POSSIBLY)){
        return true;
    }

    if (status != POSSIBLY && (leftClock.status != POSSIBLY && rightClock.status != POSSIBLY)){
        return true;
    }

    if( delta > 0 && status == leftClock.status){
        return true;
    }

    if( delta < 0 && status == rightClock.status){
        return true;
    }

    if( delta == 0
        && ((status == TRUE && (leftClock.status == TRUE || rightClock.status == TRUE))
            || (status == FALSE && (leftClock.status == FALSE && rightClock.status == FALSE))
            || (status == POSSIBLY && (leftClock.status == POSSIBLY && rightClock.status == TRUE))
            || (status == POSSIBLY && (leftClock.status == TRUE && rightClock.status == POSSIBLY)))
            ){
        return true;
    }

    if( delta > 0 && leftClock.status != POSSIBLY){
        status = leftClock.status;
        return false;
    }

    if( delta < 0 && rightClock.status != POSSIBLY){
        status = rightClock.status;
        return false;
    }

    if( delta > 0 && status != POSSIBLY){
        leftClock.status = status;
        return false;
    }

    if( delta < 0 && status != POSSIBLY){
        rightClock.status = status;
        return false;
    }

    if( delta == 0 && (status == FALSE)){
        if (rightClock.status != POSSIBLY){
            leftClock.status = status;
            return false;
        }
        if (leftClock.status != POSSIBLY){
            rightClock.status = status;
            return false;
        }
        //here we have to choose randomly
        int r = (rand()%2);
        if (r == 1 ){
            leftClock.status = status;
        }else{
            rightClock.status = status;
        }
        return false;
    }

    if( delta == 0 && (status == TRUE)){
        leftClock.status = status;
        rightClock.status = status;
        return false;
    }

    if( delta == 0 && (rightClock.status == TRUE && leftClock.status == TRUE)){
        status = TRUE;
        return false;
    }

    if( delta == 0 && (rightClock.status == FALSE || leftClock.status == FALSE)){
        status = FALSE;
        return false;
    }

    cout << "ERROR: in Sup Expression " << name << " a case is missing: left clock = "<< leftClock.status << " right clock= " << rightClock.status << " def = " << status << "and delta = " <<delta << endl;
    exit(-1);
}