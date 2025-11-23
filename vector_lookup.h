#include "Student.h"
#include "Subject.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T> bool exists(std::vector<T> &array) {
  return !array.empty();
}

Student findStudent(std::vector<Student> students, int sap) {
  int size = students.size();
  // loop over the array
  for (Student s : students) {
    if (s.getSap() == sap) {
      return s;
    }
  }
}

Student findStudent(std::vector<Student> students, std::string name) {
  int size = students.size();
  // loop over the array
  for (Student s : students) {
    if (s.getName() == name) {
      return s;
    }
  }
}

Subject findSubject(std::vector<Subject> subjects, std::string name) {
  int size = subjects.size();
  // loop over the array
  for (Subject s : subjects) {
    if (s.getName() == name) {
      return s;
    }
  }
}

Subject findSubject(std::vector<Subject> subjects, string code) {
  int size = subjects.size();
  // loop over the array
  for (Subject s : subjects) {
    if (s.getCode() == code) {
      return s;
    }
  }
}

