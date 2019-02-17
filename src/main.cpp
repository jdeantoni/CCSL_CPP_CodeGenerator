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


void solve(const vector<Clock *> &allClocks, vector<Constraint *> &allConstraints) {
    for_each(allConstraints.begin(), allConstraints.end(), [](Constraint* pt_r) {
            pt_r->evaluate();
        });

    for(Clock* pt_c : allClocks){
        if (pt_c->status == POSSIBLY){
            pt_c->chooseStatus();

            bool fixPointReached = true;
            do{
                fixPointReached = true;
                for(Constraint* pt_c : allConstraints){
                    bool isStable = pt_c->propagate();
                    fixPointReached = fixPointReached && isStable;
                }
            }while (! fixPointReached);
        }
    }
    for(Clock* pt_c : allClocks){
        if(pt_c->status == TRUE){
            pt_c->ticks();
        }
    }
}

int main() {
	const unsigned int nbSteps = 50;
//	Clock a("a"),b("b"), c("c"), d("d"), e("e");
//	Precedes prec(a,b); //a < b
//    // Precedes badPrec(b,a); //b < a ==> deadlock
//    SubClock sub(b,c);  // c C b
//    //Precedes badPrec(c,a); //c < a ==> deadlock
//    SubClock sub2(c,d);  // d C c
//
//    Union union1(a,b,"a_union_b");
//    Union union2(a,b,"a_union_b_2");
//
//    Exclusion excl(a,b);
//
//    Wait w1(e, 5, "e_wait_5");
//
//    vector<Constraint*> allConstraints = {&prec, &sub, &sub2, &union1, &union2,&excl, &w1};
//    vector<Clock*> allClocks = {&union2, &a,&b,&c,&d,&union1, &w1, &e};

    Clock c1("c1");
    Clock c2("c2");
    Clock c3("c3");

    Sequence s1({}, {5}, "s1");
    Wait w1(c1, 3, "c1_wait_3");
    Defer def(c1,w1,s1,"c1DeferedOnw1_5inf");
    Concatenation conc(w1, conc, "w1_conc_recursive");
    SubClock c2Subc1(c2,c1);
    Union c1andc3(c1,c3,"c1andc3)");
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

    vector<Constraint*> allConstraints = {&w1, &conc, &def,&c2Subc1, &c1andc3, &c1Excludesc3, &c4CausesC5, &c4InterC5, &c4ampledOnC5, &c6upToC7, &infC8C9, &supC8C9};
    vector<Clock*> allClocks = {&c1, &c2, &c3, &w1, &conc, &def,&c1andc3, &c4,&c5, &c4InterC5, &c4ampledOnC5,&c6,&c7,&c6upToC7, &c8, &c9, &infC8C9, &supC8C9};

	for (unsigned int currentStep= 0; currentStep < nbSteps; currentStep++) {
        cout << "-------------step " << currentStep << endl;


        solve(allClocks, allConstraints);

        for(Clock* pt_c: allClocks) {
            cout << *pt_c <<endl;
        }

        for_each(allConstraints.begin(), allConstraints.end(), [](Constraint* pt_r) {
            pt_r->rewrite();
        });


        for(Clock* pt_c : allClocks){
            pt_c->status = POSSIBLY;
        }
	}


	//runSequentialSimulation(nbSteps, managers);
	//runParallelSimulation(nbSteps, managers);
	cout << "Simulation ends" << endl;
	return 0;
}
