#ifndef CLASSES_H
#define CLASSES_H

#include "Date.h"
#include "Time.h"
#include "Add.h"
#include "Priority.h"
/*#include "Clear.h"
#include "Delete.h"
#include "Display.h"
#include "Edit.h"
#include "Sort.h"
#include "Search.h"*/

class Classes {
public:
	Add add;
	/*Display display;
	Delete remove;
	Edit edit;
	Clear clearFile;
	Search searchFile;
	Sort sortFile;*/
	Time time;
	Date date;
	Priority priority;
};

#endif