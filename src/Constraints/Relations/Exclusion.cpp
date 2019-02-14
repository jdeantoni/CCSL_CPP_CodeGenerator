//
// Created by jdeanton on 5/28/17.
//

#include "Exclusion.h"


Exclusion::Exclusion(Clock& l, Clock& r): c1(l), c2(r) {
}

Exclusion::~Exclusion() {
}

bool Exclusion::evaluate() {
    return false;
}

void Exclusion::rewrite() {
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Exclusion::propagate() {
    if (c1.status == TRUE){
        c2.status = FALSE;
    }
    if (c2.status == TRUE){
        c1.status = FALSE;
    }
    return true; //never propagates anything...
}