//@author A0110670W
#ifndef FILELOCATION_H
#define FILELOCATION_H

#include "ParserFacade.h"

class FileLocation {
private:
	static const std::string FILE_LOCATION_LIST;

	enum fileMsg {
		OPEN, CREATE
	};

	std::string _fileName;

public:
	FileLocation() {};
	
	void saveFileLocation();
	bool findFile(DataStore &);
	int openFile(DataStore &, ParserFacade, Classes &);

	std::string &getName();
};

#endif