#include "Student.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  ifstream rfStudent("data/students.txt");
  cout << "\nReading Students File:\n";

  string line;
  string sap, semester, name, course;

  cout << "The file is working" << endl;

  int i = 0;
  int count = 0;

  // read student.txt
  while (getline(rfStudent, line)) {

    if (i < 2) {
      i++;
      continue;
    }
    istringstream iss(line);
    getline(iss, sap, ',');
    getline(iss, name, ',');
    getline(iss, course, ',');
    getline(iss, semester, ',');

    count++;

    cout << "Sap: " << sap << endl;
    cout << "Name: " << name << endl;
    cout << "Course: " << course << endl;
    cout << "Semester: " << semester << endl;
    cout << "------------------------" << endl;
  }
  int SAP;
  cout << endl << "Total Students: " << count << endl;

  // read SUBJECTS file
  ifstream rfSubject("data/subjects.txt");
  string lineSub;
  cout << "\nReading Subjects File:\n";
  while (getline(rfSubject, lineSub)) {
    if (lineSub[0] == '#' || lineSub[0] == '/') {
      continue; // skip comment lines
    }
    istringstream issSub(lineSub);
    string course, semester, code, name, creditHours, hasLab;

    getline(issSub, course, ',');
    getline(issSub, semester, ',');
    getline(issSub, code, ',');
    getline(issSub, name, ',');
    getline(issSub, creditHours, ',');
    getline(issSub, hasLab, ',');

    cout << "Course: " << course << endl;
    cout << "Semester: " << semester << endl;
    cout << "Code: " << code << endl;
    cout << "Name: " << name << endl;
    cout << "Credit Hours: " << creditHours << endl;
    cout << "Lab: " << hasLab << endl;

    cout << "------------------------" << endl;
  }

  return 0;
}
