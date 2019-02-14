//
// Created by jdeanton on 5/24/17.
//

#include "SubClock.h"
#include <assert.h>     /* assert */

SubClock::SubClock(Clock& l, Clock& r): left(l), right(r) {
}

SubClock::~SubClock() {
}

bool SubClock::evaluate() {
    return false;
}

void SubClock::rewrite() {
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool SubClock::propagate() {
    if (right.status == FALSE){
        if (left.status != FALSE){
            left.status = FALSE;
            return false;
        }
    }
    if (left.status == TRUE){
        if (right.status != TRUE){
            assert(right.status == POSSIBLY);
            right.status = TRUE;
            return false;
        }
    }
    return true; //never propagates anything...
}