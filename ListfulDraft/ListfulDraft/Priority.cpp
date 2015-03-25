#include "Priority.h"

Priority::Priority() {
	_priority = "";
}

void Priority::checkPriority(std::string pStr) {
	size_t found = pStr.find_first_of(" ");
	std::string temp = pStr.substr(0, found);
	if (temp == "LOW") {
		_priority = "LOW";
	}
	else {
		if (temp == "MEDIUM") {
			_priority = "MEDIUM";
		}
		else {
			if (temp == "HIGH") {
				_priority = "HIGH";
			}
			else {
				return;
			}	
		}
	}
}

std::string Priority::getPriority() {

	if (_priority == "") {
		return "LOW";
	} 
	else {
		return _priority;
	}
}
