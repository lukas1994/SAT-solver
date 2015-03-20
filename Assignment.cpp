#include <map>

#include "Formula.h"
#include "Assignment.h"

using namespace std;


Assignment::Assignment() {}

void Assignment::set(Variable var, bool b) {
	m[var] = b;
}
void Assignment::unset(Variable var) {
	m.erase(var);
}

bool Assignment::isSet(Variable var) {
	return m.count(var) > 0;
}
bool Assignment::isTrue(Variable var) {
	return isSet(var) && m[var];
}
bool Assignment::isFalse(Variable var) {
	return isSet(var) && !m[var];
}
