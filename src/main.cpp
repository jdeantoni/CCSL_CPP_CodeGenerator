//============================================================================
// Name        : templates.cpp
// Author      : Julienb Deantoni
// Version     :
// Copyright   : http://i3s.unice.fr/~deantoni
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
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
#include "Constraints/Expressions/SampledOn.h"
#include "Constraints/Expressions/UpTo.h"
#include "Constraints/Expressions/Inf.h"
#include "Constraints/Expressions/Sup.h"

//remove comment to disable assert
//#define NDEBUG

void propagatesChoice(const vector<Clock *> &allClocks, const vector<Constraint *> &allConstraints);

void simulate(const unsigned int nbSteps, vector<Constraint *> &allConstraintsButExclusions,
              vector<Constraint *> &allExclusions, const vector<Clock *> &allClocks);

using namespace std;

//void runSequentialSimulation(unsigned int nbSteps, vector<ClockManager*> managers) {
//	cout << "Sequential Simulation starts" << endl;
//	for (unsigned int currentStep= 0; currentStep < nbSteps; currentStep++) {
//		cout <<"step " << currentStep <<endl;
//		for_each(managers.begin(), managers.end(), [](ClockManager* c) {
//			c->run();
//			cout << *c<<endl;
//		});
//	}
//}


//warning, here infinitePartIterator can be unfair, for instance if b is managed an hundred times before a, infinitePartIterator can not tick.
//It is not wrong but... unfair when the number of steps is finite


/*void runOneManager(unsigned int nbSteps, ClockManager* pcm){
	for (unsigned int currentStep= 0; currentStep < nbSteps; currentStep++) {
		cout <<"step " << currentStep <<" of " << pcm <<endl;
		pcm->run();
		cout << *pcm <<endl;
	}
}

void runParallelSimulation(unsigned int nbSteps, vector<ClockManager*> managers) {
	cout << "Parallel Simulation starts" << endl;
	std::vector<std::thread*> allThreads;
		for(auto infinitePartIterator = managers.begin(); infinitePartIterator < managers.end(); infinitePartIterator++){
			ClockManager* pcm = *infinitePartIterator;
			cout << "#######" <<pcm <<endl;
			allThreads.push_back(
					new std::thread(runOneManager,nbSteps,pcm)
			);

		}
		for(auto infinitePartIterator = allThreads.begin(); infinitePartIterator < allThreads.end(); infinitePartIterator++){
			(*infinitePartIterator)->join();
			delete (*infinitePartIterator);
		}
}*/

//std::thread t1(function());

ostream& operator<<(ostream& os, const vector<Clock*> vect_pt_c){
  for(Clock* pt_c : vect_pt_c){
      assert(pt_c != nullptr);
      os << *pt_c << "   |   ";
  }
  return os;
}

vector<Constraint *> operator+(const vector<Constraint *>& v1, const vector<Constraint *>& v2){
    vector<Constraint *> all = v1;
    for(Constraint* pt_c : v2){
        all.push_back(pt_c);
    }
    return all;
}



void solve(const vector<Clock *> &allClocks, vector<Constraint *> &allConstraintsButExclusions, vector<Constraint*> &allExclusions) {
    for(Constraint* pt_r: allConstraintsButExclusions + allExclusions) {
            pt_r->evaluate();
    }

    for(Clock* pt_c : allClocks) {
        if (pt_c->status == POSSIBLY) {
            pt_c->chooseStatus();
//            cout << allClocks <<endl;
            propagatesChoice(allClocks, allExclusions + allConstraintsButExclusions);
        }
    }

    for(Clock* pt_c : allClocks){
        if(pt_c->status == TRUE){
            pt_c->ticks();
        }
    }
}


void simulate(const unsigned int nbSteps, vector<Constraint *> &allConstraintsButExclusions,
              vector<Constraint *> &allExclusions, const vector<Clock *> &allClocks) {
    for (unsigned int currentStep= 0; currentStep < nbSteps; currentStep++) {
        cout << "-------------step " << currentStep << endl;


        solve(allClocks, allConstraintsButExclusions, allExclusions);

        for(Clock* pt_c: allClocks) {
            cout << *pt_c <<endl;
        }

        for(Constraint* pt_r: allConstraintsButExclusions + allExclusions) {
            pt_r->rewrite();
        }


        for(Clock* pt_c : allClocks){
            pt_c->status = POSSIBLY;
        }
    }
}


