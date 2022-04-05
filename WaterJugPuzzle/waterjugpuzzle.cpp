/*******************************************************************************
 * Name    : waterjugpuzzle.cpp
 * Author  : Jared Kronyak and Erik Anhorn
 * Version : 1.0
 * Date    : October 16, 2021
 * Description : Solves the water jug puzzle.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <memory>

using namespace std;

struct State
{
	int a, b, c;
	string directions;
	shared_ptr<State> parent;

	State(int _a, int _b, int _c, string _directions, shared_ptr<State>_parent) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} {}

	// String representation of state in tuple form.
	string to_string()
	{
		ostringstream oss;
		oss << directions << " (" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};

/*******************************************************************************************************************************************
 * Pre-Condtions: receives int argc - the number of arguments, and char *argv[] - the arguments themselves. 
 * Post-Condition: returns true if the inputs are valid, false otherwise. 
*******************************************************************************************************************************************/
bool validateInput(int argc, char *argv[]) {

	string argument_labels[] = {"A", "B", "C"};
	int integer_arguments[6];
	// Handling for invalid number of arguments.
	if (argc != 7) {
		cout << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return false;
	}

	// Handling for non-integer arguments.
	for (int i = 1; i < argc; i++) {
		int cur;
		istringstream iss(argv[i]);
		if (!(iss >> cur) || cur < 0) {
			if(i < 4) {
				cerr << "Error: Invalid capacity \'" << iss.str() << "\' for jug " << argument_labels[i - 1] << "." << endl;
			} else {
				cerr << "Error: Invalid goal \'" << iss.str() << "\' for jug " << argument_labels[i - 4] << "." << endl;
			}
			iss.clear();
			return false;
		}
		else if(i==3 && cur==0){
			cerr << "Error: Invalid capacity \'" << iss.str() << "\' for jug "<<argument_labels[i-1] << "." << endl;
			iss.clear();
			return false;
		}
		iss.clear();
		integer_arguments[i-1] = cur;
	}
	// Handling for inputs of invalid goal based on capacity.
	for(int i = 0; i < 3; i++) {
		if(integer_arguments[i] < integer_arguments[i + 3]) {
			cerr << "Error: Goal cannot exceed capacity of jug " << argument_labels[i] << "." << endl;
			return false;
		}
	}

	// Handling for inputs of which the goal differs from the capacity of C.
	if( (integer_arguments[2]) !=integer_arguments[3] + integer_arguments[4] + integer_arguments[5] ) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return false;
	}

	return true;
}

/*******************************************************************************************************************************************
 * Pre-Condtions: int origin - the current amount of water stored in the jug which is being poured from, int target - the current amount
 * of water stored in the jug which is being poured into, and int target_cap - the capacity of the jug which is being poured into.
 * Post-Condition: returns true if the given inputs produce a possible/valid pour, false otherwise. 
*******************************************************************************************************************************************/
bool validatePour(int origin, int target, int target_cap){
	if(origin == 0) {
		return false;
	}
	else if(target_cap - target==0) {
		return false;
	}
	return true;
}

