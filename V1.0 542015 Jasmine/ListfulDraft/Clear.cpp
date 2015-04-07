#include "Clear.h"

bool Clear::clearFile(DataStore &data) {
	if (data.getData().size() == 0) {
		return false;
	}
	data.getData().clear();
	return true;
}