#include "Category.h"

//Identifies category from the input and cuts them out from the string
bool Category::extractCat(int cat, std::string &cStr, size_t found) {
	_cat = "";
	
	switch(cat) {
		case 0:
			_cat = "WORK    ";
			break;
		case 1:
			_cat = "PERSONAL";
			break;
		case 2:
			_cat = "ERRAND  ";
			break;
		case 3:
			_cat = "GENERAL ";
			break;
		default:
			return false;
	}
	updateStr(cStr, found);
	return true;
}

//Cuts out the identified category
void Category::updateStr(std::string &cStr, size_t found) {
	if (found == cStr.size()) {
		cStr = "";
		return;
	}
	found = cStr.find_first_not_of(" ", found);
	cStr = cStr.substr(found);
	return;
}

std::string &Category::getCat() {
	return _cat;
}
