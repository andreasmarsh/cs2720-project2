// Student class member and friend function definition
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

#include "Student.h" // Student class definition
using namespace std;

int id;
string name;

// constructor for class Student
Student::Student(int studentIDz, string studentNamez) {
    id = studentIDz;
    name = studentNamez;
}

// constructor for class Student
Student::Student(int studentIDz) {
    id = studentIDz;
    name = " ";
}

// constructor for class Student
Student::Student(string studentNamez) {
    id = 0;
    name = studentNamez;
}

// constructor for class Student
Student::Student() {
    id = 0;
    name = " ";
}

// returns studentID
const int Student::getStudentID() const {
    return id;
}

// returns studentName
const string Student::getStudentName() const {
    return name;
}

// sets studentID
void setStudentID(int studentIDz) {
    id = studentIDz;
}

// sets studentID
void setStudentName(int studentNamez) {
    name = studentNamez;
}

// sees if two Students have same studentIDs
bool Student::equals(const Student &s) const {
    if (getStudentID() == s.getStudentID()) {
        return true;
    } else {
        return false;
    }
}

// sees if Student calling has smaller ID
bool Student::lesser(const Student &s) const {
    if (getStudentID() < s.getStudentID()) {
        return true;
    } else {
        return false;
    }
}

// sees if Student calling has larger ID
bool Student::greater(const Student &s) const {
    if (getStudentID() > s.getStudentID()) {
        return true;
    } else {
        return false;
    }
}

// overide of == operator
bool Student::operator==(const Student& s) const {
    bool temp = this->equals(s);
    return temp;
}

// overide of != operator
bool Student::operator!=(const Student& s) const {
    bool temp = !(this->equals(s));
    return temp;
}

// overide of < operator
bool Student::operator<(const Student& s) const {
    bool temp = this->lesser(s);
    return temp;
}

// overide of > operator
bool Student::operator>(const Student& s) const {
    bool temp = this->greater(s);
    return temp;
}

/*ostream& operator<<(ostream& out, const Student&) {
  out << getStudentID() << " " << getStudentName();
  return out;
  } */
