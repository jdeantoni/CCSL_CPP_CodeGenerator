//
// Created by jdeanton on 2/14/19.
//

#ifndef SRC_INTERSECTION_H
#define SRC_INTERSECTION_H


#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Intersection: public Constraint, public Clock {
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


    Intersection( Clock&c11, Clock& c22, string name);
    virtual ~Intersection() = default;
};


#endif //SRC_INTERSECTION_H
