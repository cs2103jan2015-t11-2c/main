#include "Priority.h"

//Identifies category from the input and cuts them out from the string
bool Priority::extractPriority(int impt, std::string &pStr, size_t found) {
	_priority = "";

	switch (impt) {
		case 0:
			_priority = "LOW";
			break;
		case 1:
			_priority = "MED";
			break;
		case 2:
			_priority = "HIGH";
			break;
		default:
			return false;
	}
	updateStr(pStr, found);
	return true;
}

//Cuts out if priority is identified
void Priority::updateStr(std::string &pStr, size_t found) {
	if (found == pStr.size()) {
		pStr = "";
		return;
	}
	found = pStr.find_first_not_of(" ", found);
	pStr = pStr.substr(found);
	return;
}

std::string &Priority::getPriority() {
	return _priority;
}