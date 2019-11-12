#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

// *You* are not allowed to use global variables
//  but for just the output portion *we* will. ;>
int combo = 1;

// @brief Prints a single combination of teams
//
// @param[in] team1 Array containing the names of team 1
// @param[in] team2 Array containing the names of team 2
// @param[in] len Size of each array
void printSolution(const string* team1, 
		   const string* team2,
		   int len)
{
  cout << "\nCombination " << combo++ << endl;
  cout << "T1: ";
  for(int i=0; i < len; i++){
    cout << team1[i] << " ";
  }
  cout << endl;
  cout << "T2: ";
  for(int i=0; i < len; i++){
    cout << team2[i] << " ";
  }
  cout << endl;
}

// You may add additional functions here
void formation(int total, string* people, int index1, int index2, int index3, 
  string* team1, string* team2){
  if(index1 == total/2 && index2 == total/2){
    printSolution(team1, team2, total/2);
  }else{
    if(index1 < total/2){
      team1[index1] = people[index3];
      formation(total, people, index1+1, index2, index3+1, team1, team2);
    }
    if(index2 < total/2){
      team2[index2] = people[index3];
      formation(total, people, index1, index2+1, index3+1, team1, team2);
    }
  }
}  



int main(int argc, char* argv[])
{
  if(argc < 2){
    cout << "Error: Please provide a file of names" << endl;
    return 1;
  }
  // Complete the rest of main
  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cout << "Error: Unable to open input file" << endl;
    return 1;
  }
  int total;
  ifile >> total;
  string *people = new string[total];
  string current;
  int index = 0;
  while(ifile >> current){
    people[index] = current;
    index++;
  }
  if(index != total){
    cout << "Error: Inconsistent data" << endl;
    return 1; 
  }
  string *team1 = new string[total/2];
  string *team2 = new string[total/2];
  formation(total, people, 0, 0, 0, team1, team2);
  delete[] people;
  delete[] team1;
  delete[] team2;
  return 0;
}
