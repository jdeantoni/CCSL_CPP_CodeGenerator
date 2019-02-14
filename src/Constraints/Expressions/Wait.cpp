//
// Created by jdeanton on 5/28/17.
//

#include "Wait.h"
#include "iostream"

using std::cout;
using std::endl;

Wait::Wait(Clock& c11, int waitValue, string name):c1(c11), N(waitValue), initialN(waitValue), Clock(name)  {
}

Wait::~Wait() {
}

void Wait::reset(){
    Constraint::reset();
    Clock::reset();
    N = initialN;
}

bool Wait::evaluate() {
    if(isDead){
        status = FALSE;
        return false;
    }
    if (N > 1){
        status = FALSE;
    }
    return false;
}

void Wait::rewrite() {
    if (isDead){
        return;
    }

    if (status == TRUE){
        this->isDead = true;
        N = -1;
        return;
    }

    if (c1.status == TRUE){
        N--;
//        cout << "N-- : " <<N << endl;
    }
    return;
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Wait::propagate() {
    if (((N == 1)||(N == 0))) {
        if (this->status == POSSIBLY && c1.status != POSSIBLY) {
            this->status = c1.status;
//            cout << this->name << "set to " << c1.status << endl;
            return false;
        }
        if (this->status == FALSE && c1.status == POSSIBLY) {
            c1.status = FALSE;
            return false;
        }

//        cout << "problem: "<< this->name << " is " << this->status << " && c1 is " << c1.status << endl;
    }
   return true;
}