//
// Created by jdeanton on 2/18/19.
//

#include "QuantumBoolean.h"

std::ostream& operator<<(std::ostream& os, const QuantumBoolean& v){
    switch (v){
        case QuantumBoolean::TRUE: os << "TRUE"; return os;
        case QuantumBoolean::POSSIBLY: os << "POSSIBLY"; return os;
        case QuantumBoolean::FALSE: os << "FALSE"; return os;
    }
    return os;
}