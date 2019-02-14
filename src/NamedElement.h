/*
 * NamedElement.h
 *
 *  Created on: Aug 17, 2016
 *      Author: jdeanton
 */

#ifndef NAMEDELEMENT_H_
#define NAMEDELEMENT_H_

#include <string>

class NamedElement {
public:
	std::string name;


	NamedElement(std::string name);
	virtual ~NamedElement();
};

#endif /* NAMEDELEMENT_H_ */
