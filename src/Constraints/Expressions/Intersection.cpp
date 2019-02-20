//
// Created by jdeanton on 2/14/19.
//

#include "Intersection.h"

#include "iostream"
#include "assert.h"

using std::cout;
using std::endl;

Intersection::Intersection(Clock& c11, Clock& c22, string name):c1(c11), c2(c22), Clock(name)  {
}


bool Intersection::evaluate() {
    return false;
}

void Intersection::rewrite() {
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Intersection::propagatesChoice() {
//    cout << "Intersection::propagatesChoice " << " c1 = "<< c1.status << " c2 = " << c2.status << " def = " << status << endl;

    if (status == TRUE && (c1.status == TRUE && c2.status == TRUE)) {
        return true;
    }
    if (status == FALSE && (c1.status == FALSE || c2.status == FALSE)) {
        return true;
    }
    if (status == POSSIBLY
        && (c1.status == POSSIBLY  || c2.status == POSSIBLY)) {
        return true;
    }

    if (status == FALSE && (c1.status == POSSIBLY && c2.status == POSSIBLY)) {
        return true;
    }

    //if here, something must be done

    if (c1.status == TRUE  && c2.status == TRUE){
        this->status = TRUE;
        return false;
    }
    if (c1.status == FALSE || c2.status == FALSE) {
        this->status = FALSE;
        return false;
    }
    if(status == TRUE){
        assert(c1.status != FALSE);
        c1.status = TRUE;
        assert(c2.status != FALSE);
        c2.status = TRUE;
        return false;
    }

    if (status == FALSE && (c1.status == TRUE && c2.status == POSSIBLY)) {
        c2.status = FALSE;
        return false;
    }
    if (status == FALSE && (c1.status == POSSIBLY && c2.status == TRUE)) {
        c1.status = FALSE;
        return false;
    }


    cout << "ERROR: in Union Expression " << name << " a case is missing: c1 = "<< c1.status << " c2 = " << c2.status << " def = " << status << endl;
    exit(-1);
}

void Intersection::reset(){
    Constraint::reset();
    Clock::reset();
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Intersection::propagatesDeath(){
    if ((c1.isDead || c2.isDead) && !isDead){
        isDead = true;
        return false;
    }
    return true;
}