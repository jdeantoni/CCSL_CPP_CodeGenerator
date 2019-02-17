//
// Created by jdeanton on 2/16/19.
//

#include "UpTo.h"
#include "iostream"

using std::cout;
using std::endl;

UpTo::UpTo(Clock& toFollow, Clock& theKiller, string name):clockToFollow(toFollow), killer(theKiller), Clock(name)  {
}

void UpTo::reset(){
    Constraint::reset();
    Clock::reset();
}

bool UpTo::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }
    return false;
}

void UpTo::rewrite() {
    if(killer.status == TRUE){
        isDead = true;
    }
    return;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool UpTo::propagate() {
    if(isDead){
        return true;
    }

    if( status == clockToFollow.status && killer.status != TRUE){
        return true;
    }

    if( status == FALSE && killer.status == TRUE){
        return true;
    }

    if( status == POSSIBLY && clockToFollow.status == POSSIBLY && killer.status != TRUE){
        return true;
    }

    if( status == POSSIBLY && clockToFollow.status != POSSIBLY && killer.status != TRUE){
        status = clockToFollow.status;
        return false;
    }

    if( killer.status == TRUE){
        status = FALSE;
        return false;
    }

    cout << "ERROR: in UpTo Expression " << name << " a case is missing: clock to follow = "<< clockToFollow.status << " killer = " << killer.status << " def = " << status << endl;
    exit(-1);
}