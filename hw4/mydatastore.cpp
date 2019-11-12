#include "mydatastore.h"
using namespace std;
MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
	for(map<string, Product*>::iterator it = products.begin(); it != products.end(); ++it){
		delete it->second;
	}
	for(map<string, User*>::iterator it = users.begin(); it != users.end(); ++it){
		delete it->second;
	}
} 

void MyDataStore::addProduct(Product* p){
	products.insert(pair<string, Product*>(p->getName(), p));
	set<string> temp = p->keywords();
	for(set<string>::iterator it = temp.begin(); it != temp.end(); ++it){
		if(keywords.find(*it) == keywords.end()){
			set<Product*> current;
			current.insert(p);
			keywords.insert(pair<string, set<Product*>>(*it, current));
		}else{
			keywords.find(*it)->second.insert(p);
		}
	}
}

void MyDataStore::addUser(User* u){
	if(users.find(u->getName()) == users.end()){
		users.insert(pair<string, User*>(u->getName(), u));
		queue<Product*> current;
		carts.insert(pair<User*, queue<Product*>>(u, current));
	}
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
	for(map<string, set<Product*>>::iterator it = keywords.begin(); it != keywords.end(); ++it){
		string temp = it->first;
		set<Product*> s = it->second;
	}
	vector<Product*> result;
	if(type == 0){
		//AND search
		set<Product*> all;
		if(!terms.empty()){
			string s = terms[0];
			for(int i = 0; i < (signed)s.size(); i++){
				s[i] = tolower(s[i]);
			}
			if(keywords.find(s) != keywords.end()){				
				all = keywords.find(s)->second;
				for(int i = 0; i < (signed)terms.size(); i++){
					string s = terms[i];
					for(int i = 0; i < (signed)s.size(); i++){
						s[i] = tolower(s[i]);
					}
					if(keywords.find(s) != keywords.end()){
						set<Product*> temp = keywords.find(s)->second;
						all = setIntersection(all, temp);
					}	
				}
			}	
		}		
		for(set<Product*>::iterator it = all.begin(); it != all.end(); ++it){
			result.push_back(*it);
		}	
		return result;
	}else{
		//OR search
		set<Product*> all;
		if(!terms.empty()){
			string s = terms[0];
			for(int i = 0; i < (signed)s.size(); i++){
				s[i] = tolower(s[i]);
			}
			if(keywords.find(s) != keywords.end()){				
				all = keywords.find(s)->second;
				for(int i = 1; i < (signed)terms.size(); i++){
					string c = terms[i];
					for(int i = 0; i < (signed)c.size(); i++){
						c[i] = tolower(c[i]);
					}
					if(keywords.find(c) != keywords.end()){
						set<Product*> temp = keywords.find(c)->second;         
						all = setUnion(all, temp);                        
					}	
				}
			}
		}
		for(set<Product*>::iterator it = all.begin(); it != all.end(); ++it ){
			result.push_back(*it);
		}
		return result;
	}
}

void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << endl;
	for(map<string, Product*>::iterator it = products.begin(); 
		it != products.end(); ++it){
		it->second->dump(ofile);
	}
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for(map<string, User*>::iterator it = users.begin(); it != users.end(); ++it){
		it->second->dump(ofile);
	}
	ofile << "</users>" << endl;
}