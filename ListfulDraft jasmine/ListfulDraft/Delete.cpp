#include "Delete.h"

/*
//to get the index of the entry 
int Delete::getContentIndex(DataStore &data, std::string subject) {
	std::size_t found;
	
	for (int index = 0; index != data.getData().size(); index++) {
		found = data.getDataBase()[index].subject.find(subject);
		if (subject == data.getDataBase()[index].subject || found != std::string::npos) {
			return index;
		}
	}
}*/

//to delete the content
void Delete::deleteContent(DataStore &data, std::string info) {
	//std::string emptyStr;
	//emptyStr.clear();
	std::string temp;
	temp = info.substr(0, info.find_first_of(" "));
	// if its by index
	if (temp == "subject" || temp == "SUBJECT" || temp == "sub" || temp == "SUB") {
		std::size_t found = info.find(temp);
		int start = info.find_first_of(" ",found);
		start = info.find_first_not_of(" ",start);
		std::string sub = info.substr(start);
		std::vector<Entry>::size_type sz = data.getData().size();
		for(unsigned index = 0 ; index < sz; index++) {
			if (data.getData()[index].subject == sub) {
				//display function
			}
		}
	} else {
		std::cout << info << std::endl;
		int index = atoi(info.c_str());
		//convert info to int
		data.getData().erase(data.getData().begin()+index-1);
		data.updateFile();
		data.savePrevFile();
		std::cout << "Deleted" << std::endl;
	}

	return;


	/*if (data.getDataBaseSize() == 0) {
		std::cout << "File is currently empty.\n";
		return;
	}

	//To check if the index number the user wants to delete is valid
	if (index != 0 && index > data.getDataBaseSize()) {
		throw "Index of entry to delete is invalid.\n";
		//std::cout << "Index of entry to delete is invalid.\n";
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
	}*/
}