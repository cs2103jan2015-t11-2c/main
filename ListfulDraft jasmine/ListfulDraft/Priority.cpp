#include "Priority.h"

void Priority::updateStr(std::string &pStr, size_t found) {
	found = pStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", found);

	if (found == std::string::npos) {
		pStr = "";
		return;
	}
	pStr = pStr.substr(found);
	return;
}

bool Priority::extractPriority(std::string &pStr) {
	_priority = "";

	size_t found = pStr.find_first_of(" ");
	std::string temp = pStr.substr(0, found);

	if (temp == "LOW" || temp == "L") {
		_priority = "LOW";
		updateStr(pStr, found);
		return true;
	}
	else if (temp == "MEDIUM" || temp == "MED" || temp == "M") {
		_priority = "MEDIUM";
		updateStr(pStr, found);
		return true;
	}
	else if (temp == "HIGH" || temp == "H") {
		_priority = "HIGH";
		updateStr(pStr, found);
		return true;
	}
	else {
		return false;
	}
}

std::string Priority::getPriority() {
	if (_priority == "") {
		return "LOW";
	}
	return _priority;
}