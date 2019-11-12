#include "split.h"
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]){
	Node* n7 = new Node(9, NULL);
	Node* n6 = new Node(8, n7);
	Node* n5 = new Node(4, n6);
	Node* n4 = new Node(4, n5);
	Node* n3 = new Node(3, n4);
	Node* n2 = new Node(2, n3);
	Node* n1 = new Node(1, n2);
	Node* odds = NULL; 
	Node* evens = NULL; 
	split(n1, odds, evens);
	Node* temp = n1;
	cout << "in: ";
	while(temp != NULL){
		cout << temp->value << " ";
		temp = temp->next;
	}
	cout << endl;
	cout << "odds: ";
	Node* temp1 = odds;
	while(temp1 != NULL){
		cout << temp1->value << " ";
		temp1 = temp1->next;
	}
	cout << endl;
	cout << "evens: ";
	Node* temp2 = evens;
	while(temp2 != NULL){
		cout << temp2->value << " ";
		temp2 = temp2->next;
	}
	cout << endl;
}