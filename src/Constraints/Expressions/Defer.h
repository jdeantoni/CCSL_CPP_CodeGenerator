//
// Created by jdeanton on 5/29/17.
//

#ifndef SRC_DEFER_H
#define SRC_DEFER_H

#include "../Constraint.h"
#include "../../Clock.h"
#include "../../Utils/Sequence.h"

#include "deque"
#include "string"

using std::string;
using std::deque;

class Defer : public Constraint, public Clock {
public:
    Clock& baseClock;
    Clock& delayClock;
    Sequence sigma;
    deque<int> ds;

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;


    Defer(Clock& bc, Clock& dc, Sequence seq, string name);
    virtual ~Defer();

    void nextDelay();

    int getDelay();

    void sched(int next, int start);

private:
    bool getBeta();

};


#endif //SRC_DEFER_H
