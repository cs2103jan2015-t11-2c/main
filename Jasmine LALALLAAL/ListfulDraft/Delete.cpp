#include "Delete.h"

void Delete::remove(DataStore &data, std::vector <std::string> list) {
	for (int i = 0; list.size() != 0; i++) {
		if (i == data.getData().size()) {
			i = 0;
		}
		if (data.getData()[i].subject == list[list.size() - 1]) {
			data.getData().erase(data.getData().begin() + i);
			list.pop_back();
		}
	}
	data.get_tempEntry().subject = "";
	return;
}

bool Delete::isRepeat(std::vector <int> list, int index, std::ostringstream &errMsg) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == index) {
			errMsg << "repeated index to delete found";
			return true;
		}
	}
	return false;
}

bool Delete::deleteContent(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	data.getTempData().clear();
	data.clearData(floating, scheduled, deadline);

	if (info[0] >= '0' && info[0] <= '9') {
		isDelete = true;
		return deleteByIndex(data, info, errMsg, floating, scheduled, deadline);
	}
	
	return deleteBySubject(data, info, errMsg, floating, scheduled, deadline, isDelete);
}

bool Delete::deleteByIndex(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	std::vector <int> checkList;
	std::vector <std::string> strList;
	int count = 0;
	Display show;

	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getData().size()) {
			errMsg << "index out of range";
			return false;
		}
		else if (!checkList.empty()) {
			if (isRepeat(checkList, index, errMsg)) {
				return false;
			}
		}
		data.get_tempEntry().subject = data.getData()[index - 1].subject;
		data.getTempData().push_back(data.getData()[index - 1]);
		strList.push_back(data.getData()[index - 1].subject);
		count++;
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
		checkList.push_back(index);
	}
	remove(data, strList);
	show.getTempDisplay(data, floating, scheduled, deadline);
	checkDataBaseEmpty(data, errMsg);
	data.updateFile(data);
	data.savePrevFile();
	return true;
}

bool Delete::deleteBySubject(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, bool &isDelete) {
	size_t found = 0;
	Add add;
	Display show;
	bool isTemp = true;
	_indexList.clear();
	data.getTempData().clear();

	for (int i = 0; i < data.getData().size(); i++) {
		found = data.getData()[i].subject.find(info);
		if (found != std::string::npos) {
			data.get_tempEntry() = data.getData()[i];
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			_indexList.push_back(i);
		}
	}

	data.get_tempEntry().subject = "";
	data.clearData(floating, scheduled, deadline);
	show.getTempDisplay(data, floating, scheduled, deadline);
	if (data.getTempData().empty()) {
		isDelete = true;
		errMsg << "no same/similar subject found in file";
		return false;
	}
	else if (data.getTempData().size() == 1) {
		data.getData().erase(data.getData().begin() + (_indexList.front() - 1));
		isDelete = true;
	}
	else {
		return false;
	}
	
	checkDataBaseEmpty(data, errMsg);
	data.updateFile(data);
	data.savePrevFile();
	return true;
}

bool Delete::deleteMore(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	int deleteListSize = data.getTempData().size();
	Add add;
	Display show;
	std::vector <int> checkList;
	std::vector <std::string> strList;
	bool isTemp = true;
	data.getTempData().clear();

	while (!info.empty()) {
		if (info == "all") {
			while (!_indexList.empty()) {
				strList.push_back(data.getData()[_indexList[_indexList.size() - 1]].subject);
				_indexList.pop_back();
			}
			errMsg << " all of the above deleted";
			remove(data, strList);
			checkDataBaseEmpty(data, errMsg);
			data.updateFile(data);
			data.savePrevFile();
			return true;
		}
		if (found == std::string::npos) {
			index = atoi(info.c_str());
			found = info.size();
		}
		else {
			index = atoi(info.substr(0, found).c_str());
		}
		
		if (!checkList.empty()) {
			if (isRepeat(checkList, index, errMsg)) {
				return false;
			}
		}
		if (index > deleteListSize) {
			errMsg << " index entered is invalid (out of range)";
			return false;
		}
		data.get_tempEntry() = data.getData()[_indexList[index - 1]];
		add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
		strList.push_back(data.getData()[_indexList[index - 1]].subject);
		checkList.push_back(_indexList[index - 1]);
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
	}
	remove(data, strList);
	data.clearData(floating, scheduled, deadline);
	show.getTempDisplay(data, floating, scheduled, deadline);
	checkDataBaseEmpty(data, errMsg);
	data.updateFile(data);
	data.savePrevFile();
	return true;
}

void Delete::checkDataBaseEmpty(DataStore &data, std::ostringstream &errMsg) {
	if (data.getData().empty()) {
		errMsg << std::endl << std::endl << " last entry has been cleared";
	}
	return;
}