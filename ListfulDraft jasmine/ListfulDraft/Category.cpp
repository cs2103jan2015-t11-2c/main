#include "Category.h"

void Category::removeEndChar(std::string &word) {
	size_t found = word.find_last_of(" .,;:?!'");
	
	while (found != std::string::npos) {
		word = word.substr(0, word.size()-1);
		size_t found = word.find_last_of(" .,;:?!'");
	}
}

bool Category::extractCat(std::string &cStr) {
	_cat = "";

	size_t found = cStr.find_first_of(" ");
	std::string temp = cStr.substr(0, found);
	removeEndChar(temp);

	if (temp == "PERSONAL" || temp == "PER") {
		_cat = "PERSONAL";
		updateStr(cStr, found);
		return true;
	}
	else if (temp == "WORK") {
		_cat = "WORK";
		updateStr(cStr, found);
		return true;
	}
	else if (temp == "ERRAND") {
		_cat = "ERRAND";
		updateStr(cStr, found);
		return true;
	}
	else {
		return false;
	}	
}

void Category::updateStr(std::string &cStr, size_t found) {
	found = cStr.find_first_not_of(" ,:;?/()[]{}''""!@#$%^&*-_+=|<>`~", found);

	if (found == std::string::npos) {
		cStr = "";
		return;
	}
	cStr = cStr.substr(found);
}

std::string Category::getCat() {
	if (_cat == "") {
		return "INBOX";
	}
	return _cat;
}
