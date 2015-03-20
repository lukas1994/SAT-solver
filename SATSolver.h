#ifndef SATSOLVER_H
#define SATSOLVER_H

#include "Assignment.h"
#include "Formula.h"

using namespace std;

#define DEBUG false

class SATSolver {
protected:
	Formula f;
	Assignment a;
	
	bool solved;
	bool satisfiable;

public:
	SATSolver(Formula formula);

protected:
	bool isModel();

public:
	bool isSatisfiable();
	Assignment getModel();
	void printModel();

	virtual void solve() = 0;
};

#endif