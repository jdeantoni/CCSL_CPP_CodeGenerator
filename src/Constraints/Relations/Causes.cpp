//
// Created by jdeanton on 2/14/19.
//

#include "Causes.h"

Causes::Causes(Clock& l, Clock& r): left(l), right(r) {
}


bool Causes::evaluate() {
    return false;
}

void Causes::rewrite() {
    if (left.status == TRUE){
        delta++;
    }
    if(right.status == TRUE){
        delta--;
    }
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Causes::propagate() {
    if (delta == 0){
        if (left.status == FALSE && right.status == POSSIBLY){
            right.status = FALSE;
            return false;
        };
        if (left.status == POSSIBLY && right.status == TRUE){
            left.status = TRUE;
            return false;
        };
    }
    return true; //never propagates anything...
}