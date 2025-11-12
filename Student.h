#include <string>
using namespace std;
class Student {
private:
  int SAP;
  string name;
  string course;

  int semester;

public:
  Student() {}
  Student(int SAP, string name, string course, int semester) {
    this->SAP = SAP;
    this->semester = semester;
    this->name = name;
    this->course = course;
  }

  // destructor
  ~Student() {}

  // getters
  int getSap() { return SAP; }
  string getName() { return name; }
  int getSemester() { return semester; }
  string getCourse() { return course; }

  // setters
  void setSAP(int SAP) { this->SAP = SAP; }
  void setName(string name) { this->name = name; }
  void setSemester(int semester) { this->semester = semester; }
  void setCourse(string course) { this->course = course; }
};