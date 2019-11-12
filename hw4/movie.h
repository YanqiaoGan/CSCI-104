#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h" 
#include "util.h"

class Movie : public Product{
	public:
		Movie(std::string category, std::string name, double price, int qty, 
			std::string genre, std::string rating);
	    ~Movie();
		std::set<std::string> keywords() const;
		bool isMatch(std::vector<std::string>& searchTerms) const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
		std::string getGenre() const;
		std::string getRating() const;
	private: 
		std::string genre_;
		std::string rating_;
};
#endif