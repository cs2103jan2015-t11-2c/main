//@author A0116237L
#include "Delete.h"

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
	int count = 0;
	Display show;

	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getData().size()) {
			return false;
		}
		data.get_tempEntry().subject = data.getData()[index - 1].subject;
		data.getTempData().push_back(data.getData()[index - 1]);
		data.getData().erase(data.getData().begin() + (index - 1));
		count++;
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
	}

	data.get_tempEntry().subject = "";
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
			std::cout << "list : " << i << std::endl;
		}
	}

	data.get_tempEntry().subject = "";
	data.clearData(floating, scheduled, deadline);
	show.getTempDisplay(data, floating, scheduled, deadline);
	if (data.getTempData().empty()) {
		isDelete = true;
		return false;
	}
	else if (data.getTempData().size() == 1) {
		data.getData().erase(data.getData().begin() + _indexList.front());
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
	std::vector <Entry> list;
	bool isTemp = true;
	data.getTempData().clear();

	while (!info.empty()) {
		if (info == "all") {
			while (!_indexList.empty()) {
				data.getData().erase(data.getData().begin() + _indexList.back());
				_indexList.pop_back();
			}
			errMsg << " all of the above deleted";
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
		if (index > deleteListSize) {
			errMsg << " index entered is invalid (out of range)";
			return false;
		}
		std::cout << "_index: " << _indexList[index - 1] << std::endl;
		data.get_tempEntry() = data.getData()[_indexList[index - 1]];
		data.getData().erase(data.getData().begin() + _indexList[index - 1]);
		add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
	}
	data.clearData(floating, scheduled, deadline);
	data.get_tempEntry().subject = "";
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