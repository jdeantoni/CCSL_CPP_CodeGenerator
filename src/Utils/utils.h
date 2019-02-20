//
// Created by jdeanton on 2/20/19.
//

#ifndef SRC_UTILS_H
#define SRC_UTILS_H
#include <iostream>
#include <vector>
#include <assert.h>
#include "../Clock.h"
#include "../Constraints/Constraint.h"


using std::ostream;
using std::vector;

ostream& operator<<(ostream& os, const vector<Clock*> vect_pt_c){
    for(Clock* pt_c : vect_pt_c){
        assert(pt_c != nullptr);
        os << *pt_c << "   |   ";
    }
    return os;
}

vector<Constraint *> operator+(const vector<Constraint *>& v1, const vector<Constraint *>& v2){
    vector<Constraint *> all = v1;
    for(Constraint* pt_c : v2){
        all.push_back(pt_c);
    }
    return all;
}

#endif //SRC_UTILS_H
