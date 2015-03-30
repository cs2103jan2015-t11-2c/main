#include "Clear.h"

//system restore
bool Clear::clearFile(DataStore &data) {
	if (data.getData().size() == 0) {
		std::cout << "file is currently empty.\n"; //put message in message part
		return false;
	}

	data.getData().clear();
	data.updateFile();
	data.savePrevFile();
	return true;
}