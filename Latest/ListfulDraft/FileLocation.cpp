#include "FileLocation.h"

const std::string FileLocation::FILE_LOCATION_LIST = "Listful_FileLocationList.txt";

//Shifts accessed file to the top
void FileLocation::updateFileLocation(std::string x) {
	std::string name = "";
	std::vector <std::string> fileList;
	
	//Move the open file up (location)
	fileList.push_back(x);

	//Retrieve the rest of the locations
	std::ifstream readFile(FILE_LOCATION_LIST.c_str());
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, name);
			if (name != x && name != "") {
				fileList.push_back(name);
			}
		}
		readFile.close();
	}

	//To write the locations back in the new order
	std::ofstream writeFile(FILE_LOCATION_LIST.c_str());
	if (writeFile.is_open()) {
		while (!fileList.empty()) {
			writeFile << *(fileList.begin()) << "\n";
			fileList.erase(fileList.begin());
		}
		writeFile.close();
	}
	return;
}

//To retrieve previously saved file names and location
void FileLocation::saveFileLocation() {
	std::string name = "";
	std::vector <std::string> fileList;
	std::string find = _fileName.substr(_fileName.find_last_of("\\") + 1);
					
	//Add in the new fileName (location) at the top
	fileList.push_back(_fileName);

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

	//Update file location list
	std::ofstream writeFile(FILE_LOCATION_LIST);
	while (!fileList.empty()) {
		writeFile << *(fileList.begin()) << "\n";
		fileList.erase(fileList.begin());
	}
	writeFile.close();
	return;
}

bool FileLocation::findFile(DataStore &data, bool isOpen) {
	std::string x = "";
	std::string find = "";
	size_t found = 0;

	std::ifstream readFile(FILE_LOCATION_LIST.c_str());
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, x);

			//If file has no name entered, open last accessed file
			if (!isOpen) {
				isOpen = true;
				find = _fileName.substr(_fileName.find_last_of("\\") + 1);
				if (find == ".txt") {
					_fileName = x;
					return true;
				}
			}

			//If file has no location specified and a file with the same name is found in this list, assume user is referring to the same file
			found = x.find(_fileName);
			if (x == _fileName || found != std::string::npos) {
				_fileName = x;
				updateFileLocation(x);
				return true;
			}
		}
		readFile.close();
	}
	saveFileLocation();
	if (findFile(data, isOpen)) {
		return true;
	}
	return false;
}

int FileLocation::openFile(DataStore &data, ParserFacade parse, Classes &listClass) {
	std::string x = "";
	std::string subject = "";
	size_t start = 0;
	size_t end = 0;
	int i = 0;
	bool ignore = false;
	
	if (findFile(data, ignore)) {
		std::ifstream readFile(_fileName.c_str());
		if (readFile.is_open()) {
			while (!readFile.eof()) {
				getline(readFile, x);

				//If there are extra lines inbetween the files
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
				subject = x.substr(x.find_first_of(".") + 1, (x.find(" | ") - (x.find_first_of(".") + 1)));
				parse.removeFrontChar(subject);
				parse.removeBackChar(subject);
				
				x = x.substr(x.find_first_of(".") + 2);
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