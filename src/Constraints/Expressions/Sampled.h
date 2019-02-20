//
// Created by jdeanton on 2/15/19.
//

#ifndef SRC_SAMPLEDON_H
#define SRC_SAMPLEDON_H




#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class Sampled : public Constraint, public Clock {
public:
    Clock& sampledClock;
    Clock& samplingClock;
    bool sampledSeen = false;
    bool isStrict = false;

    Sampled(Clock& sampled, Clock& sampler, string name, bool strict = false);

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagatesChoice() override;
    virtual  void rewrite() override;
    virtual  void reset() override;
    virtual  bool propagatesDeath() override;

    virtual ~Sampled() = default;

};


#endif //SRC_SAMPLEDON_H
