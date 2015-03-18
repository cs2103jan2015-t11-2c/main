#include "Search.h"

//Displays all contents that contains the keywords
void Search::searchFile(std::string &fileName, DataStore &data, std::string readInLine) {
	
	if (foundContent(data, readInLine)) {
		printSearchedContent(data);
		return;
	}

}

bool Search::foundContent(DataStore &data, std::string &readInLine) {
	
	size_t found;
	data.clearTempDataBase();

	for (int index = 0; index < data.getDataBaseSize(); index++) {
		std::string content = data.getSubject(index);
		found = content.find(readInLine);
		
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
