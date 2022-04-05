/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      :  Erik Anhorn
 * Date        :  10/02/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> outer;
vector<int> inner;

vector< vector<int> > get_ways(int num_stairs) {
	if(num_stairs<=0){																	//Base Case
		outer.push_back(inner);															//Puts whatever is in inner on the end of outer, this should be a complete way to climb the stairs
	}
	int numSteps = 1;
	while(numSteps<4 && numSteps<=num_stairs){											//Starts with steps of 1 and increments to steps of 3, updating the inner vector, recursively 																
		inner.push_back(numSteps);														//calling the method for one less stair, then working back up cleaning out inner along the way.
		get_ways(num_stairs-numSteps);
		inner.pop_back();
		numSteps++;
	}																														
	return outer;																		//Returns the final list of ways
}

int numDigits(int num) {
    int numDigits = 1;																	//Divides by 10 until there is no remainder, no remainder means
    while(num/10 !=0){																	//you have gotten to the ones place
    	num = num/10;
    	numDigits ++;
    }
    return numDigits;
}


void display_ways(const vector< vector<int> > &ways) {
	if(ways[0].size()==1)
		cout << ways.size() << " way to climb " << ways[0].size() << " stair." << endl;
	else
		cout << ways.size() << " ways to climb " << ways[0].size() << " stairs." << endl;
	for(unsigned int i=0;i<ways.size();i++){
		int j = numDigits(ways.size());
		int k = numDigits(i+1);
		while(j>k){
			cout << " ";
			k++;
		}
		cout << i+1 << ". " << "[";
		for(unsigned int l=0;l<ways[i].size();l++){
			if(l==ways[i].size()-1)
				cout << ways[i][l];
			else{
				cout << ways[i][l] << ", ";
			}
		}
		cout << "]" << endl;
	}
}


int main(int argc, char * const argv[]) {
	istringstream iss;
	int numStairs;
	if(argc !=2){
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return  1;
	}
	iss.str(argv[1]);
	if(!(iss>>numStairs) || numStairs<=0){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	display_ways(get_ways(numStairs));
	return 0;
}
