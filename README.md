# OOP-StudentResultSystem

Student Result Manger, track subjects, their grades in assignments, quizes and exams and computing semester CGPA.

## Idea

Rather than building a plain CLI program that only takes input and displays output (in CLI), this project will simulate a classroom environment. We will use dummy data files containing:

- A _list of students_ with their semesters.
- Subjects offered in each semester.
- _Grades of students_ in quizzes, assignments, midterm, and final exams.

The program will BOTH create & read these files, process the data, and output results in both the CLI and an output file, showing each student’s semester GPA and overall CGPA.

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

For [more info](NOTES.md#data-context)