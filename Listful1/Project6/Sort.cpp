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

//sorts memory
void Sort::Switch(int &index, int &start, DataStore &data){
	
	DataStore temp;

	for(int i = 0; i <data.getDataBaseSize(); i++){
	if (i<start){
		temp.getDataBase()[i] = data.getDataBase()[i]; 
		}
	else if(i == start){
		temp.getDataBase()[i] = data.getDataBase()[index]; 
		temp.getDataBase()[i+1] = data.getDataBase()[i]; //may have some problems
		}
	else if(i != index){
		temp.getDataBase()[i] = data.getDataBase()[i]; 
		}
	}
	data.getDataBase() = temp.getDataBase();
};
//sorts memory
void Sort::sortContent(std::string &fileName, DataStore &data, std::string command){
	
	category = determineCategory(command);
	
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

		case TIME:
			
			break;
		
		case DATE:
			
			break;
		
		case IMPT:
			
			break;

		case CATEGORY:
			
			break;

		default:
			std::cout << "Sort command is invalid.\n";
			return;
	}

	
		

	std::cout << "Sorted" <<  std::endl;
	std::cout << std::endl;
};