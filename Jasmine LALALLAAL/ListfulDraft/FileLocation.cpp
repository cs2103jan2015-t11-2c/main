//@author A0110670W
#include "FileLocation.h"

const std::string FileLocation::FILE_LOCATION_LIST = "Listful_FileLocationList.txt";

//To retrieve previously saved file names and location
void FileLocation::saveFileLocation() {
	std::string name = "";
	std::vector <std::string> fileList;

	//To copy the already saved file names so that it will not be overwritten
	std::ifstream readFile(FILE_LOCATION_LIST);
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, name);
			if (name != "") {
				fileList.push_back(name);
			}
		}
		readFile.close();
	}

	//Add in the new fileName (location)
	fileList.push_back(_fileName);

	//Update file location list
	std::ofstream writeFile(FILE_LOCATION_LIST);
	while (!fileList.empty()) {
		writeFile << fileList.back() << "\n";
		fileList.pop_back();
	}
	writeFile.close();
}

bool FileLocation::findFile(DataStore &data) {
	std::string x = "";
	size_t found = 0;

	std::ifstream readFile(FILE_LOCATION_LIST.c_str());
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, x);
			//If file has no location specified and a file with the same name is found in this list, assume user is referring to the same file
			found = x.find(_fileName);
			if (x == _fileName || found != std::string::npos) {
				_fileName = x;
				return true;
			}
		}
		readFile.close();
	}
	saveFileLocation();
	return false;
}

int FileLocation::openFile(DataStore &data, ParserFacade parse, Classes &listClass) {
	std::string x = "";
	std::string subject = "";
	size_t start = 0;
	size_t end = 0;
	int i = 0;
	bool ignore = false;
	
	if (findFile(data)) {
		std::ifstream readFile(_fileName.c_str());
		if (readFile.is_open()) {
			while (!readFile.eof()) {
				getline(readFile, x);

				while (x == "") {
					getline(readFile, x);
					i++;
					if (i > 10) {
						data.updateFile(data);
						data.savePrevFile();
						readFile.close();
						return fileMsg::OPEN;
					}
				}
				
				start = x.find_first_of(".");
				end = x.find(" | ");
				subject = x.substr(start + 1, end - (start + 1));
				parse.removeFrontChar(subject);
				parse.removeBackChar(subject);
				
				x = x.substr(start + 2);
				parse.readFile(x);
				parse.separateWord(listClass, data, ignore, ignore);
				data.get_tempEntry().subject = subject;
				data.getData().push_back(data.get_tempEntry());

				//Removes extra line in between entries
				getline(readFile, x);
			}
			data.updateFile(data);
			data.savePrevFile();
			readFile.close();
			return fileMsg::OPEN;
		}
	}
	data.updateFile(data);
	return fileMsg::CREATE;
}

std::string &FileLocation::getName() {
	return _fileName;
}
