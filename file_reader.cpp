#include "Converter.h" // for conversion
#include "GradePolicy.h"
#include "Student.h"
#include "Subject.h"
#include "SubjectGrade.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector> // for list

using namespace std;

// a helper method to verify if file exists..
bool fileExists(string filename) {
  ifstream file(filename);
  if (file.is_open()) {
    return true;
  }
  return false;
}

// ... data/students.txt - FUNCTION
vector<Student> fetchStudentData(string filename) {
  ifstream rfStudent(filename); // open file for reading
  cout << "\nReading Students File:\n";

  string line;
  string sap, semester, name, course;

  cout << "The file is working" << endl;

  int i = 0;
  int count = 0;

  vector<Student> students; // declaring a list of students
  Converter convert;

  // read student.txt
  while (getline(rfStudent, line)) {

    if (line[0] == '#' || line[0] == '/') {
      continue; // skip comment lines
    }
    istringstream iss(line);
    getline(iss, sap, ',');
    getline(iss, name, ',');
    getline(iss, course, ',');
    getline(iss, semester, ',');
    // ... Student .  SAP, name, course, semester
    students.push_back(
        Student(convert.toInt(sap), name, course, convert.toInt(semester)));
  }

  return students;
}

vector<Subject> fetchSubjectData(string filename) {

  // read SUBJECTS file
  ifstream rfSubject(filename);
  string line;
  cout << "\nReading Subjects File:\n";

  vector<Subject> subjects; // declaring a list of subjects
  Converter convert;

  while (getline(rfSubject, line)) {
    if (line[0] == '#' || line[0] == '/') {
      continue; // skip comment lines
    }
    istringstream issSub(line);
    string course, semester, code, name, creditHours, hasLab;

    getline(issSub, course, ',');
    getline(issSub, semester, ',');
    getline(issSub, code, ',');
    getline(issSub, name, ',');
    getline(issSub, creditHours, ',');
    getline(issSub, hasLab, ',');
    // ... Subject .  course, semester, code, name, credit_hours, hasLab
    subjects.push_back(Subject(course, convert.toInt(semester), code, name,
                               convert.toInt(creditHours),
                               convert.toBool(hasLab)));
  }
  return subjects;
}

vector<SubjectGrade> readSubjectGrades(string filename) {

  if (fileExists(filename)) {
    cout << "\nFile Found: " << filename << endl;
  }

  vector<SubjectGrade> subjectGrades; // list of subject grades
  Converter convert;
  // read subject grades file
  ifstream rfSubjectGrades(filename);
  string line;
  cout << "\nReading Subject Grades File:\n";
  int count = 0;
  while (getline(rfSubjectGrades, line)) {
    if (line[0] == '#' || line[0] == '/' || line.empty()) {
      continue; // skip comment lines
    }
    string course, semester, sap, subjectCode, component, index, total,
        obtained;
    istringstream iss(line);
    getline(iss, course, ',');
    getline(iss, semester, ',');
    getline(iss, sap, ',');
    getline(iss, subjectCode, ',');
    getline(iss, component, ',');
    getline(iss, index, ',');
    getline(iss, total, ',');
    getline(iss, obtained, ',');

    // ... Course,Semester,SAP,SubjectCode,Component,Index,Total,Obtained

    subjectGrades.push_back(
        SubjectGrade(course, convert.toInt(semester), convert.toInt(sap),
                     subjectCode, component, convert.toInt(index),
                     convert.toInt(total), convert.toInt(obtained)));
    count++;
  }
  cout << "\nTotal Subject Grades Records Loaded: " << count << endl;
  return subjectGrades;
}

vector<GradePolicy> getGradePolicy(string filename) {

  ifstream rfGradePolicy(filename);
  Converter convert;
  string line;
  cout << "\nReading Grade Policy File:\n";
  vector<GradePolicy> gradePolicies;
  while (getline(rfGradePolicy, line)) {
    if (line[0] == '#' || line[0] == '/') {
      continue; // skip comment lines
    }
    // process grade policy line
    string course, semester, name, quantity, weightage, hasLab;

    istringstream iss(line);

    getline(iss, course, ',');
    getline(iss, semester, ',');
    getline(iss, name, ',');
    getline(iss, quantity, ',');
    getline(iss, weightage, ',');
    getline(iss, hasLab, ',');
    // ... GradePolicy .  course, semester, name, quantity, weightage,

    gradePolicies.push_back(GradePolicy(
        course, convert.toInt(semester), name, convert.toInt(quantity),
        convert.toDouble(weightage), convert.toBool(hasLab)));
  }
  return gradePolicies;
}

int main() {

  // Test#1
  /*
  vector<Student> students = fetchStudentData("data/students.txt");
  vector<Subject> subjects = fetchSubjectData("data/subjects.txt");

  if (!students.empty()) {
    cout << "\nStudents Data Loaded: " << students.size() << " records.\n";
  } else {
    cout << "\nNo Student Data Loaded.\n";
  }

  if (!subjects.empty()) {
    cout << "\nSubjects Data Loaded: " << subjects.size() << " records.\n";
  } else {
    cout << "\nNo Subject Data Loaded.\n";
  }

  */

  // Test#2 - Grade Policy & Grades
  // readSubjectGrades("data/sub-grades.txt");
  getGradePolicy("data/grade-policy.txt");
}
