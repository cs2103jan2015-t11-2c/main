#ifndef CLASSES_H
#define CLASSES_H

#include "Date.h"
#include "Time.h"
#include "Add.h"
#include "Priority.h"
#include "Category.h"
#include "Clear.h"
//#include "Delete.h"
/*#include "Display.h"
#include "Edit.h"*/
#include "Sort.h"
//#include "Search.h"

class Classes {
public:
	Add add;
	//Delete remove;
	/*Display display;
	Edit edit;
	Search searchFile;*/
	Sort sortFile;
	Clear clearFile;
	Time time;
	Date date;
	Priority priority;
	Category category;
};

#endif