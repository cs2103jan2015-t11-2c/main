#ifndef DELETE_H
#define DELETE_H

#include "DataStore.h"

class Delete {
public:
	Delete() {};

<<<<<<< HEAD
	bool deleteContent(DataStore &, int);
=======
	void deleteContent(DataStore &, std::string);
	void deletebyIndex(DataStore &, int);
	void deletebySubject(DataStore &, std::string, std::string);
>>>>>>> 4dfb43ee8728d222b443bcaf02e0b0f9ae646891
	int getContentIndex(DataStore &, std::string);
};

#endif