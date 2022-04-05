/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Erik Anhorn
 * Date        : 	9/23/2021
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
	for(int i=0; i<(int)(s.length());i++){
		if(!(isalpha(s.at(i))))																//Checks if the character is a letter and if it is lower case, if either if false
				return false;																					//It will return false
		else{
			if(!(islower(s.at(i))))
				return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
	int haveSeen =0;
	for(int i=0; i<(int)(s.length());i++){
		if((haveSeen&(1<<(s.at(i)-'a')))!=0)																//Checks if storage int hasSeen has an overlap with the current char,
			return false;																								//Returns false the 2 have overlap, sets the current position of s' char
		haveSeen = haveSeen | (1<<(s.at(i)-'a'));													//In hasSeen to 1 to mark it as seen. Overlap means we have seen the
	}																															//Character before.
	return true;
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	string input;
	if(argc==1){																											//Here the only thing in argument line is the function call
		cerr << "Usage: "<<argv[0] << " <string>"<<endl;
		return 1;
	}
	else if (argc>=3){																									//Here there is more than 1 string passed with arguments
		cerr << "Usage: "<<argv[0]<<" <string>"<<endl;
		return 1;
	}
	iss.str(argv[1]);
	iss>>input;
	if(is_all_lowercase(input)){
		if(all_unique_letters(input)){
			cout << "All letters are unique."<<endl;
		}
		else{
			cout << "Duplicate letters found." << endl;
		}
		return 0;
	}
	else{
		cerr << "Error: String must contain only lowercase letters."<<endl;
		return 1;
	}
}
