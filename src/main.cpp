//============================================================================
// Name        : main.cpp
// Author      : Julien Deantoni
// Version     : 0.1
// Copyright   : http://i3s.unice.fr/~deantoni
// Description : Tests for the CCSL C++ compiled code.
//============================================================================

#include <iostream>
#include <vector>
#include <assert.h>

#include "Constraints/Relations/Precedes.h"
#include "Constraints/Relations/SubClock.h"
#include "Constraints/Expressions/Union.h"
#include "Constraints/Relations/Exclusion.h"
#include "Constraints/Expressions/Wait.h"
#include "Constraints/Expressions/Defer.h"
#include "Constraints/Expressions/Concatenation.h"
#include "Utils/Sequence.h"
#include "Constraints/Relations/Causes.h"
#include "Constraints/Expressions/Intersection.h"
#include "Constraints/Expressions/Sampled.h"
#include "Constraints/Expressions/UpTo.h"
#include "Constraints/Expressions/Inf.h"
#include "Constraints/Expressions/Sup.h"

#include "Solver.h"

//remove comment to disable assert
//#define NDEBUG

using namespace std;


void test3(const unsigned int nbSteps) {
    Clock b("b"),a("a");
    Union union1(a,b,"a_union_b");
    Exclusion excl(union1,b);
    Exclusion excl2(union1,a);

    Clock c1("c1"), c2("c2");
    Intersection inter1(c1,c2,"c1_inter_c2");
    Exclusion excl3(c1,c2);


    vector<Constraint*> allConstraintsButExclusions = {&union1, &inter1};
    vector<Constraint*> allExclusions = {&excl,&excl2,&excl3};
    vector<Clock*> allClocks = {&union1, &inter1, &a,&b, &c1, &c2};

    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(a.nbTick == 0);
    assert(b.nbTick == 0);
    assert(union1.nbTick == 0);

    assert(inter1.nbTick == 0);

    cout << endl
	     << "/**********************\n"
         << "*     TEST3 ends      *\n"
         << "**********************/"
         << endl;
}

void test1(const unsigned int nbSteps) {
    Clock a("a"),b("b"), c("c"), d("d"), e("e");
    Precedes prec(a,b); //a < b
    SubClock sub(b,c);  // c C b
    SubClock sub2(c,d);  // d C c

    Union union1(a,b,"a_union_b");
    Union union2(a,b,"a_union_b_2");

    Exclusion excl(a,b);

    Wait e_wait_5(e, 5, "e_wait_5");

    vector<Constraint*> allExclusions = {&excl};
    vector<Constraint*> allConstraintsButExclusions = {&prec, &sub, &sub2, &union1, &union2, &e_wait_5};
    vector<Clock*> allClocks = {&union1, &union2, &a,&b,&c,&d, &e_wait_5, &e};



    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);


    assert(a.nbTick >= b.nbTick);
    assert(b.nbTick <= c.nbTick);
    assert(c.nbTick <= d.nbTick);

    assert(e.nbTick > 5 ? e_wait_5.nbTick == 1 && e_wait_5.isDead : e_wait_5.nbTick == 0 && !e_wait_5.isDead);
    assert(a.nbTick+b.nbTick <= 50);

    assert(union1.nbTick == union2.nbTick);

    cout << endl
         << "/**********************\n"
         << "*     TEST1 ends      *\n"
         << "**********************/"
         << endl;

    return;
}

void test2(const unsigned int nbSteps) {
    Clock c1("c1");
    Clock c2("c2");
    Clock c3("c3");

    Sequence s1({5}, {}, "s1");
    Wait c1_wait_3(c1, 3, "c1_wait_3");
    Defer def(c1,c1_wait_3,s1,"c1DeferedOnw1_5inf");
    Concatenation conc(c1_wait_3, conc, "w1_conc_recursive");
    SubClock c2Subc1(c2,c1);
    Union c1andc3(c1,c3,"c1andc3");
    Exclusion c1Excludesc3(c1,c3);

    Clock c4("c4");
    Clock c5("c5");
    Causes c4CausesC5(c4,c5);

    Intersection c4InterC5(c4,c5,"c4InterC5");


    Clock c6("c6");
    Clock c7("c7");
    UpTo c6upToC7(c6,c7,"c6upToC7");

    Clock c8("c8");
    Clock c9("c9");
    Inf infC8C9(c8,c9,"infC8C9");
    Sup supC8C9(c8,c9,"supC8C9");

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&c1_wait_3, &conc, &def,&c2Subc1, &c1andc3, &c1Excludesc3, &c4CausesC5, &c4InterC5, &c6upToC7, &infC8C9, &supC8C9};
    vector<Clock*> allClocks = {&c1, &c2, &c3, &c1_wait_3, &conc, &def,&c1andc3, &c4,&c5, &c4InterC5,&c6,&c7,&c6upToC7, &c8, &c9, &infC8C9, &supC8C9};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert((infC8C9.nbTick == c8.nbTick) ? supC8C9.nbTick == c9.nbTick : (supC8C9.nbTick == c8.nbTick && infC8C9.nbTick == c9.nbTick));

    cout << endl
         << "/**********************\n"
         << "*     TEST2 ends      *\n"
         << "**********************/"
         << endl;

    return;
}

