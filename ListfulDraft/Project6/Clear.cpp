#include "Clear.h"

//system restore
void Clear::clearFile(std::string &fileName, DataStore &data) {
	if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}

	data.clearDataBase();
	data.updateFile(fileName);

	std::cout << "File has been cleared successfully.\n";
	//sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
	//output(messageToUser);
}
