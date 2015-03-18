#include <iostream>
#include <cmath>

#include "SATSolver.h"

using namespace std;

class TrivialSATSolver : public SATSolver {
public:
	TrivialSATSolver(Formula formula) : SATSolver(formula) {}

private:
	bool rec_solve(int n) {
		if (n == variables.size()) {
			if (isModel()) return true;
			else return false;
		}
		bool res = rec_solve(n+1);
		if (res) return res;
		a.insert(variables[n]);
		res = rec_solve(n+1);
		if (!res)
			a.erase(variables[n]);
		return res;
	}
public:
	void solve() {
		

		satisfiable = rec_solve(0);
		
		solved = true;
	}
};
