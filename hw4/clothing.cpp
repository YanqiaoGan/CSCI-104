#include "clothing.h"
#include "util.h"
#include <iostream>
#include <string> 
#include <sstream>
#include <iomanip>
using namespace std;

Clothing::Clothing(std::string category, std::string name, double price, int qty, 
			std::string size, std::string brand):
	Product(category,name,price,qty),
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing(){

}

set<std::string> Clothing::keywords() const{
	set<string> k1 = parseStringToWords(getName());
	set<string> k2 = parseStringToWords(getBrand());
	set<string> temp = setUnion(k1, k2);
	return temp;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
	return true;
}

string Clothing::displayString() const{
	string temp;
	temp = temp + getName() + '\n';
	temp = temp + "Size: " + getSize() + " Brand: " + getBrand() + '\n';
	stringstream ss;
	ss << setprecision(2) << fixed << showpoint << getPrice();
	ss << setw(3) << to_string(getQty());
	temp = temp + ss.str() + " left." + '\n';
	return temp;
}

void Clothing::dump(std::ostream& os) const{
	os << "book" << endl;
	os << getName() << endl;
	os << to_string(getPrice()) << endl;
	os << to_string(getQty()) << endl;
	os << getSize() << endl;
	os << getBrand() << endl;
}

string Clothing::getSize () const{
	return size_;
}

string Clothing::getBrand() const{
	return brand_; 
}