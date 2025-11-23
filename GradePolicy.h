#include <iostream>
#include <string>
using namespace std;
class GradePolicy {
private:
  string course;
  int semester;
  string name;
  int quantity;
  double weightage;
  bool hasLab;

public:
  GradePolicy() {}
  GradePolicy(string course, int semester, string name, int quantity,
              double weightage, bool hasLab) {
    this->course = course;
    this->semester = semester;
    this->name = name;
    this->quantity = quantity;
    this->weightage = weightage;
    this->hasLab= hasLab;
  }

  // Getters
  string getCourse() { return course; }
  int getSemester() { return semester; }
  string getName() { return name; }
  int getQuantity() { return quantity; }
  double getWeightage() { return weightage; }
  bool getHasLab() { return hasLab; }

  // Setters
  void setCourse(string course) { this->course = course; }
  void setSemester(int semester) { this->semester = semester; }
  void setName(string name) { this->name = name; }
  void setQuantity(int quantity) { this->quantity = quantity; }
  void setWeightage(double weightage) { this->weightage = weightage; }
  void setHasLab(bool hasLab) { this->hasLab = hasLab; }
};