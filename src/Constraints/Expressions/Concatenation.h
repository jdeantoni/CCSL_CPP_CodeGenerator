//
// Created by jdeanton on 6/2/17.
//

#ifndef SRC_CONCATENATION_H
#define SRC_CONCATENATION_H

#include "../Constraint.h"
#include "../../Clock.h"
#include <string>

using std::string;


class Concatenation : public Constraint, public Clock {
public:
    Clock& leftClock;
    Clock& rightClock;

    bool rightIsAConstraint = false;
    bool leftIsAConstraint = false;
    bool isRecursive = false;
    bool followLeft = true;

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;


    Concatenation(Clock& lc, Clock& rc, string name);
    virtual ~Concatenation();

    void nextDelay();

    int getDelay();

    void sched(int next, int start);


};


#endif //SRC_CONCATENATION_H