/*******************************************************************************************************************************************
 * This function utilizes a breadth-first search algorithm to obtain the optimal steps to solve the three water jug puzzle. 
 * Pre-Condtions: receives a State capacity - which stores the capacity of the jugs, and State goal - which stores the desired state.
 * Post-Condition: returns a formatted string containing the individual steps. 
*******************************************************************************************************************************************/
string bfs(State capacity, State goal) {

	
	bool **has_seen = new bool*[capacity.a + 1];	// Stores information on whether or not a given State has been seen already. 
	for(int i = 0; i < capacity.a + 1; i++){
			has_seen[i] = new bool[capacity.b + 1];
			fill(has_seen[i], has_seen[i] + capacity.b + 1, false); // Initialze each element to false. 
	}

	vector< shared_ptr <State> > q;
	q.push_back(make_shared<State> (0, 0, capacity.c, "Initial state.", nullptr));
	while( !q.empty() ) {
		shared_ptr<State> current = q.front();
		State cur = *current.get();
		q.erase( q.cbegin() );

		// If the goal state has been achieved. 
		if((cur.a == goal.a) && (cur.b == goal.b) && (cur.c == goal.c)) {
			string output = "";
			State s = cur;
			// Loop through the States, utilizing the parent pointer. 
			while(s.parent != nullptr){
				output = s.to_string() + "\n" + output;
				s = *(s.parent.get());
			}

			output = s.to_string() + "\n" + output;
			q.clear();

			for(int i = 0; i < capacity.a + 1; i++) {
				delete has_seen[i];
			}

			delete has_seen;
			return output;
		}
		// If the current State has been seen, skip the pour attempts. 
		if(has_seen[cur.a][cur.b]) {
			continue;
		}
		has_seen[cur.a][cur.b] = true;

		// Start of Pour Attempts
		
		//Pour from C to A
		if(validatePour(cur.c, cur.a, capacity.a)){
			if((capacity.a - cur.a) == 1 || cur.c == 1){
				if((capacity.a - cur.a) < cur.c) {
					q.push_back(make_shared<State>(capacity.a, cur.b, (cur.c - (capacity.a - cur.a)), "Pour " + to_string(capacity.a - cur.a) + " gallon from C to A.", current));
				} else {
					q.push_back(make_shared<State>((cur.a + cur.c), cur.b, 0, "Pour " + to_string(cur.c) + " gallon from C to A.", current));
				}
			} else { 
				if((capacity.a-cur.a) < cur.c){
					q.push_back(make_shared<State> (capacity.a, cur.b, (cur.c - (capacity.a - cur.a)), "Pour " + to_string(capacity.a - cur.a) + " gallons from C to A.", current));
				} else {
					q.push_back(make_shared<State>((cur.a + cur.c), cur.b, 0, "Pour " + to_string(cur.c) + " gallons from C to A.", current));
				}
			}
		}
		//Pour from B to A
		if(validatePour(cur.b, cur.a, capacity.a)) {
			if((capacity.a - cur.a) == 1 || cur.b == 1) {
				if((capacity.a - cur.a) < cur.b){
					q.push_back(make_shared<State>(capacity.a, (cur.b - (capacity.a - cur.a)), cur.c , "Pour " + to_string(capacity.a - cur.a) + " gallon from B to A.", current));
				} else {
					q.push_back(make_shared<State>((cur.a + cur.b), 0, cur.c, "Pour " + to_string(cur.b) + " gallon from B to A.", current));
				}
			} else {
				if((capacity.a-cur.a) < cur.b){
					q.push_back(make_shared<State>(capacity.a, (cur.b - (capacity.a - cur.a)), cur.c , "Pour " + to_string(capacity.a - cur.a) + " gallons from B to A.", current));
				} else {
					q.push_back(make_shared<State>((cur.a + cur.b), 0, cur.c, "Pour " + to_string(cur.b) + " gallons from B to A.", current));
				}
			}
		}
		//Pour from C to B
		if(validatePour(cur.c, cur.b, capacity.b)) {
			if((capacity.b-cur.b) == 1 || cur.c == 1){
				if((capacity.b - cur.b) < cur.c){
					q.push_back(make_shared<State>(cur.a, capacity.b, (cur.c - (capacity.b-cur.b)) , "Pour " + to_string(capacity.b - cur.b) + " gallon from C to B.", current));
				} else {
					q.push_back(make_shared<State>(cur.a, (cur.b + cur.c), 0, "Pour " + to_string(cur.c) + " gallon from C to B.", current));
				}
			} else {
				if((capacity.b-cur.b) < cur.c) {
					q.push_back(make_shared<State>(cur.a, capacity.b, (cur.c - (capacity.b - cur.b)) , "Pour " + to_string(capacity.b - cur.b) + " gallons from C to B.", current));
				} else {
					q.push_back(make_shared<State>(cur.a, (cur.b + cur.c), 0, "Pour " + to_string(cur.c) + " gallons from C to B.", current));
				}
			}
		}
		//Pour from A to B
		if(validatePour(cur.a, cur.b, capacity.b)){
			if((capacity.b-cur.b) == 1 || cur.a == 1){
				if((capacity.b-cur.b)<cur.a){
					q.push_back(make_shared<State>((cur.a - (capacity.b - cur.b)), capacity.b, cur.c , "Pour " + to_string(capacity.b - cur.b) + " gallon from A to B.", current));
				} else {
					q.push_back(make_shared<State>(0, (cur.b + cur.a), cur.c, "Pour " + to_string(cur.a) + " gallon from A to B.", current));
				}
			} else { 
				if((capacity.b - cur.b)<cur.a){
					q.push_back(make_shared<State>((cur.a - (capacity.b - cur.b)), capacity.b, cur.c , "Pour " + to_string(capacity.b - cur.b) + " gallons from A to B.", current));
				} else {
					q.push_back(make_shared<State>(0, (cur.b + cur.a), cur.c, "Pour " + to_string(cur.a) + " gallons from A to B.", current));
				}
			}
		}
		//Pour from B to C
		if(validatePour(cur.b, cur.c, capacity.c)){
			if((capacity.c - cur.c) == 1 || cur.b == 1){
				if((capacity.c - cur.c) < cur.b){
					q.push_back(make_shared<State>(cur.a, (cur.b - (capacity.c-cur.c)), capacity.c , "Pour " + to_string(capacity.c - cur.c) + " gallon from B to C.", current));
				} else {
					q.push_back(make_shared<State>(cur.a, 0, cur.c + cur.b, "Pour " + to_string(cur.b) + " gallon from B to C.", current));
				}
			} else {
				if((capacity.c - cur.c) < cur.b){
					q.push_back(make_shared<State>(cur.a, (cur.b - (capacity.c - cur.c)), capacity.c , "Pour " + to_string(capacity.c - cur.c) + " gallons from B to C.", current));
				} else {
					q.push_back(make_shared<State>(cur.a, 0, cur.c + cur.b, "Pour " + to_string(cur.b) + " gallons from B to C.", current));
				}
			}
		}
		//Pour from A to C
		if(validatePour(cur.a, cur.c, capacity.c)){
			if((capacity.c - cur.c) == 1 || cur.a == 1){
				if((capacity.c - cur.c) < cur.a){
					q.push_back(make_shared<State>((cur.a - (capacity.c - cur.c)), cur.b, capacity.c , "Pour " + to_string(capacity.c - cur.c) + " gallon from A to C.", current));
				} else {
					q.push_back(make_shared<State>(0, cur.b, (cur.c + cur.a), "Pour " + to_string(cur.a) + " gallon from A to C.", current));
				}
			} else {
				if((capacity.c - cur.c) < cur.a){
					q.push_back(make_shared<State>((cur.a - (capacity.c - cur.c)), cur.b, capacity.c , "Pour " + to_string(capacity.c - cur.c) + " gallons from A to C.", current));
				} else {
					q.push_back(make_shared<State>(0, cur.b, (cur.c + cur.a), "Pour " + to_string(cur.a) + " gallons from A to C.", current));
				}
			}
		}
		// End of Pour Attempts

	}

	// Memory release
	q.clear();
	for(int i= 0; i < capacity.a + 1; i++){
		delete has_seen[i];
	}
	delete has_seen;
	return "No solution.";
}

int main(int argc, char *argv[]) {

	// If the input is invalid, exit the program with error code 1. Error output is done in validateInput
	if (!validateInput(argc, argv)) {
		return 1;
	}
	int int_args[6];
	for(int i = 1; i < 7; i++){
		istringstream iss(argv[i]);
		iss >> int_args[i - 1];
	}
	State capacity(int_args[0], int_args[1], int_args[2], "Capacity state.", nullptr);
	State goal(int_args[3], int_args[4], int_args[5], "Goal state.", nullptr);
	cout << bfs(capacity, goal) << endl;
	return 0;
}
