/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Erik Anhorn
 * Date        : September 9, 2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }
    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    int get_max_prime();
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit+1]}, limit_{limit}{
    for(int i=2;i<=limit_;i++){
    	is_prime_[i]=true;
    }
    sieve();
}

void PrimesSieve::display_primes() const {
	cout << "Number of primes found: "<< num_primes_ << endl;
	cout << "Primes up to " << limit_ << ":" << endl;
	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80/(max_prime_width+1);		//Starts at 2 since 2 is the first prime num, outputs spaces for the difference
    int n = 1;
    if(num_primes_<=primes_per_row){
    	for(int m=2; m<=limit_;m++){
    		if(is_prime_[m]){
    			cout << m;
    			if(n<limit_-1 && m!=max_prime_)
    				cout << " ";
    			n++;
    		}
    	}
    }
    else{
    	for(int m=2;m<=limit_;m++){
    		if(n>primes_per_row){
    			cout << endl;
    			n = 1;
    		}
    		if(is_prime_[m]){
    			cout << setw(max_prime_width) << m;
    			if(n<primes_per_row && m!=max_prime_){
    				cout << " ";
    			}
    			n++;
    		}
    	}
    }
}

void PrimesSieve::sieve() {																				//Uses the given algorithm for sieve.
	for(int i=0;i<=sqrt(limit_); i++){
    	if(is_prime_[i]){
    		for(int j=i*i;j<=limit_;j+=i){
    			is_prime_[j] = false;
    		}
    	}
    }
	int numOfPrimes=0;
	int lastPrime;
		for(int i=0; i<=limit_;i++){
			if(is_prime_[i]){
				numOfPrimes++;
				lastPrime = i;
			}
		}
	    num_primes_ = numOfPrimes;
	    max_prime_ = lastPrime;
}

int PrimesSieve::num_digits(int num) {
    int numDigits = 1;																					//Divides by 10 until there is no remainder, no remainder means
    while(num/10 !=0){																					//you have gotten to the ones place
    	num = num/10;
    	numDigits ++;
    }
    return numDigits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve primeNums = PrimesSieve(limit);
    cout << endl;
    primeNums.display_primes();
    return 0;
}
