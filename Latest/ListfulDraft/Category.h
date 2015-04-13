#ifndef CATEGORY_H
#define CATEGORY_H

#include "DataStore.h"

class Category {
	private:
		std::string _cat;

	public:
		Category() {};

		bool checkForCat(int, std::string &, size_t);
		void extractRemainingStr(std::string &, size_t);

		std::string &getCat();
};

#endif