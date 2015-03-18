#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SATSolver.h"
#include "TrivialSATSolver.cpp"

using namespace std;

Formula cnfFileToFormula(string path) {
	ifstream infile(path);
	string line;

	Formula f;

	bool started = false;
	string s;
	int numVars, numClauses;
	int cnt = 0;
	while (getline(infile, line)) {
		istringstream iss(line);
		if (!started) {
			iss >> s;
			if (s == "c") continue;
			if (s == "p") {
				iss >> s; // "cnf"
				iss >> numVars >> numClauses;
				started = true;
			}
		}
		else {
			Clause c;
			int var;
			while (iss >> var) if (var != 0) c.insert(var);
			/*cout << "clause " << cnt << ": ";
			for (auto it = c.begin(); it != c.end(); it++)
				cout << *it << " ";
			cout << endl;*/
			f.push_back(c);
			cnt++;
		}
	}

	return f;
}
int main() {
	Formula f = cnfFileToFormula("examples/test16.cnf");

	TrivialSATSolver sat(f);
	sat.solve();
	sat.printModel();

	return 0;
}