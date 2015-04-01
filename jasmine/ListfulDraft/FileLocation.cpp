#include "FileLocation.h"

int FileLocation::openFile(DataStore &data, Parser parse, Classes &listClass) {
	std::string x = "";
	std::string subject = "";
	size_t start = 0;
	
	std::ifstream readFile (_fileName.c_str());
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            //Reads in first line which contains subject 
			getline (readFile, x);
			start = x.find_first_of(" ");
			subject = x.substr(start + 1);

			//Reads in second line which contains the subCategories (date, time, priority, category)
			getline(readFile, x);
			parse.separateWord(listClass, data);
			data.get_tempEntry().subject = subject;
			data.getData().push_back(data.get_tempEntry());
        }	
		readFile.close();
		return fileMsg::OPEN;
    }
    else {
        return fileMsg::CREATE;
    }
}

std::string &FileLocation::getName() {
	return _fileName;
}
