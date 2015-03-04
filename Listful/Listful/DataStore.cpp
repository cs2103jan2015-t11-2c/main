#include "DataStore.h"



DataStore::DataStore(void) {
}


DataStore::~DataStore(void) {
}

/*
//Updates text file after every command so that if user does not close the program 
//properly, the information is not lost
void TextBuddy::updateText(std::string &fileName) {
	std::vector <std::string>::iterator iter = file.begin();

	writeFile.open(fileName);
	for (int count = 1; iter != file.end(); count++) {
		writeFile << count << ". " << *iter << "\n";
		iter++;
	}
	writeFile.close();
}
*/