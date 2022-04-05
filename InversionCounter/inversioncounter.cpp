/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Erik Anhorn
 * Version     : 1.0
 * Date        : October 30, 2021
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long num_inversions = 0;
	for(int i=0; i<length-1;i++){
		for(int j=i+1; j<length ;j++){
			if(array[i]>array[j])
				num_inversions++;
		}
	}
	return num_inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
	vector<int> scratch(length);
	return mergesort(array, &scratch[0], 0, length-1);
    // Hint: Use mergesort!
}

static long modified_merge(int array[], int scratch[], int low, int mid, int high){
	long num_inver = 0;
	int i=low;
	int j=mid+1;
	int k=low;
	while(i<=mid && j<=high){
		if(array[i]<=array[j]){																													//Value in 1st sub array is lower, no inversion
			scratch[k++] = array[i++];
		}
		else{																																			//Value in 2nd sub array is lower, have mid-i inversions
			scratch[k++] = array[j++];
			num_inver += (mid-i+1);																										//Increments num_inver by how many values are greater than array[j] in the 1st sub array
		}
	}
	while(i<=mid){																																	//Moves rest of 1st sub array into scratch
		scratch[k++]=array[i++];
	}
	while(j<=high){																																//Moves rest of 2nd sub array into scratch
		scratch[k++]=array[j++];
	}
	for(int m = low; m<=high;m++)  																								   	//Moves values from scratch back into array
		array[m] = scratch[m];
	return num_inver;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long num_inversions = 0;
	if(low<high){
		int mid = low+(high-low)/2;
		num_inversions += mergesort(array, scratch, low, mid);													//Does a merge sort of the 1st half of the array
		num_inversions += mergesort(array, scratch, mid+1, high);											//Does a merge sort of the 2nd half of the array
		num_inversions += modified_merge(array, scratch, low, mid, high);							//Merges the 2 sorted halves together
	}
	return num_inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	bool isFast = false;
	if(argc == 2){
		string inp = argv[1];
		if(inp.compare("slow")!=0){
			cerr << "Error: Unrecognized option '" << argv[1] << "'." <<endl;
			return 1;
		}
	}
	else if (argc == 1){
		isFast = true;
	}
	else{
		cerr << "Usage: "<<argv[0] << " [slow]" <<endl;
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    // TODO: produce output
    int length = values.size();
    if (length ==0){
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }
    else if(isFast){
    	cout << "Number of inversions: "<<count_inversions_fast(&values[0], length) << endl;
    }
    else{
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], length) << endl;
    }

    return 0;
}
