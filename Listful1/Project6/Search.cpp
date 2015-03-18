#include "Search.h"

//Displays all contents that contains the keywords
void Search::searchFile(std::string &fileName, std::string readInLine) {
	
	if (foundContent(readInLine)) {
		printContent(fileName);
		return;
	}

}

bool Search::foundContent(std::string &readInLine) {
	std::vector <std::string>::iterator iter;
	size_t found;
	tempItems.clear();

	for (iter = file.begin(); iter != file.end(); iter++) {
		std::string content = *iter;
		found = content.find(readInLine);
		
		if (found != std::string::npos) {
			tempItems.push_back(content);
		}
	}

	if (tempItems.empty()) {
		return false;
	}
	
	return true;
}
