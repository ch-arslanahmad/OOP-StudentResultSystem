// ... this file is supposed to create one file which will hold the dummy data

#include<iostream>
#include<fstream> // for file handling
#include<string>
#include<vector> // for resizable arrays
using namespace std;


// combines components name with component number
void createTotalComponents(const string components[], int components_max[], int size, vector<string> &component_arrays) {

    for (int i = 0; i < size; i++) 
    {
        for (int o = 1; o <= components_max[i] ; o++)
            component_arrays.push_back(components[i] + "_" + to_string(o));
    }
}


// combines no_of_components with teachers

// todo - correct this function
void combineComponentswithSubjects(string subjects[], string subject_code[], int credit_hours[], int size, vector<string> all_components, vector<string> &subject_with_components) {
    string line;
    for (int i = 0; i < size; i++)
    {
        // oop,CS00,4
        line  = subjects[i] + "," + subject_code[i] + "," + to_string(credit_hours[i]); // creates subject with its code, credit hours
        string combine;
        // oop,
        for (int o = 0; o < all_components.size(); o++) {
            combine = line + "," + all_components[o];
            subject_with_components.push_back(combine); // now it gets each component for each subject
        }
        
    }
    }




int main() {

    // std::ios::app -  append in file not overwrite 
    ofstream wf("data/data.txt");

    string subjects[5] = {"oop", "embedded-systems", "data-communications", "operating-systems", "applied-maths-ii"};
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
// ...COMPLETED test#3 - if files, all subject get all components with correct numbering
        vector<string> subject_with_components;
        combineComponentswithSubjects(subjects, subject_code,subject_credit_hours, 5, all_components, subject_with_components);

for(string a : subject_with_components) {
    cout << a << endl;
}

cout << "Size: " << subject_with_components.size()<<endl;


// suppose there are 50 students

// todo: correct this loop, even though enough for testing

// test#1 - write basic info in a file

int n_of_students = 1;

for (int student = 0; student <= n_of_students; student++)
{

    for (int i = 0; i < subject_with_components.size(); i++)
    {
        wf << "7017707" << student << "," << "Name" << student << "," << "Fall-2025" << "," << subject_with_components[i]<<endl;

    }
}
}