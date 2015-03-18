#include "DataStore.h"

int DataStore::countDigit(int &num) {
	int count = 0;
	int tNum = num;

	while (tNum > 0) {
		count++;
		tNum = tNum/10;
	}
	return count;
}

void DataStore::updateDataBase() {
	dataBase.push_back(tempEntry);
}

void DataStore::deleteDataBase(std::vector <Entries>::iterator iter) {
	dataBase.erase(iter);
}

std::string DataStore::getDataString(int index) {
	std::ostringstream dataString;

	int sTime = countDigit(dataBase[index].startTime);
	int eTime = countDigit(dataBase[index].endTime);
	int nDay = countDigit(dataBase[index].day);
	int nMonth = countDigit(dataBase[index].month);
	int nYear = countDigit(dataBase[index].year);

	dataString << dataBase[index].index << ". " << dataBase[index].subject << "\nTime: ";
	
	while (sTime < 4) {
		dataString << '0';
		sTime++;
	}
	dataString << dataBase[index].startTime << '-';

	while (eTime < 4) {
		dataString << '0';
		eTime++;
	}
	dataString << dataBase[index].endTime << "\t\tDate: ";
	
	if (nDay < 2) {
		dataString << '0';
	}
	dataString << dataBase[index].day << '/';
	
	if (nMonth < 2) {
		dataString << '0';
	}
	dataString << dataBase[index].month << '/' << dataBase[index].year << "\tPriority: " << dataBase[index].impt << "\tCategory: " << dataBase[index].category << '\n';

	return dataString.str();

}



void DataStore::updateFile(std::string &fileName) {
	std::ofstream writeFile;

	writeFile.open(fileName);
	for (int index = 0; index != dataBase.size(); index++) {
		writeFile << getDataString(index) << "\n";
	}
	writeFile.close();
}

void DataStore::entryType(int &index, std::string &subject, int &startTime, int &endTime, int &day, int &month, int &year, std::string &impt, std::string &category) {
	tempEntry.index = index;
	tempEntry.subject = subject;
	tempEntry.startTime = startTime;
	tempEntry.endTime = endTime;
	tempEntry.day = day;
	tempEntry.month = month;
	tempEntry.year = year;
	tempEntry.impt = impt;
	tempEntry.category = category;
}
