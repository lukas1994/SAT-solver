#ifndef SATSOLVER_H
#define SATSOLVER_H

#include <vector>
#include <set>
#include <iostream>

using namespace std;

typedef int Variable;
typedef set<Variable> Clause;
typedef vector<Clause> Formula;

typedef set<Variable> Assignment;

class SATSolver {
protected:
	Formula f;
	Assignment a;
	vector<Variable> variables;

	bool solved;
	bool satisfiable;

public:
	SATSolver(Formula formula) : f(formula) {
		for (auto it = f.begin(); it != f.end(); it++) {
			Clause c = *it;
			for (auto var = c.begin(); var != c.end(); var++) {
				if (*var == 0) throw new exception(); // invalid formula
			}
		}

		// get list of variables
		set<Variable> vars;
		for (auto it = f.begin(); it != f.end(); it++) {
			Clause c = *it;
			for (auto var = c.begin(); var != c.end(); var++) {
				vars.insert(abs(*var));
			}
		}
		variables = vector<Variable>(vars.begin(), vars.end());
	}

protected:
	bool isModel() {
		for (auto it = f.begin(); it != f.end(); it++) {
			Clause c = *it;
			bool ok = false;
			for (auto var = c.begin(); var != c.end(); var++) {
				if (((*var > 0) && (a.count(*var) == 1)) ||
					((*var < 0) && (a.count(*var) == 0))) {
					ok = true;
					break;
				}
			}
			if (!ok)
				return false;
		}
		return true;
	}

public:
	bool isSatisfiable() {
		if (!solved) solve();
		return satisfiable;
	}
	Assignment getModel() {
		if (!solved) solve();
		return a;
	}
	void printModel() {
		if (!solved) solve();
		if (!satisfiable) {
			cout << "not satisfiable" << endl;
			return;
		}
		for (auto it = variables.begin(); it != variables.end(); it++) {
			if (a.count(*it) > 0)
				cout << "set " << *it << " to true" << endl;
			else
				cout << "set " << *it << " to false" << endl;
		}
	}

	virtual void solve() = 0;
};

#endif