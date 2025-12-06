# Notes

## Plan (Todo)

### Phase 1 – Create 1 File via Code




The file must contain all data of all students, their subjects, grades etc over the semester.

- [x] Make a program that creates the file with Student (dummy) basic data only.
- [x] Add subjects for the semester.
- [x] Add components for each subject (quizes, assignments, exams) with numbering. 
- [x]] Add grades for each student in each subject (dummy data).


### Phase 2 – Read File and Compute GPA

> [!IMPORTANT]
> Goal: compute each student’s GPA from raw component marks.

- [x] Get all data from the file created in Phase 1.
- [x] Get Marks
  - [x] Sum all its totals and sum all its obtained marks.
  - [x] Compute ratio = obtained / total (e.g., 24/40 = 0.60 → 60%).
  - [] Multiply ratio by the component weight (e.g., 0.60 × 10% = 6.0).
  - [x] Add all five components to get subject score out of 100.
- [x] Store them in a HashMap
- [x] Convert the normalized score to a grade point using standard conditions
- [x] Multiply grade point by credit hours to get weighted grade point
- [x] GPA = sum(weightedGradePoints) / sum(creditHours) for the student
  - [x] Display GPA per student


## Data Context

course BSIET, semster 2, subjects following:

Object Oriented Programming
4 credit hours
Operating Systems
3 - credit hours
Data Communication and Computer Networks
4 - credit hours
Applied Mathematics II
3 - credit hours
Embedded Systems
3 - credit hours

,keep in mind, Embedded and OOP will have LABs as well and they will be:
16 total for each subject.
there will be 4 assignments, 4 quizzes per subject
2 total exams, 1 midterm and one final.

The weightage will be seperate based on if they have lab or not.

For example with lab,

Assignments & Quizzes total - 20% (10% each)
Midterm - 30%
Final - 40%
Lab - 10%

Without:

- Assignments & Quizzes total - 20%
- Midterm 30%
- Final 50%

So, we need a file for:

- Semester Info with subjects - subjects.txt
- grade system - weightage - weightage.txt
  - with lab/no-lab/custom (name & weightage)
  - **Requirenment:** for number of quizes, assignments, n of xy-activity.
- Student Info Only (Name, Sap) - students.txt
- total/obtained marks in subjects - grades.txt
  - quizzes & assignments (n)
  - midterm
  - total term
  - with student names

We can get the following output:

- Student Card
- Class Result


## Logic

### Files Responsibility
`Converter.h` header file that handles conversion as when we read from a file, however the data maybe its in strings, we need it in different format like:

`string` → `int`, `double`, `float` or even `bool`, for appropriate calculations, conditionals


### Thought Process

#### Using HashMap for Records
Before i thought that using Hashmap is a plus but now i think its a necessity, because as we read from the grades file,

if each subject has:
- 4 assigments, 4 quizzess, 1 mid, 1 final..
10 lines for each student,
**10 student = 100 lines**

Then for 5 subjects = 500 lines

if lab subject has
- 4 assignmets, 4 quizzes, 1 mid, 1 final, 16 labs
26 for each student,
**10 student = 260 lines...**
Then for 5 subjects = 1300 lines

i think vector manual linear search will get hectic and it is now a necessity to use a hashmap!

So making multiple hashmaps that have a common identifier (student sap) to link them all together.