#include "Edit.h"

void Edit::updateTemp(DataStore &data, std::vector <int> list) {
	data.getTempData().clear();
	data.getTempIndexList().clear();
	std::ostringstream ignore;
	bool isTemp = true;

	while (!list.empty()) {
		data.get_tempEntry() = data.getData()[list.back()];
		add.addContent(data, ignore, ignore, ignore, ignore, isTemp);
		list.pop_back();
	}
	data.get_tempEntry() = data.get_emptyEntry();
	return;
}

bool Edit::isRepeat(DataStore &data, std::vector <int> list, int index) {
	for (int j = 0; j < list.size(); j++) {
		if (list[j] == index) {
			data.get_tempEntry().subject = " repeated index to check complete found\n";
			return true;
		}
	}
	return false;
}

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
	show.getTempDisplay(data, floating, scheduled, deadline);
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

	//To remove redundant char in front
	while (info[0] <= '0' || info[0] >= '9') {
		info = info.substr(1);
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
			if (isRepeat(data, checkList, index)) {
				return false;
			}
		}
		if (input == "uncheck" || input == "uncomplete") {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = false;
		}
		else {
			data.getData()[data.getTempIndexList()[index - 1]].isComplete = true;
		}
		checkList.push_back(data.getTempIndexList()[index - 1]);
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
	}
	updateTemp(data, checkList);
	sort.sortComplete(data);
	data.clearData(floating, scheduled, deadline);
	show.getTempDisplay(data, floating, scheduled, deadline);
	data.get_tempEntry().subject = "completed";
	return true;
}

bool Edit::editContent(DataStore &data, int index, std::ostringstream &errMsg, std::ostringstream &floating, std::ostringstream &scheduled, std::ostringstream &deadline) {
	if (index == -1) {
		index = 0;
	}

	if (data.getData().size() == 0 && data.getTempData().size() == 0) {
		errMsg << "file is empty";
		return false;
	}
	else if (index > data.getData().size() || index > data.getTempData().size()) {
		errMsg << "index entered is out of range";
		return false;
	}

	bool real = true;
	bool isTemp = false;
	data.getTempData().clear();

	switch (_category) {
		case 0:
			errMsg << " \"" << data.getData()[data.getTempIndexList()[index]].subject << "\" to \"" << data.get_tempEntry().subject << "\"";
			data.getData()[data.getTempIndexList()[index]].subject = data.get_tempEntry().subject;
			break;

		case 1:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << show.getDate(data, data.getTempIndexList()[index], isTemp) << "\" to \"" << show.getDate(data, 0, real) << "\"";
			editDate(data, data.getTempIndexList()[index]);
			add.addContent(data, errMsg, floating, scheduled, deadline, isTemp);
			return true;
		
		case 2:
			data.getTempData().push_back(data.get_tempEntry());
			errMsg << " \"" << show.getTime(data, data.getTempIndexList()[index], isTemp) << "\" to \"" << show.getTime(data, 0, real) << "\"";
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
	show.getEntry(data, floating, scheduled, deadline);
	return true;
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

int &Edit::getCat() {
	return _category;
}