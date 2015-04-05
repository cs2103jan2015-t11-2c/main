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
bool Delete::deleteContent(DataStore &data, std::string info, std::ostringstream &errMsg) {
	bool status = true;

	size_t found = info.find_first_of(" ");
	if (found == std::string::npos) {
		int index = atoi(info.c_str());
		status = deletebyIndex(data,index, errMsg);
		data.updateFile();
		data.savePrevFile();
		return status;
	}

	std::string temp = info.substr(0, found);

	// if its by subject
	if (temp == "subject" || temp == "SUBJECT" || temp == "sub" || temp == "SUB") {
		status = deletebySubject(data, temp, info, errMsg);
	}
	// if its by index
	else {
		info = info.substr(found + 1);
		int index = atoi(info.c_str());
		status = deletebyIndex(data,index, errMsg);
	}
	data.updateFile();
	data.savePrevFile();
	return status;
}

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

	}
}
/*
bool Delete::deleteContent(DataStore &data, int index) {
	std::string emptyStr;
	emptyStr.clear();

	if (data.getData().size() == 0) {
		std::cout << "File is currently empty.\n";
		return false;
	}

	//To check if the index number the user wants to delete is valid
	if (index != 0 && index > data.getData().size() == 0) {
		std::cout << "Index of entry to delete is invalid.\n";
		return false;
	}
	
	std::string text = (data.getData())[index].subject;
	data.getData().erase(data.getData().begin()+index);
	data.updateFile();
	std::cout << "Entry successfully deleted.\n";


	if (data.getData().empty()) {
		std::cout << "Last entry of is file deleted.\n";
		
	}
	return true;
}
*/

bool Delete::deletebyIndex(DataStore &data, int index, std::ostringstream &errMsg) {
	if (index > data.getData().size()) {
		return false;
	}

	errMsg << data.getData()[index - 1].subject;
	data.getData().erase(data.getData().begin()+index-1);
	return true;
}


bool Delete::deletebySubject(DataStore &data, std::string temp, std::string info, std::ostringstream &errMsg) {
	std::size_t found = info.find(temp);
	if (found == std::string::npos) {
		return false;
	}

	size_t start = info.find_first_of(" ",found);
	start = info.find_first_not_of(" ",start);
	std::string sub = info.substr(start);
	data.getTempData().clear();

	for(int ind = 0 ; ind < data.getData().size(); ind++) {
		start = data.getData()[ind].subject.find(sub);
		if (start != std::string::npos) {
			data.getTempData().push_back(data.getData()[ind]);
		}
	}

	if (data.getTempData().empty()) {
		return false;
	}

	for (int i = 0; i < data.getTempData().size(); i++) {
		std::cout << (i + 1) << ". " << data.getTempDataString(i) << std::endl;
	}
	//"which entry would you like to delete?
	int index;
	std::cin >> index;
	return deletebyIndex(data,index, errMsg);
}