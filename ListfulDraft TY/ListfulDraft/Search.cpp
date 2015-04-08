#include "Search.h"

//Displays all contents that contains the keywords
bool Search::searchFile(DataStore &data, std::string keyword, std::ostringstream &errMsg) {
	Add add;
	Display display;

	switch (_category) {
		case SUBJECT:
			return foundSubject(data, keyword, errMsg, add, display);
		case DATE:
			return foundDate(data, keyword, errMsg, add, display);
		case TIME:
			return foundTime(data, keyword, errMsg, add, display);
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
			return foundCategory(data, keyword, errMsg, add, display);
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
			return foundPriority(data, keyword, errMsg, add, display);
			}
		default:
			return false;
	}
}

bool Search::foundPriority(DataStore &data, std::string &keyword, std::ostringstream &errMsg, Add &add, Display &display) {
	size_t found = 0;
	data.getTempData().clear();
	std::ostringstream oss;
	bool isTemp = true;

	assert(!keyword.empty());
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].priority;
		found = content.find(keyword);
		if (found != std::string::npos) {
			data.get_tempEntry().subject = data.getData()[index].subject;
			add.addContent(data, oss, isTemp);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg, display);
	return true;
}

bool Search::foundCategory(DataStore &data, std::string &keyword, std::ostringstream &errMsg, Add &add, Display &display) {
	size_t found = 0;
	data.getTempData().clear();
	std::ostringstream oss;
	bool isTemp = true;

	assert(!keyword.empty());
	
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].category;
		found = content.find(keyword);
		if (found != std::string::npos) {
			data.get_tempEntry().subject = data.getData()[index].subject;
			add.addContent(data, oss, isTemp);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg, display);
	return true;
}



bool Search::foundTime(DataStore &data, std::string &keyword, std::ostringstream &errMsg, Add &add, Display &display) {
	bool found = false;
	data.getTempData().clear();
	std::ostringstream oss;
	bool isTemp = true;
	
	assert(!keyword.empty());

	for (int index = 0; index < data.getData().size(); index++) {
		std::string time = display.getTime(data, index);
		if(time == keyword){
			data.get_tempEntry().subject = data.getData()[index].subject;
			add.addContent(data, oss, isTemp);
			found = true;
		}
	}
	printSearchedContent(data, errMsg, display);
	return found;
}

bool Search::foundDate(DataStore &data, std::string &keyword, std::ostringstream &errMsg, Add &add, Display &display) {
	bool found = false;
	data.getTempData().clear();
	assert(!keyword.empty());
	std::ostringstream oss;
	bool isTemp = true;

	for (int index = 0; index < data.getData().size(); index++) {
		std::string date = display.getDate(data, index);
		if(date == keyword){
			data.get_tempEntry().subject = data.getData()[index].subject;
			add.addContent(data, oss, isTemp);
			found = true;
		}
	}
	printSearchedContent(data, errMsg, display);
	return found;
}

bool Search::foundSubject(DataStore &data, std::string &keyword, std::ostringstream &errMsg, Add &add, Display &display) {
	size_t found = 0;
	data.getTempData().clear();
	assert(!keyword.empty());
	std::ostringstream oss;
	bool isTemp = true;

	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].subject;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.get_tempEntry().subject = data.getData()[index].subject;
			add.addContent(data, oss, isTemp);
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

	errMsg << std::endl;
	for (i = 0; i < data.getTempData().size(); i++) {
		errMsg << " " << (i + 1) << ". " << display.getTempDataString(data, i, updateFile) << std::endl;
	}
}

int &Search::getCat() {
	return _category;
}