void propagatesChoice(const vector<Clock *> &allClocks, const vector<Constraint *> &allConstraints) {
            bool fixPointReached = true;
            do{
                fixPointReached = true;
                for(Constraint* pt_c : allConstraints){
                    bool isStable = pt_c->propagate();
                    fixPointReached = fixPointReached && isStable;
                }
            }while (! fixPointReached);
}

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

    simulate(nbSteps, allConstraintsButExclusions, allExclusions, allClocks);

    assert(a.nbTick == 0);
    assert(b.nbTick == 0);
    assert(union1.nbTick == 0);

    assert(inter1.nbTick == 0);

    //runSequentialSimulation(nbSteps, managers);
//runParallelSimulation(nbSteps, managers);
    cout << endl
	     << "/**********************\n"
         << "*     TEST2 ends      *\n"
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


    simulate(nbSteps, allConstraintsButExclusions, allExclusions, allClocks);

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

    SampledOn c4ampledOnC5(c4,c5,"c4SampledOnC5");

    Intersection c4InterC5(c4,c5,"c4InterC5");


    Clock c6("c6");
    Clock c7("c7");
    UpTo c6upToC7(c6,c7,"c6upToC7");

    Clock c8("c8");
    Clock c9("c9");
    Inf infC8C9(c8,c9,"infC8C9");
    Sup supC8C9(c8,c9,"supC8C9");

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&c1_wait_3, &conc, &def,&c2Subc1, &c1andc3, &c1Excludesc3, &c4CausesC5, &c4InterC5, &c4ampledOnC5, &c6upToC7, &infC8C9, &supC8C9};
    vector<Clock*> allClocks = {&c1, &c2, &c3, &c1_wait_3, &conc, &def,&c1andc3, &c4,&c5, &c4InterC5, &c4ampledOnC5,&c6,&c7,&c6upToC7, &c8, &c9, &infC8C9, &supC8C9};

    simulate(nbSteps, allConstraintsButExclusions, allExclusions, allClocks);

    assert((infC8C9.nbTick == c8.nbTick) ? supC8C9.nbTick == c9.nbTick : (supC8C9.nbTick == c8.nbTick && infC8C9.nbTick == c9.nbTick));

    cout << endl
         << "/**********************\n"
         << "*     TEST2 ends      *\n"
         << "**********************/"
         << endl;

    return;
}

void testDeadlock1(const unsigned int nbSteps) {
    Clock a("a"), b("b");
    Precedes prec(a, b); //a < b
    Precedes badPrec(b,a); //b < a ==> deadlock

    vector<Constraint*> allExclusions = {};
    vector<Constraint*> allConstraintsButExclusions = {&prec, &badPrec};
    vector<Clock*> allClocks = {&a, &b};

    simulate(nbSteps, allConstraintsButExclusions, allExclusions, allClocks);

    assert(a.nbTick == 0 && b.nbTick == 0);

    cout << endl
         << "/**********************\n"
         << "*     TEST2 ends      *\n"
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

    simulate(nbSteps, allConstraintsButExclusions, allExclusions, allClocks);

    assert(a.nbTick == 0 && b.nbTick == 0 && c.nbTick == 0);

    cout << endl
         << "/**********************\n"
         << "*     TEST2 ends      *\n"
         << "**********************/"
         << endl;

}

int main() {
	const unsigned int nbSteps = 50;

 /**
 * TEST1
 */
  test1(nbSteps);


 /**
 * TEST2
 */

//  test2(nbSteps);


 /**
 * TEST3
 */

  test3(nbSteps);

 /**
 * TEST DEADLOCK 1
 */

//    testDeadlock1(nbSteps);

 /**
 * TEST DEADLOCK 1
 */

    testDeadlock2(nbSteps);


    return 0;
}


