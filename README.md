# OOP-StudentResultSystem

Student Result Manger, track subjects, their grades in assignments, quizes and exams and computing semester CGPA.

## Idea

Rather than building a plain CLI program that only takes input and displays output (in CLI), this project will simulate a classroom environment. We will use dummy data files containing:

- A _list of students_ with their semesters.
- Subjects offered in each semester.
- _Grades of students_ in quizzes, assignments, midterm, and final exams.

The program will read these files, process the data, and output results in both the CLI and an output file, showing each student’s semester GPA and overall CGPA.

> [!IMPORTANT]
> The files need to be a specfic format to be read.

This structure reflects an OOP-based academic performance system, similar to what was described in class.

> [!NOTE]
> First priority is program working, then is applying OOP.

## Context

Files should have, Semester Specified, and its subjects.

Each subject will have:

- 4 quizzes
- 4 assignments
- 2 exams (midterm & final)

All this data will be in files.

**The program will read and give output in CLI/Output File.**

## Plan (Todo)

- [X] Finalize what files to make
- [X] Make the files
- [X] Finalize the files structure


### Phase 1 – Data Integration (Functionality First)

**Goal:** Build logic to correctly read and link all base data files before doing any calculations.

- [x] Read `students.txt`
- [x] Read `subjects.txt`
- [ ] Read `grade-policy.txt` (weightage of each component)
- [ ] Read `grades.txt`
- [ ] Link students → subjects → grades using common identifiers
- [ ] Verify merged data integrity (no missing subject or student references)
- [ ] Remove redundant `semester_subjects.txt` if not needed
  - [ ] See if Requires further enhancement, linking of files and for them to make sense .

- [ ] Read 1/2 lines from a file and print a meaningful output, i.e., `student: Arslan`, by reading from a file.

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

Assignments & Quizzes total - 20%
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
