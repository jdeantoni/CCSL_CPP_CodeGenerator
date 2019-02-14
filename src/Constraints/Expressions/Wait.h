//
// Created by jdeanton on 5/28/17.
//

#ifndef SRC_WAIT_H
#define SRC_WAIT_H

#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Wait : public Constraint, public Clock {
public:
    Clock& c1;
    int N;
    int initialN;

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;

    Wait(Clock& c1, int waitValue, string name);
    virtual ~Wait();

};


#endif //SRC_WAIT_H
