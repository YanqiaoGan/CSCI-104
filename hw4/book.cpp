#include "book.h"
#include "util.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string> 
using namespace std;

Book::Book(std::string category, std::string name, double price, int qty, 
			std::string ISBN, std::string author):
	Product(category,name,price,qty),
    ISBN_(ISBN),
    author_(author)
{

}

Book::~Book(){

}

set<std::string> Book::keywords() const{
	set<string> k1 = parseStringToWords(getName());
	set<string> k2 = parseStringToWords(getAuthor());
	set<string> temp = setUnion(k1, k2);
	temp.insert(getISBN());
	return temp;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const{
	return true;
}

string Book::displayString() const{
	string temp;
	temp = temp + getName() + '\n';
	temp = temp + "Author: " + getAuthor() + " ISBN: " + getISBN() + '\n';
	stringstream ss;
	ss << setprecision(2) << fixed << showpoint << getPrice();
	ss << setw(3) << to_string(getQty());
	temp = temp + ss.str() + " left." + '\n';
	return temp;
}

void Book::dump(std::ostream& os) const{
	os << "book" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << getISBN() << endl;
	os << getAuthor() << endl;
}

string Book::getISBN () const{
	return ISBN_;
}

string Book::getAuthor() const{
	return author_; 
}