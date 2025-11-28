#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <regex>
#include "Converter.h"
using namespace std;
int main()
{

  Converter convert;

  string component_pattern[3] = {
      "assignment_\\d+",
      "quiz_\\d+",
      "labs_\\d+"}; // for pattern
  regex r(component_pattern[0]);
  regex q(component_pattern[1]);
  regex s(component_pattern[2]);

  ifstream rf("data/data.txt");
  string line;

  set<string> lines; // to store unique lines
  while (getline(rf, line))
  {
    if (line.empty())
    {
      continue; // skip empty lines
    }

    if (line[0] == '#')
    {
      continue; // skip comment lines
    }

    if (line[0] == '\n')
    {
      continue; // skip lines starting with space
    }
    lines.insert(line);
  }

  map<int, string> students;
  map<string, int> subjects;
  map<string, int> components;

  set<string> component_grades;
  for (string line : lines)
  {
    istringstream iss(line);
    string str_sap, str_name, str_semester, str_subject, str_subject_code,
        str_credit_hours, str_components, str_total, str_obtained;

    getline(iss, str_sap, ',');
    getline(iss, str_name, ',');
    getline(iss, str_semester, ',');
    getline(iss, str_subject, ',');
    getline(iss, str_subject_code, ',');
    getline(iss, str_credit_hours, ',');
    getline(iss, str_components, ',');
    getline(iss, str_total, ',');
    getline(iss, str_obtained, ',');

    students[convert.toInt(str_sap)] = str_name;
    subjects[str_subject] = convert.toInt(str_credit_hours); // store subject and its credit hours

    // get total and obtained marks
    int total = convert.toInt(str_total);
    int obtained = convert.toInt(str_obtained);

    if (regex_match(str_components, r) || regex_match(str_components, q) || regex_match(str_components, s))
    {
      string component;
      string str_component_no;

      istringstream iss2(str_components);

      getline(iss2, component, '_');
      getline(iss2, str_component_no);
      string temp = str_sap + "," + str_subject + "," + component + "_" + str_total + "/" + str_obtained;
      component_grades.insert(temp);
    }
  }

  set<string> component_total_grades;
  int count = 0;
  for (string line : component_grades)
  {

    istringstream iss(line);

    string str_sap, str_subjects, str_components, str_total, str_obtained;

    getline(iss, str_sap, ',');
    getline(iss, str_subjects, ',');
    getline(iss, str_components, '_');
    getline(iss, str_total, '/');
    getline(iss, str_obtained);

    if (regex_match(str_components, r))
      {
        count++;
        total += convert.toInt(str_total);
        obtained += convert.toInt(str_obtained);
        if(count >= 4) {
          count = 0;
        }
      }
  }

  return 0;
}