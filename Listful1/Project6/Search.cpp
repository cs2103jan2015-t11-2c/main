#include "Search.h"

int Search::determineCategory(std::string category) {
	if (category == "date") {
		return subCategory::DATE;
	}
	else if (category == "subject") {
		return subCategory::SUBJECT;
	}
	else if (category == "time") {
		return subCategory::TIME;
	}
	else if (category == "priority") {
		return subCategory::IMPT;
	}
	else if (category == "category") {
		return subCategory::CATEGORY;
	}
	else {
		return subCategory::INVALID;
	}
}

//Displays all contents that contains the keywords
void Search::searchFile(std::string &fileName, DataStore &data, std::string keyword, std::string type) {
	
	category = determineCategory(type);
	
	switch (category) {
		case SUBJECT:{
			if (foundSubject(data, keyword)) {
				printSearchedContent(data);
			}
			break;
					 }
		case DATE:{
			//if (foundDate(data, keyword)){
						
			//}	
			break;
				  }
		case CATEGORY: {
			
			break;
					   }
		default:
			std::cout << "Search command is invalid.\n";
			return;
	}

	
		return;
}

bool Search::foundSubject(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.clearTempDataBase();

	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string content = data.getSubject(index);
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.updateTempDataBase(data.getDataBase()[index]); 
		}
	}

	if (data.getTempDataBase().empty()) {
		return false;
	}
	
	return true;
}

void Search::printSearchedContent(DataStore &data){

	std::cout << "Results: " << std::endl;
	std::cout << data.printTempDataBase() << std::endl;
	
}
