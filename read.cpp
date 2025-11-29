#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <regex>
#include <vector>
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

  string component_pattern[5] = {
      "assignment_\\d+",
      "quiz_\\d+",
      "labs_\\d+", "midterm_\\d+", "finalterm_\\d+"}; // for pattern
  regex as(component_pattern[0]);
  regex quiz(component_pattern[1]);
  regex labs(component_pattern[2]);
  regex mid(component_pattern[3]);
  regex fin(component_pattern[4]);

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

    if (regex_match(str_components, as) || regex_match(str_components, quiz) || regex_match(str_components, labs) || regex_match(str_components, mid) || regex_match(str_components, fin))
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

  // MAX CREDIT HOURS
  int totalcredit = 0;
  for (auto &subject : subjects)
  {
    totalcredit += subject.second;
  }

  // print component with total/obtained grades

  for (auto &grade : grades)
  {
    int sap = grade.first;
    for (auto &subject : grade.second)
    {
      string subject_name = subject.first;
      for (auto &component : subject.second)
      {
        string component_name = component.first;
        pair<float, float> marks = component.second;
      }
    }
  }

  // sap, subject, (marks)
  map<int, map<string, float>> subject_grades;
  for (int sap : saps)
  {
    for (auto &subject : subjects)
    {
      for (auto &component : weightage)
      {
        // this gives us the n% of weigtage of components
        float total = grades[sap][subject.first][component.first].first;
        float obtained = grades[sap][subject.first][component.first].second;
        // as some total would have 0 total marks in the start so to avoid
        if (total == 0)
        {
          continue;
        }
        subject_grades[sap][subject.first] += (obtained / total) * component.second; // accumulate total and obtained marks;
      }
    }
  }

  map<int, map<string, float>> final_subject_scores;

  // sap, grade-point = endpoints
  map<int, float> endpoints;
  // sap, total endpoints = totalendpoints
  map<int, float> totalendpoints;
  vector<string> grade;
  for (int sap : saps)
  {
    for (auto &subject : subjects)
    {
      float obtained = subject_grades[sap][subject.first];
      final_subject_scores[sap][subject.first] = obtained;
      //?subject.second is credit hours
      // condition 1
      if (obtained >= 85 && obtained <= 100)
      {
        endpoints[sap] = 4.0 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "A";
      }

      // condition 2
      if (obtained >= 80 && obtained < 85)
      {
        endpoints[sap] = 3.75 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "A-";
      }

      // condition 3
      if (obtained >= 75 && obtained < 80)
      {
        endpoints[sap] = 3.5 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "B+";
      }

      if (obtained >= 70 && obtained < 75)
      {
        endpoints[sap] = 3.0 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "B";
      }

      if (obtained >= 65 && obtained < 70)
      {
        endpoints[sap] = 2.50 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "C+";
      }
      if (obtained >= 60 && obtained < 65)
      {
        endpoints[sap] = 2.00 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "C-";
      }
      if (obtained >= 55 && obtained < 60)
      {
        endpoints[sap] = 1.50 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "D+";
      }
      if (obtained >= 50 && obtained < 55)
      {
        endpoints[sap] = 1.00 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "D";
      }
      if (obtained >= 0 && obtained < 50)
      {
        endpoints[sap] = 0.00 * subject.second;
        totalendpoints[sap] = totalendpoints[sap] + endpoints[sap];
        // grade = "F";
      }
    }

    const int MAX_GRADE = 100;

    for (auto sap : saps)
    {
      float gpa = totalendpoints[sap] / totalcredit;
      cout << "SAP: " << sap << ", Name: " << students[sap] << ", GPA: " << gpa << endl;
    }

    // find total marks of each subject for each student

    return 0;
  }
}