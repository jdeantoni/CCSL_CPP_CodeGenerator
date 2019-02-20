//
// Created by jdeanton on 2/16/19.
//

#ifndef SRC_INF_H
#define SRC_INF_H


#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Inf : public Constraint, public Clock {
public:
    Clock& leftClock;
    Clock& rightClock;
    int delta = 0;

    Inf(Clock& lc, Clock& rc, string name);

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagatesChoice() override;
    virtual  void rewrite() override;
    virtual  void reset() override;
    virtual  bool propagatesDeath() override;

    virtual ~Inf() = default;

};


#endif //SRC_INF_H
