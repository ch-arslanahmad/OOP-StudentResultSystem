#include "Converter.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
  int sap;

  float total, obtained;
  float credit_hours;
  string name, semester, subject, subject_code, component;

  // constructor
  Student(int sap, string name, string semester, string subject,
          float credit_hours, string component, float total, float obtained) {
    this->sap = sap;
    this->name = name;
    this->semester = semester;
    this->subject = subject;
    this->credit_hours = credit_hours;
    this->component = component;
    this->total = total;
    this->obtained = obtained;
  }

  // student grades per subject
  Student(int sap, string subject, float total, float obtained) {
    this->sap = sap;
    this->subject = subject;
    this->total = total;
    this->obtained = obtained;
  }

  // student, with subject components
  Student(int sap, string subject, string components) {
    this->sap = sap;
    this->subject = subject;
    this->component = components;
  }

  // student with marks
  Student(int sap, float total, float obtained) {
    this->sap = sap;
    this->total = total;
    this->obtained = obtained;
  }

  // student with subject, components, and marks
  Student(int sap, string subject, string components, float total,
          float obtained) {
    this->sap = sap;
    this->subject = subject;
    this->component = components;
    this->total = total;
    this->obtained = obtained;
  }
};

Student extractStudent(string line) {
  Converter convert;
  string str_sap, str_name, str_semester, str_subject, str_subject_code,
      str_credit_hours, str_components, str_total, str_obtained;

  istringstream iss(line);
  getline(iss, str_sap, ',');
  getline(iss, str_name, ',');
  getline(iss, str_semester, ',');
  getline(iss, str_subject, ',');
  getline(iss, str_subject_code, ',');
  getline(iss, str_credit_hours, ',');
  getline(iss, str_components, ',');
  getline(iss, str_total, ',');
  getline(iss, str_obtained, ',');

  istringstream iss2(str_components);

  // string temp;
  getline(iss2, str_components, '_'); // to get component type

  return Student(convert.toInt(str_sap), str_name, str_semester, str_subject,
                 convert.toFloat(str_credit_hours), str_components,
                 convert.toFloat(str_total), convert.toFloat(str_obtained));
}

// std::string trim(std::string s) {
//   size_t start = s.find_first_not_of(" \t\n");
//   size_t end = s.find_last_not_of(" \t\n");

//   if (start == std::string::npos)
//     return "";

//   return s.substr(start, end - start + 1);
// }

set<string> getAllData() {
  ifstream rf("data/data.txt");
  string line;

  set<string> lines; // to store unique lines
  while (getline(rf, line)) {
    if (line.empty()) {
      continue; // skip empty lines
    }

    if (line[0] == '#') {
      continue; // skip comment lines
    }

    if (line[0] == '\n') {
      continue; // skip lines starting with space
    }
    lines.insert(line);
  }
  return lines;
}

Student getStudentGradesPerSubject(string line) {
  Converter convert;
  string str_sap, str_subject, str_total, str_obtained;

  istringstream iss(line);
  getline(iss, str_sap, ',');
  getline(iss, str_subject, ',');
  getline(iss, str_total, '_');
  getline(iss, str_obtained, ',');

  Student student =
      Student(convert.toInt(str_sap), str_subject, convert.toFloat(str_total),
              convert.toFloat(str_obtained));

  return student;
}

Student getStudentSubjectComponentGrades(string line) {
  Converter convert;
  string str_sap, str_subject, str_components, str_total, str_obtained;

  istringstream iss(line);
  getline(iss, str_sap, ',');
  getline(iss, str_subject, ',');
  getline(iss, str_components, ',');
  getline(iss, str_total, '_');
  getline(iss, str_obtained, ',');

  return Student(convert.toInt(str_sap), str_subject, str_components,
                 convert.toFloat(str_total), convert.toFloat(str_obtained));
}

Student getStudentwithSubjectComponent(string line) {
  Converter convert;
  string str_sap, str_subject, str_credit_hours, str_components;

  istringstream iss(line);
  getline(iss, str_sap, ',');
  getline(iss, str_subject, ',');
  getline(iss, str_components, ',');

  return Student(convert.toInt(str_sap), str_subject, str_components);
}

