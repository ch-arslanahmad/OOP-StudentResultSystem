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

  map<string, int> weightage = {{"assignment", 10},
                                {"quiz", 10},
                                {"labs", 10},
                                {"midterm", 30},
                                {"finalterm", 40}};

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
  set<int> saps;

  // ... so set is of string, 70177071,oop,assignment_total/obtained
  // set<string> component_total_grades;
  //* [key, value[key,value[key,pair(float,float)]]]
  map<int, map<string, map<string, pair<float, float>>>> grades;

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

    int iSap = convert.toInt(str_sap);
    students[iSap] = str_name;
    saps.insert(iSap);
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

      int sap = convert.toInt(str_sap);
      // map[sap][subject][component] = pair(total, obtained)
      grades[sap][str_subject][component].first += total;
      grades[sap][str_subject][component]
          .second += obtained;
    }
  }

  // sap, subject, (total, obtained)
  map<int, map<string, pair<float, float>>> subject_grades;
  for (int sap : saps)
  {
    for (auto &subject : subjects)
    {
      for (auto &component : weightage)
      {
        // this gives us the n% of weigtage of components;
        grades[sap][subject.first][component.first].first *= (component.second / 100.0);  // total
        grades[sap][subject.first][component.first].second *= (component.second / 100.0); // obtained
        float total = grades[sap][subject.first][component.first].first;
        float obtained = grades[sap][subject.first][component.first].second;
        subject_grades[sap][subject.first] = pair(total, obtained);
      }
    }
  }

  for (int sap : saps)
  {
    for (auto &subject : subjects)
    {
      cout << "Sap: " << sap << "\t";
      cout << "Subject: " << subject.first << endl;
      pair<float, float> marks = subject_grades[sap][subject.first];
      cout << "Total: " << marks.first << "\nObtained: " << marks.second << endl;
    }
  }

  // find total marks of each subject for each student

  return 0;
}
