/*
 * QuanticBoolean.h
 *
 *  Created on: Aug 25, 2016
 *      Author: jdeanton
 */

#ifndef QUANTUM_BOOLEAN_H_
#define QUANTUM_BOOLEAN_H_

#include "iostream"

enum QuantumBoolean{
		TRUE,
		POSSIBLY,
		FALSE
};

inline std::ostream& operator<<(std::ostream& os, QuantumBoolean& v){
	switch (v){
		case TRUE: os << "TRUE"; return os;
		case POSSIBLY: os << "POSSIBLY"; return os;
		case FALSE: os << "FALSE"; return os;
	}
	return os;
}

#endif
