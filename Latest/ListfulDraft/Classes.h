//@author A0110670W
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
#include "Log.h"

class Classes {
	public:
		enum commandType {
			ADD, SEARCH, CLEAR, EDIT, SORT, REMOVE, DO_NOTHING, UNDO, REDO, INVALID, EXIT
		};

		enum fieldType {
			SUBJECT, DATE, TIME, PRIORITY, CATEGORY, INVALIDFIELD
		};

		enum priorityType {
			LOW, MEDIUM, HIGH, PINVALID
		};

		enum catType {
			WORK, PERSONAL, ERRAND, GENERAL, CINVALID
		};

		Classes () {};
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
		int determineField(std::string);
		int determinePriority(std::string);
		int determineCategory(std::string);
};

#endif