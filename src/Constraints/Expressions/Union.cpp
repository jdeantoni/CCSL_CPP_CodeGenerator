/*
 * UnionExpression.cpp
 *
 *  Created on: Aug 19, 2016
 *      Author: jdeanton
 */

#include "Union.h"
#include "iostream"

using std::cout;
using std::endl;

Union::Union(Clock& c11, Clock& c22, string name):c1(c11), c2(c22), Clock(name)  {
}

Union::~Union() {
}

bool Union::evaluate() {
	return false;
}

void Union::rewrite() {
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Union::propagate() {

//    cout << "Union::propagate " << " c1 = "<< c1.status << " c2 = " << c2.status << " def = " << status << endl;

    if (status == TRUE && (c1.status == TRUE || c2.status == TRUE)) {
        return true;
    }
    if ((status == FALSE) && (c1.status == FALSE) && (c2.status == FALSE)) {
        return true;
    }
    if ((status == POSSIBLY)
        && ((c1.status == FALSE  && c2.status == POSSIBLY)
            || (c2.status == FALSE && c1.status == POSSIBLY)
            || (c2.status == POSSIBLY && c1.status == POSSIBLY))) {
        return true;
    }
    if (status == TRUE && (c1.status == POSSIBLY && c2.status == POSSIBLY)) {
        return true;
    }
    //if here, something must be done

    if (c1.status == TRUE || c2.status == TRUE){
        this->status = TRUE;
        return false;
    }
    if (c1.status == FALSE && c2.status == FALSE) {
        this->status = FALSE;
        return false;
    }
    if(status == FALSE){
        c1.status = FALSE;
        c2.status = FALSE;
        return false;
    }

    if (status == TRUE && (c1.status == FALSE)) {
        c2.status = TRUE;
        return false;
    }
    if (status == TRUE && (c2.status == FALSE)) {
        c1.status = TRUE;
        return false;
    }

    cout << "ERROR: in Union Expression " << name << " a case is missing: c1 = "<< c1.status << " c2 = " << c2.status << " def = " << status << endl;
	exit(-1);
}

void Union::reset(){
    Constraint::reset();
    Clock::reset();
}