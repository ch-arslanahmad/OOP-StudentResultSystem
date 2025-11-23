#include <string>
class Subject {
private:
  std::string course;
  int semester;
  std::string code, name;
  int credit_hours;
  bool hasLab;

public:
  Subject() {}

  Subject(std::string course, int semester, std::string code, std::string name,
          int credit_hours, bool hasLab) {
    this->course = course;
    this->semester = semester;
    this->code = code;
    this->name = name;
    this->credit_hours = credit_hours;
    this->hasLab = hasLab;
  }

  // destructor
  ~Subject() {}

  // setters
  void setCourse(int course) { this->course = course; }
  void setSemester(int semester) { this->semester = semester; }
  void setCode(std::string code) { this->code = code; }
  void setName(std::string name) { this->name = name; }
  void setCreditHours(int credit_hours) { this->credit_hours = credit_hours; }
  void setHasLab(bool hasLab) { this->hasLab = hasLab; }

  // getters
  std::string getCourse() { return course; }
  int getSemester() { return semester; }
  std::string getCode() { return code; }
  std::string getName() { return name; }
  int getCreditHours() { return credit_hours; }
  bool getHasLab() { return hasLab; }
};