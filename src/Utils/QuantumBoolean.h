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

std::ostream& operator<<(std::ostream& os, const QuantumBoolean& v);

#endif
