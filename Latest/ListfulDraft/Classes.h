#ifndef CLASSES_H
#define CLASSES_H

#include "Timing.h"
#include "Date.h"
#include "Add.h"
#include "Priority.h"
#include "Category.h"
#include "Clear.h"
#include "Delete.h"
#include "Edit.h"
#include "Sort.h"
#include "Search.h"

class Classes {
	public:
		enum commandType {
			ADD, SEARCH, CLEAR, EDIT, SORT, REMOVE, DO_NOTHING, UNDO, REDO, INVALID, EXIT
		};

		enum subCategory {
			SUBJECT, DATE, TIME, PRIORITY, CATEGORY, INVALIDCAT
		};

		enum priorityType {
			LOW, MEDIUM, HIGH, PINVALID
		};

		enum catType {
			WORK, PERSONAL, ERRAND, GENERAL, CINVALID
		};

		Add add;
		Delete remove;
		Search search;
		Edit edit;
		Sort sortFile;
		Clear clearFile;
		Timing time;
		Date date;
		Priority priority;
		Category category;

		int determineCommand(std::string);
		int determineSubCat(std::string);
		int determineP(std::string);
		int determineC(std::string);
};

#endif