//@author A0115871E
#include "Clear.h"
//to clear the file
bool Clear::clearFile(DataStore &data) {
	if (data.getData().size() == 0) {
		return false;
	}
	data.getData().clear();
	return true;
}