#ifndef CATEGORY_H
#define CATEGORY_H

#include "DataStore.h"

class Category {
	private:
		std::string _cat;

	public:
		Category() {};

		bool extractCat(int, std::string &, size_t);
		void updateStr(std::string &, size_t);

		std::string &getCat();
};

#endif