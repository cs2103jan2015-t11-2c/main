#include "Clear.h"

//system restore
bool Clear::clearFile(DataStore &data) {
	if (data.getData().size() == 0) {
		return false;
	}

	data.getData().clear();
	data.updateFile();
	data.savePrevFile();
	return true;
}