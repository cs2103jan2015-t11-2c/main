#ifndef CHECKFILECREATED_H
#define CHECKFILECREATED_H

#include "Parser.h"

class CheckFileCreated {
public:
	CheckFileCreated() {};

	bool checkFileCreated(std::string &fileName);
	void openFile();
};

#endif