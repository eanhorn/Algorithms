/*********************************************************************************
 *Name       : student.cpp
 *Author     : Erik Anhorn
 *Version    : 1.0
 *Date       : September 9, 2021
 *Pledge     : I pledge my honor that I have abided by the Stevens Honor System.
 *********************************************************************************/
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

using namespace std;
class Student{
public:
	Student(string first, string last, float gpa, int id) : gpa_{gpa}, id_{id} {
		//I tried to include the name strings in the initializer list but I could
		//not get it to work and I cannot remember if it is even possible to put
		//strings in the initializer list so I initialized them in the body.
		first_ = first;
		last_ = last;
	}
	string full_name() const{
		string full_name = first_ + " " + last_;
		return full_name;
	}
	int id() const {
		return id_;
	}
	float gpa() const {
		return gpa_;
	}
	void print_info() const {
		cout << first_ << " " << last_ << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: " << id_ <<endl;
	}
private:
	string first_, last_;
	float gpa_;
	int id_;
};

vector<Student> find_failing_students(const vector<Student> &students){
	vector<Student> failing_students;
	for(const auto &student : students){
		if(student.gpa()<1.0)
			failing_students.push_back(student);
	}
	return failing_students;
}
void print_students(const vector<Student> &students){
	for(const auto &student : students){
		student.print_info();
	}
}
int main(){
	string first_name, last_name;
	float gpa;
	int id;
	char repeat;
	vector<Student> students;
	do{
		cout << "Enter student's first name: ";
		cin >> first_name;
		cout << "Enter student's last name: ";
		cin >> last_name;
		gpa = -1;
		while(gpa < 0 || gpa > 4){
			cout << "Enter student's GPA (0.0-4.0): ";
			cin >> gpa;
		}
		cout << "Enter student's ID: ";
		cin >> id;
		students.push_back(Student(first_name, last_name, gpa, id));
		cout << "Add another student to database (Y/N)? ";
		cin >> repeat;
	}while(repeat == 'y' || repeat == 'Y');
	cout << endl << "All students:" << endl;
	print_students(students);
	cout << endl << "Failing students:";
	vector<Student> failing_students = find_failing_students(students);
	if(failing_students.size()==0){
		cout << " None" << endl;
	}
	else{
		cout << endl;
		print_students(failing_students);
	}
	return 0;
}
