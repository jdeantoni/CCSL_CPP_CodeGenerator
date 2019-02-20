//
// Created by jdeanton on 2/14/19.
//

#ifndef SRC_CAUSES_H
#define SRC_CAUSES_H

#include "../../Clock.h"
#include "../Constraint.h"

class Causes : public Constraint{
public:
    int delta = 0;
    Clock& left;
    Clock& right;

    Causes(Clock& l, Clock& r);
    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagatesChoice() override;
    virtual  void rewrite() override;
    virtual  bool propagatesDeath() override;

    virtual ~Causes() = default;
};


#endif //SRC_CAUSES_H
