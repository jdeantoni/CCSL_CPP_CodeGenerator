//
// Created by jdeanton on 5/28/17.
//

#include "Exclusion.h"
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

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
bool Exclusion::propagatesChoice() {
//    cout << "Exclusion::propagatesChoice " << " c1 = "<< c1.status << " c2 = " << c2.status << endl;

    if(  (c1.status == TRUE && c2.status == FALSE)
       ||(c1.status == FALSE && c2.status == TRUE)
       ||(c1.status == POSSIBLY && c2.status == POSSIBLY)
       ||(c1.status == POSSIBLY && c2.status == FALSE)
       ||(c1.status == FALSE && c2.status == POSSIBLY)
       ||(c1.status == FALSE && c2.status == FALSE)
    ){
        return true;
    }

    if (c1.status == TRUE){
//        cout << c2 << endl;
//        assert(c2.status != TRUE);
        c2.status = FALSE;
        return false;
    }
    if (c2.status == TRUE){
//        assert(c1.status != TRUE);
        c1.status = FALSE;
        return false;
    }

    cout << "ERROR: in Exclusion, a case is missing: c1 = "<< c1.status << " c2 = " << c2.status << endl;
    exit(-1);
}
/**
 *
 * @return true is stability is reached, false otherwise
 */
bool Exclusion::propagatesDeath(){
    return true;
}
