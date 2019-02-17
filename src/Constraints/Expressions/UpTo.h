//
// Created by jdeanton on 2/16/19.
//

#ifndef SRC_UPTO_H
#define SRC_UPTO_H


#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class UpTo : public Constraint, public Clock {
public:
    Clock& clockToFollow;
    Clock& killer;

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;

    UpTo(Clock& toFollow, Clock& theKiller, string name);
    virtual ~UpTo() = default;

};


#endif //SRC_UPTO_H
