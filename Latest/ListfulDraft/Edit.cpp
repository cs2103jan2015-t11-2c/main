#include "Edit.h"

bool Edit::checkAll(DataStore &data, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input) {
	int size = 0;
	while (size < data.getTempData().size()) {
		if (input == "uncheck" || input == "uncomplete") {
			data.getData()[data.getTempIndexList()[size]].isComplete = false;
			data.get_tempEntry().subject = "uncompleted all of the below";
		}
		else {
			data.getData()[data.getTempIndexList()[size]].isComplete = true;
			data.get_tempEntry().subject = "completed all of the below";
		}
		size++;
	}
	sort.sortComplete(data);
	data.clearData(errMsg, floating, scheduled);
	data.clearData(floating, scheduled, deadline);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	return true;
}

bool Edit::checkComplete(DataStore &data, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	std::vector <int> checkList;

	//To complete all tasks shown
	if (info == "all") {
		return checkAll(data, errMsg, floating, scheduled, deadline, input);
	}

	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getTempData().size()) {
			errMsg << "index out of range";
			return false;
		}
		else if (!checkList.empty()) {
			if (isRepeat(data, checkList, index - 1)) {
				errMsg << data.get_tempEntry().subject;
				return false;
			}
		}
		if (input == "uncheck" || input == "uncomplete") {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = false;
		}
		else {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = true;
		}
		checkList.push_back(data.getData()[data.getTempIndexList()[index - 1]].referenceNo);
		if (found == info.size()) {
			info = "";
		}
		else {
			info = info.substr(found + 1);
			found = info.find_first_of(" ");
		}
	}
	updateTemp(data, checkList);
	sort.sortComplete(data);
	data.clearData(floating, scheduled, deadline);
	search.getTempDisplay(data, floating, scheduled, deadline, errMsg);
	data.get_tempEntry().subject = "completed";
	return true;
}



bool Edit::editContent(DataStore &data, std::vector <int> editCat, std::string info, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline, std::string input) {
	if (data.getData().size() == 0) {
		errMsg << "file is empty";
		return false;
	}
	
	bool real = true;
	bool isTemp = false;
	int index = 0;

	if (!getEditIndex(info, index)) {
		if (data.getTempData().size() != 1) {
			errMsg << "no index entered";
			return false;
		}
		else if (info.size() != 0 && info[0] >= '0' && info[0] <= '0') {
			checkComplete(data, info, errMsg, floating, scheduled, deadline, input);
		}
	}
	else if (data.get_tempEntry().subject == info && editCat.size() == 1 && editCat[0] == 0) {
		checkComplete(data, info, errMsg, floating, scheduled, deadline, input);
	}

	if (index == 0) {
		index = 1;
	}
	
	data.getTempData().clear();
	index--;
	
	std::cout << index << std::endl;
	std::cout << editCat[0] << std::endl;
	switch (editCat[0]) {
		case 0:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].subject << "\" to \"" << data.get_tempEntry().subject << "\"";
			data.getData()[data.getTempIndexList()[index]].subject = data.get_tempEntry().subject;
			break;

		case 1:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << search.getDate(data, data.getTempIndexList()[index], isTemp) << "\" to \"" << search.getDate(data, 0, real) << "\"";
			editDate(data, data.getTempIndexList()[index]);
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			return true;

		case 2:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << search.getTime(data, data.getTempIndexList()[index], isTemp) << "\" to \"" << search.getTime(data, 0, real) << "\"";
			editTime(data, data.getTempIndexList()[index]);
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			return true;
		    
		case 3:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].priority << "\" to \"" << data.get_tempEntry().priority << "\"";
			data.getData()[data.getTempIndexList()[index]].priority = data.get_tempEntry().priority;
			break;
			
		case 4:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].category << "\" to \"" << data.get_tempEntry().category << "\"";
			data.getData()[data.getTempIndexList()[index]].category = data.get_tempEntry().category;
			break;

		default:
			return false;
	}
	data.get_tempEntry() = data.getData()[data.getTempIndexList()[index]];
	data.clearData(floating, scheduled, deadline);
	search.getEntry(data, floating, scheduled, deadline, errMsg);
	data.get_tempEntry().subject = "";

	if (editCat.size() > 1) {
		editCat.erase(editCat.begin());
		editContent(data, editCat, info, errMsg, floating, scheduled, deadline, input);
	}
	return true;
}

bool Edit::getEditIndex(std::string info, int &index) {
	while (info.size() != 0 && info[0] >= '9' && info[0] <= '0') {
		index = (index * 10) + (info[0] - '0');
		info = info.substr(1);
	}
	
	if (info.size() == 0) {
			return true;
	}
	else {
		return false;
	}
}

void Edit::editTime(DataStore &data, int index) {
	_editEntry = data.getData()[index];

	if (data.get_tempEntry().startTime != data.get_tempEntry().endTime && !_editEntry.isFloat) {
		_editEntry.isTimedTask = true;
	}
	else {
		_editEntry.isTimedTask = false;
	}

	_editEntry.startTime = data.get_tempEntry().startTime;
	_editEntry.endTime = data.get_tempEntry().endTime;
	data.getData().erase(data.getData().begin() + index);
	data.get_tempEntry() = _editEntry;
	return;
}

void Edit::editDate(DataStore &data, int index) {
	_editEntry = data.getData()[index];
	if (data.get_tempEntry().day == 0) {
		_editEntry.isFloat = true;
	}
	else {
		_editEntry.isFloat = false;
	}
	_editEntry.day = data.get_tempEntry().day;
	_editEntry.month = data.get_tempEntry().month;
	_editEntry.year = data.get_tempEntry().year;
	data.getData().erase(data.getData().begin() + index);
	data.get_tempEntry() = _editEntry;
	return;
}



void Edit::updateTemp(DataStore &data, std::vector <int> list) {
	data.getTempData().clear();
	data.getTempIndexList().clear();
	std::ostringstream ignore;
	bool isTemp = true;
		
	for (int i = 0; !list.empty(); i++) {
		if (i < data.getData().size() && data.getData()[i].referenceNo == list.back()) {
			data.getTempIndexList().push_back(i);
			data.get_tempEntry() = data.getData()[list.back()];
			add.addContent(data, ignore, ignore, ignore, ignore, isTemp);
			list.pop_back();
		}
		
		if (i == data.getData().size()) {
			i = -1;
		}
	}
	data.get_tempEntry() = data.get_emptyEntry();
	return;
}

bool Edit::isRepeat(DataStore &data, std::vector <int> list, int index) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == data.getData()[index].referenceNo) {
			data.get_tempEntry().subject = "repeated index to check complete found";
			return true;
		}
	}
	return false;
}