//
// Created by jdeanton on 5/24/17.
//

#ifndef SRC_SUBCLOCKRELATION_H
#define SRC_SUBCLOCKRELATION_H

#include "../../Utils/TruthTable.h"
#include "../../Clock.h"
#include "../Constraint.h"

class SubClock : public Constraint{
public:
    Clock& left;
    Clock& right;

    SubClock(Clock& l, Clock& r);

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagatesChoice() override;
    virtual  void rewrite() override;
    virtual  bool propagatesDeath() override;

    virtual ~SubClock();
};



#endif //SRC_SUBCLOCKRELATION_H
