#include "movie.h"
#include "util.h"
#include <iostream>
#include <string> 
#include <sstream>
#include <iomanip>
using namespace std;

Movie::Movie(std::string category, std::string name, double price, int qty, 
			std::string genre, std::string rating):
	Product(category,name,price,qty),
    genre_(genre),
    rating_(rating)
{

}

Movie::~Movie(){

}

set<std::string> Movie::keywords() const{
	set<string> temp = parseStringToWords(getName());
	temp.insert(getGenre());
	return temp;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
	return true;
}

string Movie::displayString() const{
	string temp;
	temp = temp + getName() + '\n';
	temp = temp + "Genre: " + getGenre() + " Rating: " + getRating() + '\n';
	stringstream ss;
	ss << setprecision(2) << fixed << showpoint << getPrice();
	ss << setw(3) << to_string(getQty());
	temp = temp + ss.str() + " left." + '\n';
	return temp;
}

void Movie::dump(std::ostream& os) const{
	os << "movie" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << getGenre() << endl;
	os << getRating() << endl;
}

string Movie::getGenre () const{
	return genre_;
}

string Movie::getRating() const{
	return rating_; 
}