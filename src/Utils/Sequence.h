//
// Created by jdeanton on 5/29/17.
//

#ifndef SRC_SEQUENCE_H
#define SRC_SEQUENCE_H


#include "../NamedElement.h"
#include "vector"
#include "list"
#include "string"

using std::vector;
using std::list;
using std::string;

class Sequence: public NamedElement {

public:
    list<int> finitePart;
    vector<int> infinitePart;
    vector<int>::iterator infinitePartIterator;

    int nextHead();
    bool empty();
    Sequence(list<int> finitePart, vector<int> infinitePart, string name);
    ~Sequence() = default;

};


#endif //SRC_SEQUENCE_H
