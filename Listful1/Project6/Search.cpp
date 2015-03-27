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
		case IMPT: {
			if (keyword[0] == 'l' || keyword[0] == 'L'){
				keyword = "Low"; 
			}
			else if(keyword[0] == 'h' || keyword[0] == 'H'){
				keyword = "High";
			}
			else if(keyword[0] == 'm' || keyword[0] == 'M'){
				keyword = "Medium";
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

			return;
	}

	
		return;
}

bool Search::foundPriority(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.clearTempDataBase();
	
	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string content = data.getPriority(index);
		std::cout<<content<<std::endl;
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

bool Search::foundCategory(DataStore &data, std::string &keyword) {
	
	size_t found;
	data.clearTempDataBase();

	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string content = data.getCategory(index);
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



bool Search::foundTime(DataStore &data, std::string &keyword) {
	
	bool found = false;
	data.clearTempDataBase();

	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string time = data.getTime(index);
	if(time == keyword){
		data.updateTempDataBase(data.getDataBase()[index]); 
		found = true;
	}
		
	if (data.getTempDataBase().empty()) {
		return false;
	}
	}
	return found;
}

bool Search::foundDate(DataStore &data, std::string &keyword) {
	
	bool found = false;
	data.clearTempDataBase();

	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string date = data.getDate(index);
	if(date == keyword){
		data.updateTempDataBase(data.getDataBase()[index]); 
		found = true;
	}
		
	if (data.getTempDataBase().empty()) {
		return false;
	}
	}
	return found;
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

	/*for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string word = data.getSubject(index);
		word = word.substr(1);
		//std::string acronym = data.findAcronym(word);
		std::string content = data.getSubject(index);
		found = content.find(keyword);
		if (found != std::string::npos/*content == keyword || acronym == keyword) {
			data.updateTempDataBase(data.getDataBase()[index]); 
			found = true;
		}
	}*/

	if (data.getTempDataBase().empty()) {
		return false;
	}
	
	return true;
}


void Search::printSearchedContent(DataStore &data){

	std::cout << "Results: " << std::endl;
	std::cout << data.printTempDataBase() << std::endl;
	
}
