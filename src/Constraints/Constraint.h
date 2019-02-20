//
// Created by jdeanton on 5/24/17.
//

#ifndef SRC_RELATION_H
#define SRC_RELATION_H


class Constraint {
public:
    virtual void reset();
    virtual  bool evaluate()=0;
    virtual  bool propagatesChoice()=0;
    virtual  void rewrite()=0;
    virtual  bool propagatesDeath()=0;
};


#endif //SRC_RELATION_H
