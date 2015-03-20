#include <iostream>
#include <cassert>
#include <map>
#include <cstdlib>
#include <stdexcept>

#include "SATSolver.h"
#include "utils.h"
#include "SATSolver.h"

using namespace std;

/*
 *
 * DPLL algorithm using uni resolution and clause learning.
 *
 */
class DPLL : public SATSolver {
public:
	DPLL(Formula formula) : SATSolver(formula) {}

private:

	Variable findResVar(Clause c1, Clause c2) {
		for (auto it = c2.begin(); it != c2.end(); it++) {
			if (c1.count(-*it) > 0)
				return abs(*it);
		}
		//throw new runtime_error("no resolvent found");
		return 0;
	}

	Clause resolve(Clause c1, Clause c2, Variable v) {
		if (DEBUG) {
			cout << "resolve clauses wrt variable " << v << ": " << endl;
			f.printClause(c1);
			f.printClause(c2);
		}

		Clause c;
		bool pos = false;
		bool found = false;
		for (auto it = c1.begin(); it != c1.end(); it++) {
			if (*it == v) {
				pos = true;
				found = true;
			}
			else if (*it == -v) {
				pos = false;
				found = true;
			}
			else c.insert(*it);
		}
		if (!found) throw new runtime_error("invalid resolve call");

		found = false;
		for (auto it = c2.begin(); it != c2.end(); it++) {
			if (*it == v) {
				if (pos) throw new runtime_error("invalid resolve call");
				found = true;
			}
			else if (*it == -v) {
				if (!pos) throw new runtime_error("invalid resolve call");
				found = true;
			}
			else c.insert(*it);
		}
		if (!found) throw new runtime_error("invalid resolve call");
		
		if (DEBUG) {
			cout << "result:" << endl;
			f.printClause(c);
		}
		return c;
	}

	pair<Variable, int> unitResoultion() {
		for (int i = 0; i < f.getClauses().size(); i++) {
			Clause c = f.getClause(a, i);
			if (c.count(0) > 0) continue; // clause is true (distinguish from conflict clause)

			if (c.size() == 1) {
				int clause = *c.begin();
				Variable var = abs(clause);
				if (clause > 0) {
					a.set(var, true);
					if (DEBUG)
						cout << "unit resolution on variable " << var << " (clause: " << i << ") -> true" << endl;
				}
				else if (clause < 0) {
					a.set(var, false);
					if (DEBUG)
						cout << "unit resolution on variable " << var << " (clause: " << i << ") -> false" << endl;
				}
				else assert(false);

				return make_pair(var, i);
			}
		}
		return make_pair(-1, -1);
	}

	Clause rec_solve(int decisionLevel = 0) {
		if (DEBUG)
			cout << "rec_solve -------> level: " << decisionLevel << endl;

		while (true) {
			
			vector<Clause> clauses = f.getClauses(a);

			satisfiable = true;
			for (int i = 0; i < clauses.size(); i++) {
				// {0} represents true clause
				// if all clauses are true -> SAT
				if (clauses[i].count(0) == 0) satisfiable = false;

				// {} is a contradictory clause
				if (clauses[i].size() == 0) {
					// start learning
					return f.getClauses()[i];
				}
			}
			if (satisfiable) {
				Clause c;
				c.insert(0);
				return c;
			}

			// try unit resolution
			auto p = unitResoultion();
			if (p.first != -1) {
				Clause c = rec_solve(decisionLevel);
				if (c.size() == 0) { // UNSAT
					a.unset(p.first);
					return c;
				} else if (c.count(0) > 0) {  // SAT
				    return c;
				}

				assert(p.second != -1);

				a.unset(p.first);

				Clause c2 = f.getClauses()[p.second];

				// clause contains implied variable
				if ((c.count(p.first) > 0) || (c.count(-p.first) > 0)) {
					return resolve(c, c2, p.first);
				}
				// clause doesn't contain implied variable
				else {
					if (DEBUG) {
						cout << "clause doesn't contain implied variable: " << p.first << endl;
					}
					return c;
				}
			}

			// make decision
		
			set<Variable> vars = f.getVariables();
			Variable var = 0;
			for (auto it = vars.begin(); it != vars.end(); it++) {
				if (a.isSet(*it)) continue;
				var = *it;
			}
			assert(var != 0);

		
			bool value = rand() % 2;
			a.set(var, value);
			if (DEBUG)
				cout << "make decision: " << var << " -> " << value << endl;

			Clause c = rec_solve(decisionLevel+1);
			
			/*if (c.size() == 0) { // UNSAT
				a.unset(var);
				return c;
			}
			else*/
			if (c.count(0) != 0) { // SAT
				return c;
			}
			else if ((c.count(var) == 0) && (c.count(-var) == 0)) { // conflict doesn't involve this decision
				if (DEBUG)
					cout << "!!! conflict doesn't involve this decision -> " << var << endl;
				a.unset(var);
				return c;
			}

			a.unset(var);

			f.add(c);

			if (DEBUG) {
				cout << "learn clause: ";
				f.printClause(c);
			}

			/*a.set(var, !value);

			return rec_solve(decisionLevel+1);*/

		}
	}

public:
	void solve() {
		if (solved) return;

		while (unitResoultion().first != -1);

		rec_solve();

		solved = true;
	}
};