/*
 * UnionExpression.h
 *
 *  Created on: Aug 19, 2016
 *      Author: jdeanton
 */

#ifndef UNIONEXPRESSION_H_
#define UNIONEXPRESSION_H_

#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Union: public Constraint, public Clock {
public:
	Clock& c1;
	Clock& c2;

	/**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
	virtual  bool evaluate() override;
	virtual  bool propagate() override;
	virtual  void rewrite() override;
	virtual  void reset() override;


	Union( Clock&c11, Clock& c22, string name);
	virtual ~Union();
};

#endif /* UNIONEXPRESSION_H_ */
