#include "Delete.h"

int Delete::getContentIndex(DataStore &data, std::string subject) {
	std::size_t found;
	
	for (int index = 0; index != data.getDataBaseSize(); index++) {
		found = data.getDataBase()[index].subject.find(subject);
		if (subject == data.getDataBase()[index].subject || found != std::string::npos) {
			return index;
		}
	}
}

void Delete::deleteContent(std::string &fileName, DataStore &data, int index) {
	std::string emptyStr;
	emptyStr.clear();

	if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}

	//To check if the index number the user wants to delete is valid
	if (index != 0 && index > data.getDataBaseSize()) {
		std::cout << "Index of entry to delete is invalid.\n";
		return;
	}
	
	std::string text = (data.getDataBase())[index - 1].subject;
	data.deleteDataBase(data.getDataIter() + (index - 1));
	data.updateFile(fileName);
	std::cout << "Entry of index " << index << ": " << text << " successfully deleted.\n";
	//sprintf_s(messageToUser, MESSAGE_DELETE.c_str(), fileName.c_str(), text.c_str());
	//output(messageToUser);

	if (data.getDataBase().empty()) {
		std::cout << "Last entry of is file deleted.\n";
		//sprintf_s(messageToUser, MESSAGE_CLEAR.c_str(), fileName.c_str());
		//output(messageToUser);
	}
}