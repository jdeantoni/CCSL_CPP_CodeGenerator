//
// Created by jdeanton on 5/28/17.
//

#ifndef SRC_EXCLUSION_H
#define SRC_EXCLUSION_H

#include "../Constraint.h"
#include "../../Clock.h"

class Exclusion: public Constraint{
        public:
        Clock& c1;
        Clock& c2;

        /**
         * set "False" clock values
         * @return true if something changed, false otherwise
         **/
        virtual  bool evaluate() override;
        virtual  bool propagate() override;
        virtual  void rewrite() override;
        Exclusion(Clock& l, Clock& r);
        virtual ~Exclusion();
};


#endif //SRC_EXCLUSION_H
