#ifndef CLASSES_H
#define CLASSES_H

#include "Timing.h"
#include "Date.h"
#include "Add.h"
#include "Priority.h"
#include "Category.h"
#include "Clear.h"
#include "Delete.h"
#include "Display.h"
#include "Edit.h"
#include "Sort.h"
#include "Search.h"

class Classes {
public:
	enum commandType {
		ADD, DISPLAY, CLEAR, EDIT, SORT, SEARCH, REMOVE, UNDO, REDO, INVALID, DO_NOTHING, EXIT
	};

	enum subCategory {
		SUBJECT, DATE, TIME, PRIORITY, CATEGORY, INVALIDCAT
	};

	enum priorityType {
		LOW, MEDIUM, HIGH, PINVALID
	};

	enum catType {
		WORK, PERSONAL, ERRAND, INBOX, CINVALID
	};

	Add add;
	Delete remove;
	Display display;
	Edit edit;
	Search searchFile;
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