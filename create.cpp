// ... this file is supposed to create one file which will hold the dummy data

#include<iostream>
#include<fstream> // for file handling
#include<string>
#include<vector> // for resizable arrays
#include "Random.h" // for random val generation
using namespace std;


// combines components name with component number
void createTotalComponents(const string components[], int components_max[], int component_max_grades[], int size, vector<string> &component_arrays) {

    for (int i = 0; i < size; i++) 
    {
        for (int o = 1; o <= components_max[i] ; o++) {
            int max_grades = component_max_grades[i];
        component_arrays.push_back(components[i] + "_" + to_string(o) + "," + to_string(max_grades) + "," + to_string(genRandomVal(0, max_grades)));
        }
    }
}


// combines no_of_components with teachers
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
    int component_max_grades[] = {10,10,30,40,10};


    int components_max[5] = {4, 4, 1, 1, 16};

    vector<string> all_components;
    createTotalComponents(components, components_max, component_max_grades, 5, all_components);
        vector<string> subject_with_components;
        combineComponentswithSubjects(subjects, subject_code,subject_credit_hours, 5, all_components, subject_with_components);


// suppose there are 50 students

/* ... for each student:
total components = (4+4+1+1+16) = 26 components
for each subject = 26 entries
1 student (5 subjects) = 5 * 26 = 130 entries
*/
int n_of_students = 1;
        wf << "#Format," << "id,name,semester,subject,subject_code,credit_hours,component_type/number,total,obtained(random)" << endl;

for (int student = 1; student <= n_of_students; student++)
{

    for (int i = 0; i < subject_with_components.size(); i++)
    {
        wf << "7017707" << student << "," << "Name" << student << "," << "Fall-2025" << "," << subject_with_components[i] << endl;
    }
}
}