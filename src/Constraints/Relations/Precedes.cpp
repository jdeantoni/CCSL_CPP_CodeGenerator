/*
 * PrecedesRelation.cpp
 *
 *  Created on: Aug 17, 2016
 *      Author: jdeanton
 */

#include "Precedes.h"

Precedes::Precedes(Clock& l, Clock& r): left(l), right(r) {
}

Precedes::~Precedes() {
}

bool Precedes::evaluate() {
    if (delta == 0){
        right.status = FALSE;
    }
	return false;
}

void Precedes::rewrite() {
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
bool Precedes::propagatesChoice() {
    evaluate();
    return true; //never propagates anything...
}


/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Precedes::propagatesDeath(){
    if (left.isDead && !right.isDead && delta == 0){
        right.isDead = true;
        return false;
    }
    return true;
}