#include "Parser.h"

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
	int openFile(DataStore &, Parser, Classes &);

	std::string &getName();
};

