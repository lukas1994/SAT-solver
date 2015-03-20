#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Formula.h"
#include "SATSolver.h"
#include "TrivialSATSolver.cpp"
#include "DPLL.cpp"

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
			f.add(c);
			cnt++;
		}
		if (cnt == numClauses)
			break;
	}

	return f;
}
int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "USAGE: " << argv[0] << " [.cnf FILE]" << endl;
		return 0;
	}
	string path = string(argv[1]);
	Formula f = cnfFileToFormula(path);

	//TrivialSATSolver sat(f);
	DPLL sat(f);
	sat.solve();
	sat.printModel();

	return 0;
}