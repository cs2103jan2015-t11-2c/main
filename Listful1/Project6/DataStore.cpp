#include "DataStore.h"

//to count the number of digits in the datastore
int DataStore::countDigit(int &num) {
	int count = 0;
	int tNum = num;

	while (tNum > 0) {
		count++;
		tNum = tNum/10;
	}
	return count;
}

//to update the database
void DataStore::updateDataBase() {
	dataBase.push_back(tempEntry);
}

//to update the temp database
void DataStore::updateTempDataBase(Entries entry) {
	tempDataBase.push_back(entry);
}
//to edit subject
void DataStore::editSubject(std::string newSubject, int index){
	dataBase[index].subject = newSubject;
}
//to edit time
void DataStore::editTime(int sTime, int eTime, int index){
	dataBase[index].startTime = sTime;
	dataBase[index].endTime = eTime;
}
// to edit date
void DataStore::editDate(int newDay, int newMonth, int newYear, int index){
	dataBase[index].day = newDay;
	dataBase[index].month = newMonth;
	dataBase[index].year = newYear;
}
// to edit priority
void DataStore::editPriority(std::string newPriority, int index){
	dataBase[index].impt = newPriority;
}
// to edit category
void DataStore::editCategory(std::string newCategory, int index){
	dataBase[index].category = newCategory;
}
//to update database with temp database
void DataStore::switchDataBase(){
	dataBase = tempDataBase;
}
//to clear temp data base
void DataStore::clearTempDataBase(){
	tempDataBase.clear();
}
//to delete the database
void DataStore::deleteDataBase(std::vector <Entries>::iterator iter) {
	dataBase.erase(iter);
}

std::string DataStore::getDate(int index){
	std::ostringstream date;
	int nDay = countDigit(dataBase[index].day);
	int nMonth = countDigit(dataBase[index].month);
	int nYear = countDigit(dataBase[index].year);

	if (nDay < 2) {
		date << '0';
	}
	date << dataBase[index].day << '/';
	
	if (nMonth < 2) {
		date << '0';
	}
	date << dataBase[index].month << '/';

	while (nYear < 4) {
		date<< '0';
		nYear++;
	}
	date << dataBase[index].year;

	return date.str();
}

std::string DataStore::getTime(int index){
	std::ostringstream time;
	int sTime = countDigit(dataBase[index].startTime);
	int eTime = countDigit(dataBase[index].endTime);
	

	while (sTime < 4) {
		time << '0';
		sTime++;
	}
	time << dataBase[index].startTime << '-';

	while (eTime < 4) {
		time << '0';
		eTime++;
	}
	time << dataBase[index].endTime;

	return time.str();
}

//to access the private data string in the datastore
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


//'Auto Save the file'
void DataStore::updateFile(std::string &fileName) {
	std::ofstream writeFile;

	writeFile.open(fileName);
	for (int index = 0; index != dataBase.size(); index++) {
		writeFile << getDataString(index) << "\n";
	}
	writeFile.close();
}
//print temporary data base
std::string DataStore::printTempDataBase(){
	std::ostringstream print;

	for(int index = 0; index < tempDataBase.size(); index++){
	int sTime = countDigit(tempDataBase[index].startTime);
	int eTime = countDigit(tempDataBase[index].endTime);
	int nDay = countDigit(tempDataBase[index].day);
	int nMonth = countDigit(tempDataBase[index].month);
	int nYear = countDigit(tempDataBase[index].year);

	print << tempDataBase[index].index << ". " << tempDataBase[index].subject << "\nTime: ";
	
	while (sTime < 4) {
		print << '0';
		sTime++;
	}
	print << tempDataBase[index].startTime << '-';

	while (eTime < 4) {
		print << '0';
		eTime++;
	}
	print << tempDataBase[index].endTime << "\t\tDate: ";
	
	if (nDay < 2) {
		print << '0';
	}
	print << tempDataBase[index].day << '/';
	
	if (nMonth < 2) {
		print << '0';
	}
	print << tempDataBase[index].month << '/' << tempDataBase[index].year << "\tPriority: " << tempDataBase[index].impt << "\tCategory: " << tempDataBase[index].category << '\n';
	}
	return print.str();
}
//to store the parsed information into a temporary entry object to store into the vector
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
