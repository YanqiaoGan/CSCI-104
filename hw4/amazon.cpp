#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <queue>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;


    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    map<User*, queue<Product*>> carts = ds.carts;
    map<string, User*> users = ds.users;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
            else if( cmd == "ADD"){
                string username;
                int hit_result_index;
                ss >> username;
                if(ss.fail()){
                    cout << "1" << "Invalid request" << endl;
                    return 1;
                }
                ss >> hit_result_index;
                if(ss.fail()){
                    cout << "2" << "Invalid request" << endl;
                    return 1;
                }
                Product* item = hits[hit_result_index-1];

                User* consumer = users.find(username)->second;
                if(carts.find(consumer) != carts.end()){
                    carts.find(consumer)->second.push(item);
                }else{
                    cout << "3" << "Invalid request" << endl;
                    return 1;
                }
            }
            else if( cmd == "VIEWCART"){
                string username;
                ss >> username;
                if(ss.fail()){
                    cout << "Invalid request" << endl;
                    return 1;
                }
                if(ds.users.find(username) == ds.users.end()){
                    cout << "Invalid username" << endl;
                    return 1;
                }
                User* consumer = users.find(username)->second;
                queue<Product*> temp = carts.find(consumer)->second;
                int size = temp.size();
                for(int i = 0; i < size; i++){
                    cout << "Item " << i+1 << endl;
                    Product* p = temp.front();
                    temp.pop();
                    temp.push(p);
                    cout << p->displayString() << endl;
                }
            }
            else if( cmd == "BUYCART"){
                string user;
                ss >> user;
                if(ss.fail()){
                    cout << "Invalid request" << endl;
                    return 1;
                }
                if(users.find(user) == users.end()){
                    cout << "Invalid username" << endl;
                    return 1;
                }
                User* consumer = users.find(user)->second;
                Product* recent = carts.find(consumer)->second.front();
                while(!carts.find(consumer)->second.empty() && consumer->getBalance()-recent->getPrice() >= 0){
                    carts.find(consumer)->second.pop();
                    consumer->deductAmount(recent->getPrice());
                    recent = carts.find(consumer)->second.front();
                }
            }
            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        //cout << endl;
        resultNo++;
    }
}