void testStrictSample(const unsigned int nbSteps) {
    Clock c4("c4");
    Clock c5("c5");
    Causes c4CausesC5(c4,c5);
    Sampled c4SampledOnC5(c4,c5,"c4SampledOnC5", true);


    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&c4SampledOnC5, &c4CausesC5};
    vector<Clock*> allClocks = {&c4, &c5, &c4SampledOnC5};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(c4.nbTick >= 1 && c4SampledOnC5.nbTick == 1 && c4SampledOnC5.isDead);

    cout << endl
         << "/************************\n"
         << "*test strict sample ends*\n"
         << "************************/"
         << endl;

}

void testSample(const unsigned int nbSteps) {
    Clock c5("c5");
    Sampled meSampledOnC5(meSampledOnC5,c5,"meSampledOnC5", false);


    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&meSampledOnC5};
    vector<Clock*> allClocks = {&c5, &meSampledOnC5};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(meSampledOnC5.nbTick <= 1 && c5.nbTick >=1);

    cout << endl
         << "/**********************\n"
         << "*   test sample ends  *\n"
         << "**********************/"
         << endl;

}

void testDeadlock1(const unsigned int nbSteps) {
    Clock a("a"), b("b");
    Precedes prec(a, b); //a < b
    Precedes badPrec(b,a); //b < a ==> deadlock

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&prec, &badPrec};
    vector<Clock*> allClocks = {&a, &b};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(a.nbTick == 0 && b.nbTick == 0);

    cout << endl
         << "/**********************\n"
         << "*   DEADLOCK1 ends    *\n"
         << "**********************/"
         << endl;

}

void testDeadlock2(const unsigned int nbSteps) {
    Clock a("a"), b("b"), c("c");
    Precedes prec(a, b); //a < b
    SubClock sub(c, b);  // c C b
    Precedes badPrec(c,a); //c < a ==> deadlock

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&prec, &badPrec, &sub};
    vector<Clock*> allClocks = {&a, &b, &c};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(a.nbTick == 0 && b.nbTick == 0 && c.nbTick == 0);

    cout << endl
         << "/**********************\n"
         << "*     DEADLOCK2 ends  *\n"
         << "**********************/"
         << endl;

}

void test4(const unsigned int nbSteps) {
    Clock b("b"),a("a");
    Union union1(a,b,"a_union_b");
    Exclusion excl(union1,b);

    Clock c1("c1"), c2("c2");
    Intersection inter1(c1,c2,"c1_inter_c2");
    Exclusion excl3(c1,c2);

    vector<Constraint*> allConstraintsButExclusions = {&union1, &inter1};
    vector<Constraint*> allExclusions = {&excl,&excl3};
    vector<Clock*> allClocks = {&union1, &inter1, &a,&b, &c1, &c2};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    assert(b.nbTick == 0);
    assert(inter1.nbTick == 0);

    //runSequentialSimulation(nbSteps, managers);
//runParallelSimulation(nbSteps, managers);
    cout << endl
         << "/**********************\n"
         << "*     TEST4 ends      *\n"
         << "**********************/"
         << endl;
}

void testDeathPropagation(const unsigned int nbSteps) {
    Clock c5("c5");
    Clock c4("c4");
    Precedes c4precC5(c4,c5);
    UpTo c4UpToC5(c4,c5,"c4UpToC5");

    Clock willDieWhenSizeOfc4UpToC5("willDieWhenSizeOfc4UpToC5");
    Precedes deathPropagator(c4UpToC5,willDieWhenSizeOfc4UpToC5);

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&c4precC5,&c4UpToC5, &deathPropagator};
    vector<Clock*> allClocks = {&c4, &c5, &c4UpToC5, &willDieWhenSizeOfc4UpToC5};


    Solver solver(allClocks, allConstraintsButExclusions, allExclusions);
    solver.simulate(nbSteps);

    cout << endl
         << "/***********************************\n"
         << "*   test death propagation 1 ends  *\n"
         << "************************************/"
         << endl;

}

int main() {
    const unsigned int nbSteps = 50;

//    /**
//    * TEST1
//    */
//    test1(nbSteps);
//
//
//    /**
//    * TEST2
//    */
//
//    test2(nbSteps);
//
//
//    /**
//    * TEST3
//    */
//
//    test3(nbSteps);
//
//    /**
//    * TEST DEADLOCK 1
//    */
//
//    testDeadlock1(nbSteps);
//
//    /**
//    * TEST DEADLOCK 1
//    */
//
//    testDeadlock2(nbSteps);
//
//    /**
//    * TEST 4
//    */
//
//    test4(nbSteps);
//
//    /**
//     * TEST sampled
//     */
//
//    testSample(nbSteps);
//
//    /**
//   * TEST sampled
//   */
//    testStrictSample(nbSteps);

    /**
     * test death propagation 1
     */
    testDeathPropagation(nbSteps);
    return 0;
}


