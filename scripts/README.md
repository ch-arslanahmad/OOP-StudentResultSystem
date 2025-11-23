Generate sub-grades
===================

This folder contains `generate_sub_grades.py` — a small utility to generate `data/sub-grades.txt` from
`data/subjects.txt` and `data/students.txt`.

Quick usage (from repository root):

```bash
python3 scripts/generate_sub_grades.py \
  --subjects data/subjects.txt \
  --students data/students.txt \
  --out data/sub-grades.txt
```

Notes:
- The script ignores comment lines starting with `#` or `//`.
- It only assigns a subject to a student when the subject's `Course` and `Semester` match the student's.
- Scoring pattern is fixed in the script (quizzes/assignments/midterm/final/labs) — edit the script if you need different scores.
