#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore{
public:
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	std::map<std::string, std::set<Product*>> keywords;
	std::map<std::string, User*> users;
	std::map<std::string, Product*> products; 
	std::map<User*, std::queue<Product*>> carts;
};

#endif