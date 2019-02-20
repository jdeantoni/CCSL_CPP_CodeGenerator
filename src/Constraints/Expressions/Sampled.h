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

    /**
     * set "False" clock values
     * @return true if something changed, false otherwise
     **/
    virtual  bool evaluate() override;
    virtual  bool propagate() override;
    virtual  void rewrite() override;
    virtual  void reset() override;

    Sampled(Clock& sampled, Clock& sampler, string name, bool strict = false);
    virtual ~Sampled() = default;

};


#endif //SRC_SAMPLEDON_H
