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

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    Causes(Clock& l, Clock& r);
    virtual ~Causes() = default;
};


#endif //SRC_CAUSES_H
