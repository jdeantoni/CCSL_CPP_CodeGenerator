//
// Created by jdeanton on 2/15/19.
//

#include "SampledOn.h"
#include "iostream"

using std::cout;
using std::endl;

SampledOn::SampledOn(Clock& sampled, Clock& sampler, string name):sampledClock(sampled), samplingClock(sampler), Clock(name)  {
}

void SampledOn::reset(){
    Constraint::reset();
    Clock::reset();
    sampledSeen = false;
}

bool SampledOn::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }
    if (!sampledSeen){
        status = FALSE;
    }
    return false;
}

void SampledOn::rewrite() {
    if(status == TRUE){
        sampledSeen = false;
        cout << "sampledSeen set to false" <<endl;
    }

    if (sampledClock.status == TRUE){
        sampledSeen = true;
        cout << "sampledSeen set to true" <<endl;
    }

    return;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool SampledOn::propagate() {
    if( status == TRUE && sampledSeen && samplingClock.status == TRUE){
        return true;
    }

    if( status == POSSIBLY && samplingClock.status == POSSIBLY){
        return true;
    }

    if( status == FALSE && !sampledSeen){
        return true;
    }

    if( status == FALSE && sampledSeen && samplingClock.status == FALSE){
        return true;
    }

    if( status == POSSIBLY && sampledSeen && samplingClock.status == TRUE){
        status = TRUE;
        return false;
    }

    if( status == POSSIBLY && sampledSeen && samplingClock.status == FALSE){
        status = FALSE;
        return false;
    }

    if( status == TRUE && sampledSeen && samplingClock.status == POSSIBLY){
        samplingClock.status = TRUE;
        return false;
    }
    if( status == FALSE && sampledSeen && samplingClock.status == POSSIBLY){
        samplingClock.status = FALSE;
        return false;
    }

    cout << "ERROR: in SampledOn Expression " << name << " a case is missing: sampled = "<< sampledClock.status << " sampler = " << samplingClock.status << " def = " << status << endl;
    exit(-1);
}