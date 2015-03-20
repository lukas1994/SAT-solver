#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <map>

#include "Formula.h"

using namespace std;

class Assignment {
private:
	map<Variable, bool> m;

public:
	Assignment();

	void set(Variable var, bool b);
	void unset(Variable var);

	bool isSet(Variable var);
	bool isTrue(Variable var);
	bool isFalse(Variable var);

};

#endif