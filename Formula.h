#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include <set>
#include <map>

using namespace std;

typedef int Variable;
typedef set<int> Clause;

class Assignment; // forward referencing

class Formula {
private:
	vector<Clause> clauses;
	set<Variable> variables;

	map<Variable, int> decisions; // variable -> decision_level

public:
	Formula();

	void add(Clause c);

	set<Variable>& getVariables();

	vector<Clause>& getClauses();

	Clause getClause(Assignment a, int i);
	vector<Clause> getClauses(Assignment a);

	// debug
	void printClause(Clause c);
};

#endif