#include "Search.h"


//Displays all contents that contains the keywords
bool Search::searchFile(DataStore &data, std::string keyword, std::ostringstream &errMsg) {
	switch (_category) {
		case SUBJECT:
			return foundSubject(data, keyword, errMsg);
		case DATE:
			return foundDate(data, keyword, errMsg);
		case TIME:
			return foundTime(data, keyword, errMsg);
		case CATEGORY:{
			if (keyword[0] == 'W' || keyword[0] == 'w'){
				keyword = "WORK"; 
			}
			else if(keyword[0] == 'I' || keyword[0] == 'i'){
				keyword = "INBOX";
			}
			else if(keyword[0] == 'P' || keyword[0] == 'p'){
				keyword = "PERSONAL";
			}
			else if(keyword[0] == 'E' || keyword[0] == 'e'){
				keyword = "ERRAND";
			}
			return foundCategory(data, keyword, errMsg);
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
			return foundPriority(data, keyword, errMsg);
			}
		default:
			return false;
	}
}

bool Search::foundPriority(DataStore &data, std::string &keyword, std::ostringstream &errMsg) {
	size_t found = 0;
	data.getTempData().clear();
	assert(!keyword.empty());
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].priority;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.getTempData().push_back(data.getData()[index]);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg);
	return true;
}

bool Search::foundCategory(DataStore &data, std::string &keyword, std::ostringstream &errMsg) {
	size_t found = 0;
	data.getTempData().clear();

	assert(!keyword.empty());
	
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].category;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.getTempData().push_back(data.getData()[index]);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg);
	return true;
}



bool Search::foundTime(DataStore &data, std::string &keyword, std::ostringstream &errMsg) {
	bool found = false;
	data.getTempData().clear();
	
	assert(!keyword.empty());

	for (int index = 0; index < data.getData().size(); index++) {
		
		std::string time = data.getTime(data.getData()[index]);
		if(time == keyword){
			data.getTempData().push_back(data.getData()[index]);
			found = true;
		}
		
		//if (data.getTempData().empty()) {
			//return false;
		//}
	}
	printSearchedContent(data, errMsg);
	return found;
}

bool Search::foundDate(DataStore &data, std::string &keyword, std::ostringstream &errMsg) {
	bool found = false;
	data.getTempData().clear();
	assert(!keyword.empty());

	for (int index = 0; index < data.getData().size(); index++) {
		std::string date = data.getDate(data.getData()[index]);
		if(date == keyword){
			data.getTempData().push_back(data.getData()[index]);
			found = true;
		}
		
	//	if (data.getTempData().empty()) {
		//	return false;
		//}
	}
	printSearchedContent(data, errMsg);
	return found;
}

bool Search::foundSubject(DataStore &data, std::string &keyword, std::ostringstream &errMsg) {
	size_t found = 0;
	data.getTempData().clear();
	assert(!keyword.empty());

	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].subject;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.getTempData().push_back(data.getData()[index]);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	printSearchedContent(data, errMsg);
	return true;
}

void Search::printSearchedContent(DataStore &data, std::ostringstream &errMsg){
	errMsg << std::endl;
	for (int i = 0; i < data.getTempData().size(); i++) {
		errMsg << (i + 1) << ". " << data.getTempDataString(i) << std::endl;
	}
}

int &Search::getCat() {
	return _category;
}