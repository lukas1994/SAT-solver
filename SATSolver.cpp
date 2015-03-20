#include <vector>
#include <set>
#include <iostream>

#include "SATSolver.h"
#include "Assignment.h"
#include "Formula.h"

using namespace std;


SATSolver::SATSolver(Formula formula) : f(formula) {}

bool SATSolver::isModel() {
	vector<Clause> clauses = f.getClauses(a);
	for (int i = 0; i < clauses.size(); i++) {
		if (clauses[i].count(0) == 0) return false;
	}
	return true;
}

bool SATSolver::isSatisfiable() {
	if (!solved) solve();
	return satisfiable;
}
Assignment SATSolver::getModel() {
	if (!solved) solve();
	return a;
}
void SATSolver::printModel() {
	if (!solved) solve();
	if (!satisfiable) {
		cout << "not satisfiable" << endl;
		return;
	}
	if (!isModel()) {
		cout << "ERROR!!!" << endl;
		return;
	}
	cout << "satisfiable" << endl << "model:" << endl;
	for (auto it = f.getVariables().begin(); it != f.getVariables().end(); it++) {
		if (a.isTrue(*it))
			cout << "set " << *it << " to true" << endl;
		else
			cout << "set " << *it << " to false" << endl;
	}
}
