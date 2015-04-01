#include "Priority.h"

void Priority::removeEndChar(std::string &word) {
	size_t found = word.find_last_of(" .,;:?!'");
	
	while (found != std::string::npos) {
		word = word.substr(0, word.size()-1);
		found = word.find_last_of(" .,;:?!'");
	}
	return;
}

//Cuts out the identified priority
void Priority::updateStr(std::string &pStr, size_t found) {
	found = pStr.find_first_not_of(" ", found);

	if (found == std::string::npos) {
		pStr = "";
		return;
	}
	pStr = pStr.substr(found);
	return;
}

//Identifies category from the input and cuts them out from the string
bool Priority::extractPriority(std::string &pStr) {
	_priority = "";

	size_t found = pStr.find_first_of(" ");
	if (found == std::string::npos) {
		found = pStr.size();
	}
	std::string temp = pStr.substr(0, found);
	removeEndChar(temp);

	if (temp == "LOW" || temp == "L") {
		_priority = "LOW  ";
		updateStr(pStr, found);
		return true;
	}
	else if (temp == "MEDIUM" || temp == "MED" || temp == "M") {
		_priority = "MED  ";
		updateStr(pStr, found);
		return true;
	}
	else if (temp == "HIGH" || temp == "H") {
		_priority = "HIGH ";
		updateStr(pStr, found);
		return true;
	}
	else {
		return false;
	}
}

std::string &Priority::getPriority() {
	return _priority;
}