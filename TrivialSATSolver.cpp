#include <iostream>
#include <cmath>

#include "SATSolver.h"

using namespace std;

class TrivialSATSolver : public SATSolver {
public:
	TrivialSATSolver(Formula formula) : SATSolver(formula) {}

private:
	vector<int> variables;

	bool rec_solve(int n) {
		if (n == variables.size()) {
			if (isModel()) return true;
			else return false;
		}
		a.set(variables[n], false);
		bool res = rec_solve(n+1);
		if (res) return res;
		a.set(variables[n], true);
		res = rec_solve(n+1);
		if (!res)
			a.unset(variables[n]);
		return res;
	}
public:
	void solve() {
		if (solved) return;
		
		set<Variable> varSet = f.getVariables();
		variables = vector<Variable>(varSet.begin(), varSet.end());
		
		satisfiable = rec_solve(0);
		
		solved = true;
	}
};
