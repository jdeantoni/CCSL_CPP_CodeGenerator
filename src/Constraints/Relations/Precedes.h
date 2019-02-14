/*
 * PrecedesRelation.h
 *
 *  Created on: Aug 17, 2016
 *      Author: jdeanton
 */

#ifndef PRECEDESRELATION_H_
#define PRECEDESRELATION_H_

#include "../../Utils/TruthTable.h"
#include "../../Clock.h"
#include "../Constraint.h"



class Precedes : public Constraint{
public:
	int delta = 0;
    Clock& left;
    Clock& right;
//    TruthTable truthTable =
//			{//delta == 0 ;          a     ;     b
//				{ TRUE, 	   POSSIBLY,   FALSE  },
//				{ FALSE, 	   POSSIBLY,   POSSIBLY}
//			};

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
	Precedes(Clock& l, Clock& r);
	virtual ~Precedes();
};

#endif /* PRECEDESRELATION_H_ */
