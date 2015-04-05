#include "Sort.h"

//determine what category user chooses to sort by
int Sort::determineCategory(std::string category) {
	if (category == "date") {
		return subCategory::DATE;
	}
	else if (category == "subject") {
		return subCategory::SUBJECT;
	}
	else if (category == "time") {
		return subCategory::TIME;
	}
	else if (category == "impt") {
		return subCategory::IMPT;
	}
	else if (category == "category") {
		return subCategory::CATEGORY;
	}
	else {
		return subCategory::INVALID;
	}
}

//switches the structures
void Sort::Switch(int &index, int &start, DataStore &data){
	
	for(int i = 0; i <data.getDataBaseSize(); i++){
	if (i<start){
		data.updateTempDataBase(data.getDataBase()[i]); 
		}
	else if(i == start){
		data.updateTempDataBase(data.getDataBase()[index]); 
		data.updateTempDataBase(data.getDataBase()[i]); 
		}
	else if(i != index){
		data.updateTempDataBase(data.getDataBase()[i]); 
		}
	}

	data.switchDataBase();
	data.clearTempDataBase();
};
//to sort content
void Sort::sortContent(std::string &fileName, DataStore &data, std::string field){
	
	category = determineCategory(field);
	
	switch (category) {
		case SUBJECT:
			for(int index = 1; index < data.getDataBaseSize(); index++){
				for (int start = 0; start < index; start++){
					if (data.getSubject(start) > data.getSubject(index)){
						Switch(index,start,data);
						}
					}
				}	
			break;
		
		case DATE:
			for(int index = 1; index < data.getDataBaseSize(); index++){
				for (int start = 0; start < index; start++){
					if (data.getYear(start) > data.getYear(index)){
						Switch(index,start,data);
						}
					else if (data.getYear(start) == data.getYear(index))
						if (data.getMonth(start) > data.getMonth(index)){
							Switch(index,start,data);
							}
						else if (data.getMonth(start) == data.getMonth(index))
							if (data.getDay(start) > data.getDay(index)){
								Switch(index,start,data);
								}
							else if (data.getDay(start) == data.getDay(index))
								if (data.getStartTime(start) > data.getStartTime(index)){
									Switch(index,start,data);
									}
					}	
				}	
			break;

		default:
			std::cout << "Sort command is invalid.\n";
			return;
	}

	
	std::cout << "Sorted" <<  std::endl;
	std::cout << std::endl;
};