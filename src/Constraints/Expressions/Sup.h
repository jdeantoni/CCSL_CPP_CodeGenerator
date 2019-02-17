//
// Created by jdeanton on 2/17/19.
//

#ifndef SRC_SUP_H
#define SRC_SUP_H



#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Sup : public Constraint, public Clock {
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

    Sup(Clock& lc, Clock& rc, string name);
    virtual ~Sup() = default;

};


#endif //SRC_SUP_H
