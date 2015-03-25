#include "Priority.h"

Priority::Priority() {
	_priority = "";
}

bool Priority::checkPriority(std::string &pStr) {
	size_t found = pStr.find_first_of(" ");
	std::string temp = pStr.substr(0, found);
	std::size_t start;

	if (temp == "LOW") {
		_priority = "LOW";
		start = pStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", found);
		pStr = pStr.substr(start);
		return true;

	}
	else if (temp == "MEDIUM") {
		_priority = "MEDIUM";
		start = pStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", found);
		pStr = pStr.substr(start);
		return true;
	}
	else if (temp == "HIGH") {
		_priority = "HIGH";
		start = pStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", found);
		pStr = pStr.substr(start);
		return true;
	}
	else {
		return false;
	}	
}

std::string Priority::getPriority() {
	return _priority;
}