Student getStudentMarks(string line) {
  Converter convert;
  string str_sap, str_total, str_obtained;

  istringstream iss(line);
  getline(iss, str_sap, ',');
  getline(iss, str_total, '_');
  getline(iss, str_obtained, ',');

  return Student(convert.toInt(str_sap), convert.toFloat(str_total),
                 convert.toFloat(str_obtained));
}

bool regex_compare(const string &component) {
  // Define the regex pattern to match valid component types
  const regex pattern(
      "^(assignment|quiz|labs|midterm|finalterm)(_total|_obtained)?$");

  // Perform the regex match
  return regex_match(component, pattern);
}

void printSet(const set<string> &s) {
  for (const auto &item : s) {
    cout << item << endl;
  }
}

void removeUselessKeys(set<string> &keys_with_grades, float weightage[],
                       string components[], int size, Converter convert) {
  set<string> keys_to_remove;

  // For each entry, check if there's another entry with same
  // sap_subject_component but higher total
  for (const auto &key_with_grades : keys_with_grades) {

    // Extract the main part and the totals
    Student student = getStudentSubjectComponentGrades(key_with_grades);

    string sap_subject_component = to_string(student.sap) + "_" +
                                   student.subject + "_" + student.component;

    float total = student.total;

    /* Remove entries with lower totals (keep only max)
    70177071,applied-maths-ii,assignment,10_2  <- remove
    70177071_applied-maths-ii_assignment_20_10 <- remove
    70177071_applied-maths-ii_assignment_30_17 <- remove
    70177071_applied-maths-ii_assignment_40_21 <- keep (max) */

    // Check if there's a higher total for the same sap_subject_component
    for (const auto &other_key : keys_with_grades) {

      Student other = getStudentSubjectComponentGrades(other_key);

      float other_total = other.total;

      string other_sap_subject_component =
          to_string(other.sap) + "_" + other.subject + "_" + other.component;

      // If same component but higher total exists, mark current for removal
      if (sap_subject_component == other_sap_subject_component &&
          total < other_total) {
        keys_to_remove.insert(key_with_grades);
        break;
      }
    }

    // Validate component using regex (use parsed component directly)
    if (!regex_compare(student.component)) {
      keys_to_remove.insert(key_with_grades);
      continue;
    }
  }
  // Remove invalid keys
  for (const auto &key : keys_to_remove) {
    keys_with_grades.erase(key);
  }
}

set<string> getComponentGradePerWeightage(set<string> keys_with_grades,
                                          float weightage[],
                                          string components[], int size,
                                          Converter convert) {

  set<string> component_grades;

  // For each student and subject, calculate final grade
  for (const auto keys : keys_with_grades) {

    Student student = getStudentSubjectComponentGrades(keys);

    float total = student.total;
    float obtained = student.obtained;

    float weighted_total = 0.0f;
    float weighted_obtained = 0.0f;

    for (int i = 0; i < size; i++) {
      if (student.component == components[i]) {

        if (student.component == "labs") {
          total = total / 16; // since 16 labs
          obtained = obtained / 16;
        } else if (student.component == "quiz") {
          total = total / 4; // since 4 quizzes
          obtained = obtained / 4;
        } else if (student.component == "assignment") {
          total = total / 4; // since 4 assignments
          obtained = obtained / 4;
        }

        weighted_total = weightage[i];
        weighted_obtained = (obtained / total) * weightage[i];
      }
    }

    string temp_new_keys = to_string(student.sap) + "," + student.subject +
                           "," + student.component + "," +
                           to_string(weighted_total) + "_" +
                           to_string(weighted_obtained);
    component_grades.insert(temp_new_keys);
  }
  return component_grades;
}

// THIS function will recieve data in the followign format,

