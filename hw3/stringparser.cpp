#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cstring>
#include "stackstring.h"
using namespace std;

string remove(StackString&, int, int, bool&, ofstream&);
string add(string, string);
string substract(string, string);

int main(int argc, char** argv)
{	
	if(argc < 2){
		cout << "Insufficient input" << endl;
		return 1;
	}
	char *iname = argv[1];
	char *oname = argv[2];
	ifstream ifile(iname);
	if(ifile.fail()){
		cout << "Error: couldn't open file" << endl;
		return 1;
	}
	ofstream ofile(oname);
	string myline;
	while(getline(ifile,myline)){
		StackString s1;
		int i = 0;
		bool malformed = false;
		while ((unsigned)i < myline.length() && !malformed){
			char temp = myline[i];
			i++;
			if(isspace(temp)){
				
			}else if(!islower(temp) && temp != '<' && temp != '>' && 
				temp != '+' && temp != '-' && temp != '(' && temp != ')'){
				malformed = true;
			}else{
				if(islower(temp)){
					string current;
					current.push_back(temp);
					while(islower(myline[i])){
						current.push_back(myline[i]);
						i++;
					}
					s1.push(current);
				}else{
					string s(1,temp);
					s1.push(s);
				}
			}
		}
		if(malformed){
			ofile << "Malformed" << endl;
		}else if(s1.empty()){
			ofile << endl;
		}else{
			StackString s2;
			while(s1.size()!=1 && !malformed){
				string temp = s1.top();
				if(temp == ")"){
				// reach the end of inner loop and push to s2
					while(temp != "(" && !s1.empty()){
						s2.push(temp);
						s1.pop();
						if(!s1.empty()){
							temp = s1.top();
						}
					}
					if(s1.empty()){
						ofile << "Malformed" << endl;
						malformed = true;
					}else{
						s1.pop();
						while( !s2.empty() && s2.top() != ")" && !malformed){
							string last = s2.top();
							s2.pop();
							// push_back the processed string
							if(last == "<" || last == ">"){
								string current;
								if(last == "<"){
									current = remove(s2, 1, 0, malformed, ofile);
								}else{
									current = remove(s2, 0, 1, malformed, ofile);
								}
								if(!malformed){
									if(s2.top() == ")"){
											s1.push(current);
									}else{
											s2.push(current);
									}
							    }	
							}else if(islower(last[0])){
								string lhs = last;
								string next = s2.top();
								s2.pop();
								if(next == "+" || next == "-"){
									if(s2.top() == "<" || s2.top() == ">"){
										string current;
										current = remove(s2, 0, 0, malformed, ofile);
							    		s2.push(current);
									}
									if(islower(s2.top()[0])){
										string rhs = s2.top();
										s2.pop();
										string result;
										if(next == "+"){
											result = add(lhs, rhs);
											if (s2.top()!= "+" && s2.top() != ")"){
												ofile << "Malformed" << endl;
												malformed = true;
											}
										}else{
											result = substract(lhs, rhs);
											if(s2.top() != ")"){
												ofile << "Malformed" << endl;
												malformed = true;
											}
										}
										if(!malformed){	
											if(s2.top() == ")"){
												s1.push(result);
											}else{
												s2.push(result);
											}
										}	
									}else{
										ofile << "Malformed" << endl;
										malformed = true;
									}

								}else if(next == ")" ){
									s1.push(last);
								}else{
									ofile << "Malformed" << endl;
									malformed = true;
								}
							}else{
								ofile << "Malformed" << endl;
								malformed = true;
							}

						}
					}	
				}else if(islower(temp[0])){
					while(!s1.empty()){
						s2.push(s1.top());
						s1.pop();
					}
					string last = s2.top();
					s2.pop();
					// push_back the processed string
					if(last == "<" || last == ">"){
						string current;
						if(last == "<"){
							current = remove(s2, 1, 0, malformed, ofile);
						}else{
							current = remove(s2, 0, 1, malformed, ofile);
						}
						s1.push(current);
					}else{
						ofile << "Malformed" << endl;
						malformed = true;
					}	

				}else{
					ofile << "Malformed" << endl;
					malformed = true;
				}
				if(!s2.empty() && s2.top() == ")"){
					// discard the ")"
					s2.pop();
					while(!s2.empty()){
						string last = s2.top();
						s2.pop();
						s1.push(last);
					}
				}
			}
			if(!malformed){
				if(islower(s1.top()[0])){
					ofile << s1.top() << endl;
				}else{
					ofile << "Malformed" << endl;
					malformed = true;
				}
			}	
		}
	}
}

string remove(StackString& s2, int removeEnd, int removeStart, bool& malformed, ofstream& ofile){
	while(!islower(s2.top()[0])){
		string last = s2.top();
		s2.pop();
		if(last == "<"){
			removeEnd++;
		}else if(last == ">"){
			removeStart++;
		}else{
			malformed = true;
			ofile << "Malformed" << endl;
		}
	}
	if(!malformed){
		string current = s2.top();
		s2.pop();
		while(removeStart != 0){
			current = current.substr(1, current.size()-1);
			removeStart--;
		}
		while(removeEnd != 0){
			current = current.substr(0, current.size()-1);
			removeEnd--;
		}
		return current;
	}else{
		return s2.top();
	}	
}

string add(string lhs, string rhs){
	lhs.append(rhs);
	return lhs;
}

string substract(string lhs, string rhs){
	size_t pos = lhs.find(rhs);
	if(pos != string::npos){
		lhs.erase(pos, rhs.size());
	}
	return lhs;
}