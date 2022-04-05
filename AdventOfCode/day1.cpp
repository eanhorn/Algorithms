#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;
int main(int argc, char *argv[]){
//	part 1
//	ifstream inputFile(argv[1]);
//	string line;
//	int lastNum=0, currNum, numIncreases=0;
//	int lineNum = 1;
//	while(getline(inputFile, line)){
//		istringstream iss(line);
//		cout << line << endl;
//		if(!(iss >> currNum)){
//			lineNum++;
//			continue;
//		}
//		else if(lineNum == 1){
//			lineNum++;
//			lastNum = currNum;
//			continue;
//		}
//		if(currNum>lastNum)
//			numIncreases++;
//		lastNum = currNum;
//	}
//	cout << numIncreases << endl;

//	part 2
	ifstream inputFile(argv[1]);
	string line;
	queue<int> sums;
	int lineNum = 1, firstNum;
	while(getline(inputFile, line)){
		istringstream iss(line);
		if(lineNum == 1){
			iss >> firstNum;
			continue;
		}

	}
}
