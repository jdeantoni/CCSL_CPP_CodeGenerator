//
// Created by jdeanton on 2/15/19.
//

#ifndef SRC_SAMPLEDON_H
#define SRC_SAMPLEDON_H




#include "../Constraint.h"
#include "../../Clock.h"
#include "string"

using std::string;

class SampledOn : public Constraint, public Clock {
public:
    Clock& sampledClock;
    Clock& samplingClock;
    bool sampledSeen;

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;

    SampledOn(Clock& sampled, Clock& sampler, string name);
    virtual ~SampledOn() = default;

};


#endif //SRC_SAMPLEDON_H
