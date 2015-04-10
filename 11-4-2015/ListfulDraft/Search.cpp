#include "Search.h"

//Displays all contents that contains the keywords
bool Search::searchFile(DataStore &data, std::string keyword, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	Add add;
	Display display;
	data.clearData(floating, scheduled, deadline);

	switch (_category) {
		case SUBJECT:
			return foundSubject(data, keyword, errMsg, floating, scheduled, deadline, add, display);
		case DATE:
			return foundDate(data, keyword, errMsg, floating, scheduled, deadline, add, display);
		case TIME:
			return foundTime(data, keyword, errMsg, floating, scheduled, deadline, add, display);
		case CATEGORY:{
			if (keyword[0] == 'W' || keyword[0] == 'w'){
				keyword = "WORK"; 
			}
			else if(keyword[0] == 'I' || keyword[0] == 'i'){
				keyword = "GENERAL";
			}
			else if(keyword[0] == 'P' || keyword[0] == 'p'){
				keyword = "PERSONAL";
			}
			else if(keyword[0] == 'E' || keyword[0] == 'e'){
				keyword = "ERRAND";
			}
			return foundCatPriority(data, keyword, errMsg, floating, scheduled, deadline, add, display);
			}
		case PRIORITY: {
			if (keyword[0] == 'l' || keyword[0] == 'L'){
				keyword = "LOW"; 
			}
			else if(keyword[0] == 'h' || keyword[0] == 'H'){
				keyword = "HIGH";
			}
			else if(keyword[0] == 'm' || keyword[0] == 'M'){
				keyword = "MED";
			}
			return foundCatPriority(data, keyword, errMsg, floating, scheduled, deadline, add, display);
			}
		default:
			return false;
	}
}

bool Search::foundCatPriority(DataStore &data, std::string &keyword, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, Add &add, Display &display) {
	size_t found = 0;
	data.getTempData().clear();
	std::ostringstream oss;
	bool isTemp = true;

	assert(!keyword.empty());
	for (int index = 0; index < data.getData().size(); index++) {
		if (keyword == data.getData()[index].priority) {
			data.get_tempEntry() = data.getData()[index];
			add.addContent(data, oss, floating, scheduled, deadline, isTemp);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg, display);
	return true;
}

bool Search::foundTime(DataStore &data, std::string &keyword, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, Add &add, Display &display) {
	bool found = false;
	data.getTempData().clear();
	std::ostringstream oss;
	bool notTrue = false;
	bool isTemp = true;
	
	assert(!keyword.empty());
	for (int index = 0; index < data.getData().size(); index++) {
		if(display.getTime(data, index, notTrue) == keyword){
			data.get_tempEntry() = data.getData()[index];
			add.addContent(data, oss, floating, scheduled, deadline, isTemp);
			found = true;
		}
	}
	printSearchedContent(data, errMsg, display);
	return found;
}

bool Search::foundDate(DataStore &data, std::string &keyword, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, Add &add, Display &display) {
	bool found = false;
	data.getTempData().clear();
	assert(!keyword.empty());
	std::ostringstream oss;
	bool notTrue = false;
	bool isTemp = true;

	for (int index = 0; index < data.getData().size(); index++) {
		if(display.getDate(data, index, notTrue) == keyword){
			data.get_tempEntry() = data.getData()[index];
			add.addContent(data, oss, floating, scheduled, deadline, isTemp);
			found = true;
		}
	}
	printSearchedContent(data, errMsg, display);
	return found;
}

bool Search::foundSubject(DataStore &data, std::string &keyword, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, Add &add, Display &display) {
	size_t found = 0;
	data.getTempData().clear();
	assert(!keyword.empty());
	std::ostringstream oss;
	bool isTemp = true;

	for (int index = 0; index < data.getData().size(); index++) {
		found = data.getData()[index].subject.find(keyword);
		if (found != std::string::npos) {
			data.get_tempEntry() = data.getData()[index];
			add.addContent(data, oss, floating, scheduled, deadline, isTemp);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg, display);
	return true;
}

void Search::printSearchedContent(DataStore &data, std::ostringstream &errMsg, Display &display) {
	bool updateFile = false;
	int i = 0;
	int j = 0;

	std::cout << std::endl;
	for (i = 0; data.getTempData().size() != 0; i++) {
		if (data.getData()[i].subject == data.getTempData()[j].subject) {
			std::cout << " " << (i + 1) << ". " << display.getTempDataString(data, j, updateFile) << std::endl;
			data.getTempData().erase(data.getTempData().begin());
			j++;
			i = 0;
		}
	}
	return;
}

int &Search::getCat() {
	return _category;
}