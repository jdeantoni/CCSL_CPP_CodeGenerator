//
// Created by jdeanton on 5/24/17.
//

#ifndef FR_INRIA_KAIROS_TIMESQUARE_COMPILEDCODETESTS_TRUTHTABLE_H
#define FR_INRIA_KAIROS_TIMESQUARE_COMPILEDCODETESTS_TRUTHTABLE_H

#include <vector>
using std::vector;

#include "QuantumBoolean.h"

class TruthTable: public vector<vector<QuantumBoolean >>{
public:
    TruthTable(std::initializer_list<vector<QuantumBoolean >> v);

};


#endif //FR_INRIA_KAIROS_TIMESQUARE_COMPILEDCODETESTS_TRUTHTABLE_H
