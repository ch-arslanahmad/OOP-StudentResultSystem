#include "Converter.h"

#include <fstream>

#include <iostream>

#include <regex> // for pattern

#include <set>   // for sets

#include <sstream>

#include <vector>

using namespace std;
// read from a file and make sets
void getvariablesfromString(string line) {
	string str_sap, str_name, str_semester, str_subject, str_subject_code,
	str_credit_hours, str_components, str_total, str_obtained;
	istringstream iss;
	getline(iss, str_sap, ',');
	getline(iss, str_name, ',');
	getline(iss, str_semester, ',');
	getline(iss, str_subject, ',');
	getline(iss, str_subject_code, ',');
	getline(iss, str_credit_hours, ',');
	getline(iss, str_components, ',');
	getline(iss, str_total, ',');
	getline(iss, str_obtained, ',');
}
int main() {
	Converter convert;
	ifstream rf("data/data.txt");
	string line;

    string component_pattern[3] = {
        "assignment_*",
        "quiz_*",
        "labs_*"}; // for pattern
    regex r(component_pattern[0]);
	regex q(component_pattern[1]);
	regex s(component_pattern[2]);
	set < string > lines;
	while(getline(rf, line)) {
		lines.insert(line);
	}
	int total_assignment_marks = 0, total_labs_marks = 0, total_quiz_marks = 0,
		total_mid_marks = 0, total_final_marks = 0;
	int assignment_marks = 0, labs_marks = 0, quiz_marks = 0, mid_marks,
		final_marks; // obtained;
	string grade;
	double grade_points; // total grade point earned
	/*
	Credit Hours  Percentage    Grade
	    3           85-100       A
	    3           75-84        B
	    3           65-74        C
	    3           55-64        D
	    3           50-54        E
	    3           <50          F
	*/
	//---TOTALS---
	int total_marks_obtained = 0;
	int total_marks = 0;
	int total_credit_hours = 0;
	double totalendpoints = 0.0; // sum of all grade points earned
	for(string line: lines) {
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
		double sap = convert.toDouble(str_sap);
		double semester = convert.toDouble(str_semester);
		double credit_hours = convert.toDouble(str_credit_hours);
		double total = convert.toDouble(str_total);
		double obtained = convert.toDouble(str_obtained);
		int i = 0;
		if(regex_match(str_components, r)) // for assignment
		{
			cout << "this is a component";
			total_assignment_marks += total;
			assignment_marks += obtained;
		}
		if(regex_match(str_components, r)) // for quiz
		{
			cout << "this is a component";
			total_quiz_marks += total;
			quiz_marks += obtained;
		}
		if(regex_match(str_components, s)) // for lab
		{
			cout << "this is a component";
			total_labs_marks += total;
			labs_marks += obtained;
		}
		if(str_components == "midterm_1") {
			total_mid_marks += total;
			mid_marks = obtained;
		}
		if(str_components == "finalterm_1") {
			total_final_marks += total;
			final_marks = obtained;
		}
		total_marks = total_assignment_marks + total_labs_marks + total_quiz_marks + total_mid_marks + total_final_marks;
		total_marks_obtained = assignment_marks + labs_marks + quiz_marks + mid_marks + final_marks;
		double percentage = (double(total_marks_obtained) / double(total_marks)) * 100.0;
		if(percentage >= 85 && percentage <= 100) {
			grade_points = 4.0 * credit_hours;
			grade = "A";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 80 && percentage < 85) {
			grade_points = 3.75 * credit_hours;
			grade = "A-";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 75 && percentage < 80) {
			grade_points = 3.5 * credit_hours;
			grade = "B+";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 70 && percentage < 75) {
			grade_points = 3.0 * credit_hours;
			grade = "B";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 65 && percentage < 70) {
			grade_points = 2.5 * credit_hours;
			grade = "C+";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 60 && percentage < 65) {
			grade_points = 2.0 * credit_hours;
			grade = "C-";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 55 && percentage < 60) {
			grade_points = 1.5 * credit_hours;
			grade = "D+";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 50 && percentage < 55) {
			grade_points = 1.0 * credit_hours;
			grade = "D";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}
		if(percentage >= 0 && percentage < 50) {
			grade_points = 0.0 * credit_hours;
			grade = "F";
			total_credit_hours += credit_hours;
			totalendpoints = totalendpoints + grade_points;
		}

    double GPA = totalendpoints / total_credit_hours;
    cout << "Student SAP: " << str_sap << endl;
    cout << "Student Name: " << str_name << endl;
    cout << "Semester: " << str_semester << endl;
    cout << "Subject: " << str_subject << endl;
    cout << "Subject Code: " << str_subject_code << endl;
    cout << "Credit Hours: " << str_credit_hours << endl;
    cout << "Total Marks: " << total_marks << endl;
    cout << "Obtained Marks: " << total_marks_obtained << endl;
    cout << "Percentage: " << percentage << "%" << endl;
    cout << "Grade: " << grade << endl;
    cout << "Grade Points: " << grade_points << endl;
    cout << "GPA: " << GPA << endl;
	}
}