// ... this file is supposed to create one file which will hold the dummy data

#include<iostream>
#include<fstream> // for file handling
#include<string>
#include<vector> // for resizable arrays
using namespace std;


void createTotalComponents(const string components[], int components_max[], int size, vector<string> &component_arrays) {

    for (int i = 0; i < size; i++) 
    {
        for (int o = 1; o <= components_max[i] ; o++)
            component_arrays.push_back(components[i] + "_" + to_string(o));
    }
}


int main() {

    // std::ios::app -  append in file not overwrite 
    ofstream wf("data/data.txt");

    string subjects[5] = {"oop", "embedded-sytems", "data-communications", "operating-systems", "applied-maths-ii"};
    string subject_code[5] = {"CS011", "EM022", "DC33", "CS044", "MA055"};
    int subject_credit_hours[5] = {4, 3, 4, 3, 3};
    string components[5] = {"assignment", "quiz", "midterm", "finalterm", "labs"};
    int components_max[5] = {4,4,1,1,16};

// test#2 complete - CREATING all COMPONENENTS of a subject
        vector<string> all_components;
        createTotalComponents(components, components_max, 5, all_components);
        for(string a : all_components) {
            cout << a << endl;
        }
// test#1 - write basic info in a file 
        int o = 0, p = 0; // for array count - 4


        // suppose there are 50 students

        // todo: correct this loop, even though enough for testing
for (int i = 1; i <= 50; i++) {
    if(o > 4) o = 0;
    if (p >= all_components.size())
        p = 0;
    wf << "7017707" << i << "," << "Name" << i << "," << "Fall-2025" << "," << subjects[o] << "," << subject_credit_hours[o] << "," << subject_code[o] << "," << all_components[o] << "\n";
    o++;
    p++;
}
}