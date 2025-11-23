#include <string>
class Student {
private:
  int SAP;
  std::string name, course;
  int semester;

public:
  Student() {}
  Student(int SAP, std::string name, std::string course, int semester) {
    this->SAP = SAP;
    this->semester = semester;
    this->name = name;
    this->course = course;
  }

  // destructor
  ~Student() {}

  // getters
  int getSap() { return SAP; }
  std::string getName() { return name; }
  int getSemester() { return semester; }
  std::string getCourse() { return course; }

  // setters
  void setSAP(int SAP) { this->SAP = SAP; }
  void setName(std::string name) { this->name = name; }
  void setSemester(int semester) { this->semester = semester; }
  void setCourse(std::string course) { this->course = course; }
};