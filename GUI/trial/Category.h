#pragma once

#ifndef CATEGORY_H
#define CATEGORY_H

#include "DataStore.h"

class Category {
private:
	std::string _cat;

public:
	Category() {};

	bool extractCat(std::string &);
	void updateStr(std::string &, size_t);
	void removeEndChar(std::string &);

	std::string getCat();
};

#endif
