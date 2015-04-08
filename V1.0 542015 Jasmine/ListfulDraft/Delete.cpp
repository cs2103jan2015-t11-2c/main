#include "Delete.h"

bool Delete::deleteContent(DataStore &data, std::string info, std::ostringstream &errMsg, bool &isDelete) {
	if (info[0] >= '0' && info[0] <= '9') {
		return deleteByIndex(data, info, errMsg);
	}
	
	return  deleteBySubject(data, info, errMsg, isDelete);
}

bool Delete::deleteByIndex(DataStore &data, std::string info, std::ostringstream &errMsg) {
	size_t found = info.find_first_of(" ");
	std::string list = info;
	int index = 0;
	int count = 0;

	while (!info.empty()) {
		if (found == std::string::npos) {
			found = info.size();
		}
		index = atoi(info.substr(0, found).c_str());
		if (index > data.getData().size()) {
			return false;
		}
		data.get_tempEntry().subject = data.getData()[index - 1].subject;
		data.getData().erase(data.getData().begin() + (index - 1));
		count++;
		if (found == info.size()) {
			info.clear();
			break;
		}
		info = info.substr(found + 1);
		found = info.find_first_of(" ");
	}

	if (count > 1) {
		data.get_tempEntry().subject = "";
		errMsg << " multiple entries [ " << list << " ] deleted";
	}

	checkDataBaseEmpty(data, errMsg);
	data.updateFile(data);
	data.savePrevFile();
	return true;
}

bool Delete::deleteBySubject(DataStore &data, std::string info, std::ostringstream &errMsg, bool &isDelete) {
	size_t found = 0;
	Add add;
	std::vector <Entry>::iterator iter;
	std::ostringstream ignore;
	bool isTemp = true;
	_indexList.clear();
	data.getTempData().clear();

	for (iter = data.getData().begin(); iter != data.getData().end(); iter++) {
		found = (*iter).subject.find(info);
		if (found != std::string::npos) {
			data.get_tempEntry() = (*iter);
			add.addContent(data, ignore, isTemp);
			_indexList.push_back(iter);
		}
	}

	if (data.getTempData().empty()) {
		isDelete = true;
		return false;
	}
	else if (data.getTempData().size() == 1) {
		data.getData().erase(*(_indexList.begin()));
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

bool Delete::deleteMore(DataStore &data, std::string info, std::ostringstream &errMsg) {
	size_t found = info.find_first_of(" ");
	int index = 0;
	std::string subject = "";
	std::ostringstream msg;

	if (found == std::string::npos) {
		index = atoi(info.c_str());
		if (index > data.getTempData().size()) {
			errMsg << " index [ " << index << " ] out of range";
			return false;
		}
		subject = (*_indexList[index - 1]).subject;
		data.getData().erase(_indexList[index - 1]);
		errMsg << " deleted from " << data.getFileName() << ": \"" << subject << "\"";
		msg << " deleted from " << data.getFileName() << ": \"" << subject << "\"";

		data.savePrevAction(msg.str());
		checkDataBaseEmpty(data, errMsg);
		data.updateFile(data);
		data.savePrevFile();
		return true;
	}
	else {
		subject = info;
		while (!info.empty()) {
			if (data.getData().empty()) {
				errMsg << " remaining index(es) [ " << info << " ] not found in file";
				return false;
			}

			if (found == std::string::npos) {
				index = atoi(info.c_str());
			}
			else {
				info = info.substr(found + 1);
				index = atoi((info.substr(0, found)).c_str());
			}

			if (index > data.getTempData().size()) {
				errMsg << " index [ " << index << " ] out of range";
				return false;
			}
			data.getData().erase(_indexList[index - 1]);
			_indexList.erase(_indexList.begin() + (index - 1));
			found = info.find_first_of(" ");
		}
		errMsg << " deleted from " << data.getFileName() << ": index(es) [ " << subject << " ]";
		msg << " deleted from " << data.getFileName() << ": index(es) [ " << subject << " ]";
		data.savePrevAction(msg.str());
		checkDataBaseEmpty(data, errMsg);
		data.updateFile(data);
		data.savePrevFile();
		return true;
		
	}
}

void Delete::checkDataBaseEmpty(DataStore &data, std::ostringstream &errMsg) {
	if (data.getData().empty()) {
		errMsg << std::endl << std::endl << " last entry has been cleared";
	}
	return;
}