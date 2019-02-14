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
    TruthTable truthTable =
            {//   a     ;     b
               { TRUE, 	   POSSIBLY},
               { FALSE, 	  FALSE},
            };

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    SubClock(Clock& l, Clock& r);
    virtual ~SubClock();
};



#endif //SRC_SUBCLOCKRELATION_H
