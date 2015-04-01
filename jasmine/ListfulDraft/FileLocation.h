#ifndef FILELOCATION_H
#define FILELOCATION_H

#include "Parser.h"

class FileLocation {
private:
	enum fileMsg {
		OPEN, CREATE
	};

	std::string _fileName;

public:
	FileLocation() {};

	int openFile(DataStore &, Parser, Classes &);

	std::string &getName();
};

#endif