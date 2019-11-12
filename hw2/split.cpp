/*
CSCI 104: Homework 2 Problem 6

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;



void split(Node*& in, Node*& odds, Node*& evens){
	Node* temp1 = in;
	Node* temp2 = odds;
	Node* temp3 = evens;
	split_help(in, odds, evens, temp1, temp2, temp3);
	in = NULL;
	split_check(odds, 1);
	split_check(evens, 2);
}

void split_help(Node*& in, Node*& odds, Node*& evens, 
	Node*& temp1, Node*& temp2, Node*& temp3){
	if(temp1 == NULL){
		cout << "..." << endl;
		return;
	}else{
		if(temp1->value % 2 != 0){
			if(odds == NULL){
				odds = temp1;
				temp2 = odds;
			}else{
				temp2 = temp1; 
			}
			split_help(in, odds, evens, temp1->next, temp2->next, temp3);

		}else{
			if(evens == NULL){
				evens = temp1;
				temp3 = evens;
			}
			else{
				temp3 = temp1;
			}
			split_help(in, odds, evens, temp1->next, temp2, temp3->next);
		}
	}
}






void split_check(Node*& temp, int type){
	if(type == 1){
		if(temp == NULL){
			return;
		}else{
			if(temp->value % 2 == 0){
				temp = NULL;
			}else{
				split_check(temp->next, type);
			}
		}
	}else{
		if(temp == NULL){
			return;
		}else{
			if(temp->value % 2 != 0){
				temp = NULL;
			}else{
				split_check(temp->next, type);
			}
		}
	}
}	