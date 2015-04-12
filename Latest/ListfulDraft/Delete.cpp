#include "Delete.h"

void Delete::remove(DataStore &data, std::vector <int> list) {
	data.getTempIndexList().clear();
	std::ostringstream ignore;
	bool isTemp = true;
	
	for (int i = 0; !list.empty(); i++) {
		if (data.getData()[i].referenceNo == list.back()) {
			data.getTempIndexList().push_back(i);
			data.getData().erase(data.getData().begin() + i);
			list.pop_back();
		}
		if ((i + 1) == data.getData().size()) {
			i = -1;
		}
	}
	return;
}

bool Delete::isRepeat(DataStore &data, std::vector <int> list, int index) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == data.getData()[index].referenceNo) {
			data.get_tempEntry().subject = " repeated index to check complete found\n";
			return true;
		}
	}
	return false;
}

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
				data.get_tempEntry().subject = "";
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
	std::cout << "wgf" << std::endl;
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	std::cout << "th" << std::endl;
	checkDataBaseEmpty(data, errMsg);
	std::cout << "erdh" << std::endl;
	return true;
}

bool Delete::deleteBySubject(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	size_t found = 0;
	bool isTemp = true;
	std::vector <int> checkList;
	data.getTempData().clear();
	data.getTempIndexList().clear();

	if (info == "all") {
		for (int i = 0; i < data.getTempData().size(); i++) {
			checkList.push_back(data.getTempData()[i].referenceNo);
		}
		remove(data, checkList);
		data.clearData(floating, scheduled, deadline);
		search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
		checkDataBaseEmpty(data, errMsg);
		isDelete = true;
		return true;
	}
	
	for (int i = 0; i < data.getData().size(); i++) {
		found = data.getData()[i].subject.find(info);
		if (found != std::string::npos) {
			data.get_tempEntry() = data.getData()[i];
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			data.getTempIndexList().push_back(i);
			checkList.push_back(data.getData()[i].referenceNo);
		}
	}
	data.get_tempEntry().subject = "";

	if (data.getTempData().empty()) {
		isDelete = true;
		errMsg << "no same/similar subject found in file";
		return false;
	}
	else if (data.getTempData().size() == 1) {
		remove(data, checkList);
		isDelete = true;
		data.clearData(floating, scheduled, deadline);
		search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
		checkDataBaseEmpty(data, errMsg);
		return true;
	}
	data.get_tempEntry() = data.get_emptyEntry();
	data.clearData(floating, scheduled, deadline);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	checkDataBaseEmpty(data, errMsg);
	return false;
}

void Delete::checkDataBaseEmpty(DataStore &data, std::ostringstream &errMsg) {
	if (data.getData().empty()) {
		errMsg << std::endl << " last entry has been cleared";
	}
	return;
}