/*
70177071,applied-maths-ii,assignment,10.000000_5.250000
70177071,applied-maths-ii,finalterm,40.000000_39.000000
70177071,applied-maths-ii,labs,10.000000_4.250000
70177071,applied-maths-ii,midterm,30.000000_28.000000
70177071,applied-maths-ii,quiz,10.000000_5.750000
*/
set<string> getGradesPerSubjectPerStudent(set<string> component_grades,
                                          const set<int> &saps,
                                          const set<string> &subjects,
                                          Converter convert) {

  set<string> subject_grades;

  // Temporary container to store processed SAP+SUBJECT combinations
  set<string> processed;

  for (const auto &grade : component_grades) {

    Student student = getStudentSubjectComponentGrades(grade);

    // Skip if not in given saps/subjects
    if (!saps.count(student.sap) || !subjects.count(student.subject))
      continue;

    string sap_subject = to_string(student.sap) + "," + student.subject;

    // Skip if we've already processed this student+subject
    if (processed.count(sap_subject))
      continue;

    float total_sum = 0.0f;
    float obtained_sum = 0.0f;

    // Sum all components for this student+subject
    for (const auto &other_grade : component_grades) {
      Student other = getStudentSubjectComponentGrades(other_grade);
      if (other.sap == student.sap && other.subject == student.subject) {
        total_sum += other.total;
        obtained_sum += other.obtained;
      }
    }

    // Insert aggregated grade into the result set
    string final_grade = to_string(student.sap) + "," + student.subject + "," +
                         to_string(total_sum) + "_" + to_string(obtained_sum);
    subject_grades.insert(final_grade);

    // Mark this student+subject as processed
    processed.insert(sap_subject);
  }
  return subject_grades;
}

// THIS function will recieve data in the following format,
/*
70177071_applied-maths-ii_130.00_85.50
70177071_applied-physics-ii_100.00_75.00
*/
set<string> getGradePerStudent(set<string> subject_grades) {

  set<string> students_grades;
  set<int> processed; // to track processed SAPs
  for (const auto &student_grade : subject_grades) {

    Student student = getStudentGradesPerSubject(student_grade);

    // Skip if already processed this student
    if (processed.count(student.sap))
      continue;

    float total_sum = 0.0f;
    float obtained_sum = 0.0f;

    // Sum all components for this student+subject
    for (const auto &other_grade : subject_grades) {
      Student other = getStudentGradesPerSubject(other_grade);
      if (other.sap == student.sap) { // sum per student
        total_sum += other.total;
        obtained_sum += other.obtained;
      }

      string student_grades_str = to_string(student.sap) + "," +
                                  to_string(total_sum) + "_" +
                                  to_string(obtained_sum);

      students_grades.insert(student_grades_str);
      processed.insert(student.sap);
    }
  }
  return students_grades;
}

int main() {
  string components[5] = {"assignment", "quiz", "labs", "midterm",
                          "finalterm"}; // for pattern

  float weightage[5] = {10.0f, 10.0f, 10.0f, 30.0f, 40.0f};
  Converter convert;

  ifstream rf("data/data.txt");

  string line;

  set<string> subjects;

  set<string> last_iteration;
  set<int> saps;
  // ... so set is of string, 70177071,oop,assignment_total/obtained

  int temp_total = 0;
  int temp_obtained = 0;

  set<string> lines = getAllData(); // GET ALL DATA FROM FILE

  set<string> keys; // holds keys
  set<string> keys_with_grades;
  for (string line : lines) {

    last_iteration.insert(line); // inserting to test

    Student student = extractStudent(line);

    saps.insert(student.sap);

    subjects.insert(student.subject);

    // get total and obtained marks
    int total = student.total;
    int obtained = student.obtained;

    string key = to_string(student.sap) + "," + student.subject + "," +
                 student.component;

    if (keys.find(key) == keys.end()) {
      // new key, reset totals
      temp_total = total;
      temp_obtained = obtained;
      keys.insert(key);
    } else {
      // key exists, aggregate totals
      temp_total += total;
      temp_obtained += obtained;
    }

    string key_with_grades =
        key + "," + to_string(temp_total) + "_" + to_string(temp_obtained);
    keys_with_grades.insert(key_with_grades);
  }

  removeUselessKeys(keys_with_grades, weightage, components, 5, convert);

  // now after this we have output in the following format
  /*
  70177071,applied-maths-ii,assignment,40_21
70177071,applied-maths-ii,finalterm,40_39
70177071,applied-maths-ii,labs,160_68
70177071,applied-maths-ii,midterm,30_28
70177071,applied-maths-ii,quiz,40_23
  */

  // Next step is to calculate final grades per subject per student

  set<string> component_grades = getComponentGradePerWeightage(
      keys_with_grades, weightage, components, 5, convert);

  set<string> subject_grades =
      getGradesPerSubjectPerStudent(component_grades, saps, subjects, convert);


  set<string> students_marks = getGradePerStudent(subject_grades);
  printSet(students_marks);

  return 0;
}
