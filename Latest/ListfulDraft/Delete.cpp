#include "Delete.h"

bool Delete::deleteContent(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	if (info[0] >= '0' && info[0] <= '9') {
		isDelete = true;
		return deleteByIndex(data, info, errMsg, floating, scheduled, deadline);
	}
	
	return deleteBySubject(data, info, errMsg, floating, scheduled, deadline, isDelete);
}

bool Delete::deleteByIndex(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	bool isTemp = true;
	std::vector <int> checkList;
	data.getTempData().clear();

	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getTempIndexList().size()) {
			errMsg << "index out of range";
			return false;
		}
		else if (!checkList.empty()) {
			if (isRepeat(data, checkList, index)) {
				errMsg << data.get_tempEntry().subject;
				return false;
			}
		}
		data.get_tempEntry() = data.getData()[data.getTempIndexList()[index - 1]];
		add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
		checkList.push_back(data.getData()[data.getTempIndexList()[index - 1]].referenceNo);
		if (found == info.size()) {
			info = "";
		}
		else {
			info = info.substr(found + 1);
			found = info.find_first_of(" ");
		}
	}
	remove(data, checkList);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	checkDataBaseEmpty(data, errMsg);
	return true;
}

bool Delete::deleteBySubject(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	size_t found = 0;
	bool isTemp = true;
	std::vector <int> checkList;
	data.getTempData().clear();

	if (info == "all") {
		deleteAll(data, errMsg, floating, scheduled, deadline, isDelete);
		return true;
	}
	
	data.get_tempEntry().subject = info;
	search.getSubjectSearch(data, floating, scheduled, deadline, errMsg);
	data.get_tempEntry() = data.get_emptyEntry();


	if (data.getTempData().empty()) {
		isDelete = true;
		errMsg << "no same/similar subject found in file";
		return false;
	}
	else if (data.getTempData().size() == 1) {
		checkList.push_back(data.getData()[data.getTempIndexList()[0]].referenceNo);
		remove(data, checkList);
		isDelete = true;
		checkDataBaseEmpty(data, errMsg);
		return true;
	}
	checkDataBaseEmpty(data, errMsg);
	return false;
}



void Delete::deleteAll(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	bool isTemp = true;
	std::vector <int> checkList;

	for (int i = 0; i < data.getTempIndexList().size(); i++) {
		checkList.push_back(data.getData()[data.getTempIndexList()[i]].referenceNo);
		data.get_tempEntry() = data.getData()[data.getTempIndexList()[i]];
		add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
	}
	remove(data, checkList);
	data.clearData(floating, scheduled, deadline);
	data.get_tempEntry() = data.get_emptyEntry();
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	checkDataBaseEmpty(data, errMsg);
	isDelete = true;
	return;
}

void Delete::remove(DataStore &data, std::vector <int> list) {
	data.getTempIndexList().clear();
	bool isTemp = true;
	
	for (int i = 0; !list.empty(); i++) {
		if (i < data.getData().size() && data.getData()[i].referenceNo == list.back()) {
			data.getTempIndexList().push_back(i);
			data.getData().erase(data.getData().begin() + i);
			list.pop_back();
		}
		
		if (i == data.getData().size()) {
			i = -1;
		}
	}
	return;
}

bool Delete::isRepeat(DataStore &data, std::vector <int> list, int index) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == data.getData()[index - 1].referenceNo) {
			data.get_tempEntry().subject = "repeated index to delete found";
			return true;
		}
	}
	return false;
}

void Delete::checkDataBaseEmpty(DataStore &data, std::ostringstream &errMsg) {
	if (data.getData().empty()) {
		errMsg << std::endl << std::endl << " last entry has been cleared";
	}
	return;
}