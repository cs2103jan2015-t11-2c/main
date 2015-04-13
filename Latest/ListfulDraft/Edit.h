//@author A0116237L
#ifndef EDIT_H
#define EDIT_H

#define MIN -1

#include "DataStore.h"
#include "Add.h"
#include "Search.h"
#include "Sort.h"

class Edit {
	private:
		Entry _editEntry;

		Add add;
		Search search;
		Sort sort;

	public:
		Edit() {};
		
		bool checkAll(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::string);
		bool checkComplete(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::string);
		
		bool editContent(DataStore &, std::vector <int>, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::string, int = MIN);
		bool getEditIndex(std::string &, int &);
		void editTime(DataStore &, int);
		void editDate(DataStore &, int);
		
		void updateTemp(DataStore &, std::vector <int>);
		bool isRepeat(DataStore &, std::vector <int>, int);
		

};

#endif