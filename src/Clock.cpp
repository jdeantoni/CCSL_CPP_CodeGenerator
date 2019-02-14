/*
 * Clock.cpp
 *
 *  Created on: Aug 17, 2016
 *      Author: jdeanton
 */

#include "Clock.h"
#include <iostream>

using std::cout;
using std::endl;

Clock::Clock(std::string name): NamedElement(name),status(POSSIBLY) {
	srand(this->randomSeed);
}

Clock::~Clock() {
}

void Clock::ticks(){
	this->nbTick++;
}

std::ostream& operator<<(std::ostream& os, const Clock& c){
	os << "Clock " << c.name << ": " << c.nbTick;
    if(c.isDead){
        os << " (is dead)";
    }
	return os;
}

/**
 * @note
 * without comments it implements a random poilicy, with the comment of everything but status = TRUE it implements a non exact max card policy
 */
void Clock::chooseStatus() {
  int r = (rand()%2);
	if (r == 1 ){
		status = TRUE;
	}else{
		status = FALSE;
	}
}

void Clock::reset() {
	this->isDead = false;
//	this->status = POSSIBLY; // should not be here to avoif blurring F set during rewriting rules
}
