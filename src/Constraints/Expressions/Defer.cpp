//
// Created by jdeanton on 5/29/17.
//

#include "Defer.h"
#include <iostream>

using std::cout;
using std::endl;

void Defer::reset(){
    Constraint::reset();
    Clock::reset();
    ds.clear();
}

bool Defer::getBeta() {
    bool beta = false;
    if (ds.empty()) {
        beta = false;
    }
    else {
        beta = (getDelay() == 1 || getDelay() == 0);
    }
    return beta;
}

bool Defer::evaluate() {
//    cout << "defer::evaluate --> ds=";
//        for(int i : ds){
//            cout << i << " ";
//        }
//    cout << endl;
    if(isDead){
        status = FALSE;
        return false;
    }
    bool beta = getBeta();
    if (! beta) {
        status = FALSE;
    }

    return false;
}


void Defer::rewrite() {
    if (isDead){
        return;
    }

    if (baseClock.status == TRUE) {
        if (delayClock.status == TRUE) {
            // RWDefer3
            nextDelay();
            int next = sigma.nextHead();
            if (next != -1) {
                sched(next, 0);
            }
        }
        else {
            // RWDefer2
            int next = sigma.nextHead();
            if (next != -1) {
                sched(next, 0);
            }
        }
    }
    else if (delayClock.status == TRUE) {
        // RWDefer1 nextDelay()
        nextDelay();
    }

    if ( (ds.empty() && sigma.empty())
         || delayClock.isDead) {
        isDead = true;
        return;
    }
}


int Defer::getDelay() {
    if (ds.empty()) {
        return INT32_MAX;
    }
    return ds.front();
}


void Defer::sched(int next, int start) {
//    cout << "sched("<<next<<","<<start<<")"<<endl;
    if (ds.size() == start) {
        ds.push_back(next);
    }
    else {
        int head = ds.at(start);
        if (next == head) {
            return;
        }
        else if (next < head) {
            int rem = head - next;
            ds.at(start) = next;
            ds.emplace(ds.begin()+start + 1, rem);
        }
        else { // next > head
            int rem = next - head;
            sched(rem, start + 1);
        }
    }
}

void Defer::nextDelay() {
    if (! ds.empty()) {
        int head = ds.front();

        if ((head == 1) || (head == 0)) {
            ds.pop_front();
        }
        else {
            ds.front() = head - 1;
        }
    }
}

/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Defer::propagate() {
    bool beta = getBeta();
    if (beta) {
//        cout << "beta is true" << endl;
       if (delayClock.status != POSSIBLY && delayClock.status != status){
           status = delayClock.status;
           return false;
       }
       if (delayClock.status == POSSIBLY && status == FALSE){
           delayClock.status = FALSE;
           return false;
       }
    }
    return true;
}

Defer::Defer(Clock& bc, Clock& dc, Sequence seq, string name)
:baseClock(bc),delayClock(dc),sigma(seq),Clock(name)
{}

Defer::~Defer(){

}
