# Notes


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


## Logic

`Converter.h` header file that handles conversion as when we read from a file, however the data maybe its in strings, we need it in different format like:

`string` → `int`, `double`, `float` or even `bool`, for appropriate calculations, conditionals