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

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;

    Inf(Clock& lc, Clock& rc, string name);
    virtual ~Inf() = default;

};


#endif //SRC_INF_H
