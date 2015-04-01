#include "Search.h"


//Displays all contents that contains the keywords
bool Search::searchFile(DataStore &data, std::string keyword, int category) {
		
	
	switch (category) {
		case SUBJECT:{
			if (foundSubject(data, keyword)) {
				printSearchedContent(data);
			}
			else
				std::cout << "Not Found!" << std::endl;
			break;
					 }
		case DATE:{
			if (foundDate(data, keyword)){
				printSearchedContent(data);	
			}	
			else
				std::cout << "Not Found!" << std::endl;
			break;
				  }
		case TIME:{
			if (foundTime(data, keyword)){
				printSearchedContent(data);			
			}	
			else
				std::cout << "Not Found!" << std::endl;
			break;
				  }
		case CATEGORY: {
			if (foundCategory(data, keyword)){
				printSearchedContent(data);			
			}	
			else
				std::cout << "Not Found!" << std::endl;
			
			break;
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
			if (foundPriority(data, keyword)){
				printSearchedContent(data);			
			}	
			else
				std::cout << "Not Found!" << std::endl;
			
			break;
					   }
		default:
			std::cout << "Search command is invalid.\n";

	}

	
		return true;
}

bool Search::foundPriority(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.getTempData().clear();

	
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].priority;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.updateTempDataBase(data.getData()[index]); 
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	
	return true;
}

bool Search::foundCategory(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.getTempData().clear();

	
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].category;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.updateTempDataBase(data.getData()[index]); 
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	
	return true;
}



bool Search::foundTime(DataStore &data, std::string &keyword) {
	
	bool found = false;
	data.getTempData().clear();

	for (int index = 0; index < data.getData().size(); index++) {
		std::string time = data.getTime(data.getData()[index]);
	if(time == keyword){
		data.updateTempDataBase(data.getData()[index]); 
		found = true;
	}
		
	if (data.getTempData().empty()) {
		return false;
	}
	}
	return found;
}

bool Search::foundDate(DataStore &data, std::string &keyword) {
	
	bool found = false;
	data.getTempData().clear();

	for (int index = 0; index < data.getData().size(); index++) {
		std::string date = data.getDate(data.getData()[index]);
	if(date == keyword){
		data.updateTempDataBase(data.getData()[index]); 
		found = true;
	}
		
	if (data.getTempData().empty()) {
		return false;
	}
	}
	return found;
}

bool Search::foundSubject(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.getTempData().clear();

	
	for (int index = 0; index < data.getData().size(); index++) {
		std::string content = data.getData()[index].subject;
		found = content.find(keyword);
		
		if (found != std::string::npos) {
			data.updateTempDataBase(data.getData()[index]); 
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}
	
	return true;
}


void Search::printSearchedContent(DataStore &data){

	std::cout << "Results: " << std::endl;
	std::cout << data.printTempDataBase() << std::endl;
	
}

