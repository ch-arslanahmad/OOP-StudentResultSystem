#include "Student.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

std::fstream openFile(string filename) {
  fstream file(filename, ios::in | ios::out); // opening file for read/write
  return file;
}

void createFile(string filename) { fstream create(filename); }

int main() {
  ifstream rf("data/students.txt");

  string line;
  string sap, semester, name, course;

  cout << "The file is working" << endl;

  int i = 0;
  int count = 0;

  // read student.txt
  while (getline(rf, line)) {
    if (i < 2) {
      i++;
      continue;
    }
    istringstream iss(line);
    getline(iss, sap, ',');
    getline(iss, name, ',');
        getline(iss, semester, ',');
    count++;

    cout << "Sap: " << sap << endl;
    cout << "Name: " << name << endl;
    cout << "Semester: " << semester << endl;
  }
  int SAP;
  cout << endl << "Total Students: " << count << endl;

  rf.close();
  return 0;
}
