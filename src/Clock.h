/*
 * Clock.h
 *
 *  Created on: Aug 17, 2016
 *      Author: jdeanton
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include <iostream>
#include "NamedElement.h"
#include "Utils/QuantumBoolean.h"

class Clock : public NamedElement{
public:
	int nbTick = 0;
	int randomSeed = time(nullptr);
	bool isDead = false;

	QuantumBoolean status = POSSIBLY;
	Clock(std::string name);
	virtual ~Clock();
	virtual void reset();
	void ticks();
	/**
	 * @note in this method we can implement a simulation policy. For instance to choose true or false according to some probabilities
	 */
	void chooseStatus();
	friend std::ostream& operator<<(std::ostream& os, const Clock& cm);

};

#endif /* CLOCK_H_ */
