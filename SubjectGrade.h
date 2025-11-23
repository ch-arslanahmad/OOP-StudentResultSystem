#include <iostream>
using namespace std;
#include <string>
class SubjectGrade {
private:
  string course;
  int semester, SAP;
  string code, component;
  int index, total, obtained;

public:
  SubjectGrade() {}

  SubjectGrade(string course, int semester, int SAP, string code,
               string component, int index, int total, int obtained) {
    this->course = course;
    this->semester = semester;
    this->SAP = SAP;
    this->code = code;
    this->component = component;
    this->index = index;
    this->total = total;
    this->obtained = obtained;
  }
  // destructor
  ~SubjectGrade() {}
  // getters
  string getCourse() { return course; }
  int getSemester() { return semester; }
  int getSAP() { return SAP; }
  string getCode() { return code; }
  string getComponent() { return component; }
  int getIndex() { return index; }
  int getTotal() { return total; }
  int getObtained() { return obtained; }

  // setters
  void setCourse(string course) { this->course = course; }
  void setSemester(int semester) { this->semester = semester; }
  void setSAP(int SAP) { this->SAP = SAP; }
  void setCode(string code) { this->code = code; }
  void setComponent(string component) { this->component = component; }
  void setIndex(int index) { this->index = index; }
  void setTotal(int total) { this->total = total; }
  void setObtained(int obtained) { this->obtained = obtained; }
};