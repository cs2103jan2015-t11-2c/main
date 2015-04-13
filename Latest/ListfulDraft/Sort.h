//@author A0116237L
#ifndef SORT_H
#define SORT_H

#include "DataStore.h"

class Sort {
	private:
		enum priorityType {
			LOW, MEDIUM, HIGH, PINVALID
		};

		enum catType {
			WORK, PERSONAL, ERRAND, GENERAL, CINVALID
		};

		int _category;

	public:
		Sort() {};

		bool sortContent(DataStore &);
	
		void shiftPos(int &, int &, DataStore &);
	
		void sortSub(DataStore &);
		void compareLineSize(std::string &, std::string &, std::string &);
		bool isUpperCase(std::string, std::string, int, char &);
		bool isLargerChar(std::string &, std::string &, std::string &);	
	
		void sortDate(DataStore &);
		void sortComplete(DataStore &);
		void sortTime(DataStore &);

		int determineCategory(std::string);
		void sortCat(DataStore &);

		void sortPriority(DataStore &);
		int determinePriority(std::string);

		bool cmpSame(DataStore & ,int, int);

		int &getSortCat();
};

#endif