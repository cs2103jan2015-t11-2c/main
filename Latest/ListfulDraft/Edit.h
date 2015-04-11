#ifndef EDIT_H
#define EDIT_H

#include "DataStore.h"
#include "Add.h"
#include "Display.h"
#include "Sort.h"

class Edit {
	private:
		int _category;
		Entry _editEntry;

		Add add;
		Display show;
		Sort sort;

	public:
		Edit() {};
	
		void updateTemp(DataStore &, std::vector <int>);
		bool isRepeat(DataStore &, std::vector <int>, int);
		bool checkAll(DataStore &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::string);
		bool checkComplete(DataStore &, std::string, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::string);
		bool editContent(DataStore &, int, std::ostringstream &, std::ostringstream &, std::ostringstream &, std::ostringstream &);
		void editTime(DataStore &, int);
		void editDate(DataStore &, int);

		int &getCat();
};

#endif