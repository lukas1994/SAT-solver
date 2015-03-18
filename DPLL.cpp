#include <iostream>

#include "SATSolver.h"

using namespace std;

class DPLL : public SATSolver {
public:
	DPLL(Formula f) : SATSolver(f) {}

	void solve() {
		cout << "TEST" << endl;
	}
};