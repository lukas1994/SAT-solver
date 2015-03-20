#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <stdexcept>

#include "Formula.h"
#include "Assignment.h"
#include "utils.h"
#include "SATSolver.h"

using namespace std;

Formula::Formula() {}

void Formula::add(Clause c) {
	clauses.push_back(c);
	for (auto it = c.begin(); it != c.end(); it++) {
		if (*it == 0) throw new runtime_error("0 is not a valid literal");
		variables.insert(abs(*it));
	}
}

set<Variable>& Formula::getVariables() {
	return variables;
}

vector<Clause>& Formula::getClauses() {
	return clauses;
}

Clause Formula::getClause(Assignment a, int i) {
	Clause c;
	bool addClause = true;
	for (auto it = clauses[i].begin(); it != clauses[i].end(); it++) {
		int var = abs(*it);
		if (!a.isSet(var)) {
			c.insert(*it);
			continue;
		}
		if ((*it > 0 && a.isTrue(var)) || (*it < 0 && a.isFalse(var))) {
			addClause = false;
			break;
		}
		else if ((*it > 0 && a.isFalse(var)) || (*it < 0 && a.isTrue(var)))
			continue;
		else
			c.insert(*it);
	}
	if (addClause)
		return c;

	c.clear();
	c.insert(0); // -> distinguish from conflict clause

	return c;
}

vector<Clause> Formula::getClauses(Assignment a) {
	vector<Clause> cs;
	for (int i = 0; i < clauses.size(); i++) {
		Clause c;
		bool addClause = true;
		for (auto it = clauses[i].begin(); it != clauses[i].end(); it++) {
			int var = abs(*it);
			if (!a.isSet(var)) {
				c.insert(*it);
				continue;
			}
			if ((*it > 0 && a.isTrue(var)) || (*it < 0 && a.isFalse(var))) {
				addClause = false;
				break;
			}
			else if ((*it > 0 && a.isFalse(var)) || (*it < 0 && a.isTrue(var)))
				continue;
			else
				c.insert(*it);
		}
		if (addClause)
			cs.push_back(c);
		else {
			c.clear();
			c.insert(0); // -> distinguish from conflict clause
			cs.push_back(c);
		}
	}

	if (DEBUG) {
		cout << "********* print clauses **********" << endl;
		for (int i = 0; i < cs.size(); i++) {
			printClause(cs[i]);
		}
		cout << "**********************************" << endl;
	}

	return cs;
}

// debug
void Formula::printClause(Clause c) {
	for (auto it = c.begin(); it != c.end(); it++)
		cout << *it << " ";
	cout << endl;
}
