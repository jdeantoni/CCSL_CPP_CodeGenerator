//
// Created by jdeanton on 5/29/17.
//

#include "Sequence.h"

/*
 * @return -1 if the sequence is empty
 */
int Sequence::nextHead() {
    if (! finitePart.empty()){
        int nextInt = finitePart.front();
        finitePart.pop_front();
        return nextInt;
    }
    if (infinitePart.empty()){
        return -1;
    }

    if ((infinitePartIterator - infinitePart.begin()) >= infinitePart.size()){
        infinitePartIterator = infinitePart.begin();
    }
    int nextInt = *infinitePartIterator;
    ++infinitePartIterator;
    return nextInt;
}

Sequence::Sequence(list<int> finitePart, vector<int> infinitePart, string name)
:finitePart(finitePart), infinitePart(infinitePart), NamedElement(name)
{
    infinitePartIterator = this->infinitePart.begin();
}

bool Sequence::empty() {
    return infinitePart.empty() && finitePart.empty();
}

