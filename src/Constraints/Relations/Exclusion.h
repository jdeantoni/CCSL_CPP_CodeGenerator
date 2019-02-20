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

        Exclusion(Clock& l, Clock& r);
        /**
         * set "False" clock values
         * @return true if something changed, false otherwise
         **/
        virtual  bool evaluate() override;
        virtual  bool propagatesChoice() override;
        virtual  void rewrite() override;
        virtual  bool propagatesDeath() override;

        virtual ~Exclusion();
};


#endif //SRC_EXCLUSION_H
