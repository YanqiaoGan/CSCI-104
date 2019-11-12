/* Write your test code for the ULListStr in this file */

#include <iostream>
#include <string>
#include "ulliststr.h"
using namespace std;


int main(int argc, char* argv[])
{
	ULListStr test;
	cout << "start" << endl;
	// push_back function: 
	// Case1: The new value is the first element in the list
	test.push_back("a");
	cout << "first element: " << test.front() << endl;
	cout << "last element: " << test.back() << endl;
	cout << "current size: " << test.size() << endl;
	cout << "get: " << test.get(0) << endl;
	// Case2: Some basic cases
	test.push_back("b");
	test.push_back("c");
	test.push_back("d");
	test.push_back("e");
	test.push_back("f");
	test.push_back("g");
	test.push_back("h");
	test.push_back("i");
	test.push_back("j");
	cout << "first element: " << test.front() << endl;
	cout << "last element: " << test.back() << endl;
	cout << "current size: " << test.size() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
	// Case3: Boundary case where new item need to be allocated
	test.push_back("k");
	test.push_back("l");
	cout << "last element:" << test.back() << endl;
	cout << "current size: " << test.size() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
     
	// pop_back function:
	// Case1: basic case
	test.pop_back();
	cout << "current size: " << test.size() << endl;
	cout << "last element:" << test.back() << endl;
    // Case2: Boundary case where the last item will be deallocated
	test.pop_back();
	cout << "current size: " << test.size() << endl;
	cout << "last element:" << test.back() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
	// Case3: deallocate the last item
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	cout << "current size: " << test.size() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;

    // push_front function
    // Case1: Add the first element in the list
	test.push_front("a");
	cout << "first element: " << test.front() << endl;
	cout << "current size: " << test.size() << endl;
	// Case2: Basic cases
	test.push_front("b");
	test.push_front("c");
	test.push_front("d");
	test.push_front("e");
	test.push_front("f");
	test.push_front("g");
	test.push_front("h");
	test.push_front("i");
	test.push_front("j");
	cout << "first element: " << test.front() << endl;
	cout << "current size: " << test.size() << endl;
    cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
	// Case3: Boundary case (Allocate a new item)
	test.push_front("k");
	cout << "first element: " << test.front() << endl;
	cout << "current size: " << test.size() << endl;
    cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;


	// pop_front function
	// Case1: Boundary case (Deallocate an itme)
	test.pop_front();
	cout << "current size: " << test.size() << endl;
	cout << "first element: " << test.front() << endl;
	// Case2: Basic case
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	test.pop_front();
	cout << "current size: " << test.size() << endl;
	cout << "first element: " << test.front() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
	// Case3: the last element in the list
	cout << "Case3" << endl;
	test.pop_front();
	cout << "current size: " << test.size() << endl;
	cout << "current elements: ";
	for(int i = 0; (size_t)i < test.size(); i++){
		cout << test.get(i) << " ";
	}
	cout << endl;
    return 0;
}
