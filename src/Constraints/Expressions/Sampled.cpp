//
// Created by jdeanton on 2/15/19.
//

#include "Sampled.h"
#include "iostream"

using std::cout;
using std::endl;

Sampled::Sampled(Clock& sampled, Clock& sampler, string name, bool strict)
   :sampledClock(sampled), samplingClock(sampler), Clock(name), isStrict(strict), sampledSeen(false)  {
}

void Sampled::reset(){
    Constraint::reset();
    Clock::reset();
    sampledSeen = false;
}

bool Sampled::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }
    if (!sampledSeen && isStrict){
        status = FALSE;
    }
    return false;
}

void Sampled::rewrite() {
    if(status == TRUE){
        sampledSeen = false;
        isDead = true;
//        cout << "sampledSeen set to false" <<endl;
    }

    if (sampledClock.status == TRUE && isStrict){
        sampledSeen = true;
//        cout << "sampledSeen set to true" <<endl;
    }

    if (sampledClock.status == TRUE && !isStrict && samplingClock.status != TRUE){
        sampledSeen = true;
//        cout << "sampledSeen set to true" <<endl;
    }

    return;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Sampled::propagate() {
//    cout << "Sampled::propagate " << " sampled = "<< sampledClock.status << " sampling = " << samplingClock.status << " def = " << status << " sampledSeen " << sampledSeen <<endl;

    if( status == TRUE && sampledSeen && samplingClock.status == TRUE){
        return true;
    }

    if( status == TRUE && sampledClock.status == TRUE && samplingClock.status == TRUE && !isStrict){
        return true;
    }

    if( status == TRUE && !sampledSeen && !isStrict && samplingClock.status == TRUE && sampledClock.status == TRUE){
        return true;
    }

    if( status == POSSIBLY && samplingClock.status == POSSIBLY){
        return true;
    }
    if( status == POSSIBLY && !sampledSeen && !isStrict && samplingClock.status == TRUE && sampledClock.status == POSSIBLY){
        return true;
    }

    if( status == FALSE && !sampledSeen && isStrict){
        return true;
    }

    if( status == FALSE && !sampledSeen && !isStrict && (sampledClock.status != TRUE || samplingClock.status != TRUE)){
        return true;
    }

    if( status == FALSE && !sampledSeen && !isStrict && sampledClock.status == POSSIBLY && samplingClock.status == POSSIBLY){
        return true;
    }

    if( status == FALSE && sampledSeen && samplingClock.status == FALSE){
        return true;
    }

    //do something from here
    if( status == POSSIBLY && sampledSeen && samplingClock.status == TRUE){
        status = TRUE;
        return false;
    }

    if( status == POSSIBLY && samplingClock.status == TRUE && !isStrict && sampledClock.status == TRUE){
        status = TRUE;
        return false;
    }

    if( status == POSSIBLY && samplingClock.status == FALSE){
        status = FALSE;
        return false;
    }

    if( status == POSSIBLY && sampledSeen && samplingClock.status == FALSE){
        status = FALSE;
        return false;
    }

    if( status == TRUE && sampledSeen){
        samplingClock.status = TRUE;
        return false;
    }

    if( status == TRUE && !sampledSeen && !isStrict){
        samplingClock.status = TRUE;
        sampledClock.status = TRUE;
        return false;
    }


    if( status == FALSE && sampledSeen && samplingClock.status == POSSIBLY){
        samplingClock.status = FALSE;
        return false;
    }

    if( status == FALSE && !sampledSeen && !isStrict && samplingClock.status == POSSIBLY && sampledClock.status == TRUE){
        samplingClock.status = FALSE;
        return false;
    }

    if( status == FALSE && !sampledSeen && !isStrict && samplingClock.status == TRUE && sampledClock.status == POSSIBLY){
        sampledClock.status = FALSE;
        return false;
    }

    cout << "ERROR: in Sampled Expression " << name << " a case is missing: sampled = "<< sampledClock.status << " sampler = " << samplingClock.status << " def = " << status << endl;
    exit(-1);
}