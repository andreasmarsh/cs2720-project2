#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {

public:

    Student(int studentIDz, string studentNamez); // constructer
    Student(int studentIDz); // constructer
    Student(string studentNamez); // constructer
    Student(); // constructer

    const int getStudentID() const; // returns studentID
    const string getStudentName() const; // returns studentName

    bool equals(const Student & s) const; // see if the two Students have same IDs
    bool lesser(const Student & s) const; // see if the Student calling has smaller ID
    bool greater(const Student & s) const; // see if the Student calling has larger ID

    void setStudentID(int studentIDz); // sets studentID
    void setStudentName(string studentNamez); // sets studentName

    bool operator==(const Student &s) const;
    bool operator!=(const Student &s) const;
    bool operator<(const Student &s) const;
    bool operator>(const Student &s) const;


private:
    int id;
    string name;

    friend ostream& operator << (ostream& out, Student&);
    friend istream& operator >> (istream& in, Student&s);
};
#endif
