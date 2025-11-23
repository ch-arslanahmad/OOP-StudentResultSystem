#!/usr/bin/env python3
"""
Generate `data/sub-grades.txt` from `data/subjects.txt` and `data/students.txt`.

Output format (one entry per line):
Course,Semester,SAP,SubjectCode,Component,Index,Total,Obtained

Usage:
  python3 scripts/generate_sub_grades.py \
    --subjects data/subjects.txt \
    --students data/students.txt \
    --out data/sub-grades.txt

The script uses a fixed pattern of scores:
- quizzes: 4 items -> 8,9,8,9 out of 10
- assignments: 4 items -> 9,9,7,3 out of 10
- midterm: 64/100 (index 1)
- final: 81/100 (index 1)
- lab (if subject has lab=true): 16 items all 9/10

The script only assigns a subject to a student when the subject's course and semester
match the student's course and semester.
"""

import argparse
from pathlib import Path
import sys

QUIZ_SCORES = [8, 9, 8, 9]
ASSIGN_SCORES = [9, 9, 7, 3]
MIDTERM = (64, 100)
FINAL = (81, 100)
LAB_SCORE = 9
LAB_COUNT = 16


def parse_subjects(path):
    subjects = []
    for raw in Path(path).read_text(encoding='utf-8').splitlines():
        line = raw.strip()
        if not line or line.startswith('#') or line.startswith('//'):
            continue
        parts = [p.strip() for p in line.split(',')]
        if len(parts) < 6:
            # skip malformed lines
            continue
        course = parts[0]
        semester = parts[1]
        code = parts[2]
        # remaining fields are name, creditHours, lab
        lab_field = parts[-1].lower()
        lab = lab_field in ('true', '1', 'yes', 'y', 't')
        subjects.append({
            'course': course,
            'semester': semester,
            'code': code,
            'lab': lab,
        })
    return subjects


def parse_students(path):
    students = []
    for raw in Path(path).read_text(encoding='utf-8').splitlines():
        line = raw.strip()
        if not line or line.startswith('#'):
            continue
        parts = [p.strip() for p in line.split(',')]
        if len(parts) < 4:
            continue
        sap = parts[0]
        name = parts[1]
        course = parts[2]
        semester = parts[3]
        students.append({'sap': sap, 'name': name, 'course': course, 'semester': semester})
    return students


def normalize(s):
    return str(s).strip()


def generate_lines(subjects, students):
    out_lines = []
    header = '# Format: Course,Semester,SAP,SubjectCode,Component,Index,Total,Obtained'
    out_lines.append(header)

    # For deterministic output, sort students by SAP and subjects by code
    students_sorted = sorted(students, key=lambda s: s['sap'])
    subjects_sorted = sorted(subjects, key=lambda s: (s['course'], s['semester'], s['code']))

    for stu in students_sorted:
        stu_course = normalize(stu['course'])
        stu_sem = normalize(stu['semester'])
        for sub in subjects_sorted:
            sub_course = normalize(sub['course'])
            sub_sem = normalize(sub['semester'])
            if stu_course != sub_course or stu_sem != sub_sem:
                continue
            sap = stu['sap']
            code = normalize(sub['code'])

            # quizzes
            for idx, score in enumerate(QUIZ_SCORES, start=1):
                out_lines.append(f"{stu_course},{stu_sem},{sap},{code},quizzes,{idx},10,{score}")
            # assignments
            for idx, score in enumerate(ASSIGN_SCORES, start=1):
                out_lines.append(f"{stu_course},{stu_sem},{sap},{code},assignments,{idx},10,{score}")
            # midterm
            out_lines.append(f"{stu_course},{stu_sem},{sap},{code},midterm,1,{MIDTERM[1]},{MIDTERM[0]}")
            # final
            out_lines.append(f"{stu_course},{stu_sem},{sap},{code},final,1,{FINAL[1]},{FINAL[0]}")
            # labs if applicable
            if sub['lab']:
                for idx in range(1, LAB_COUNT + 1):
                    out_lines.append(f"{stu_course},{stu_sem},{sap},{code},lab,{idx},10,{LAB_SCORE}")

    return out_lines


def main(argv=None):
    parser = argparse.ArgumentParser(description='Generate sub-grades from subjects+students files')
    parser.add_argument('--subjects', default='data/subjects.txt', help='Path to subjects.txt')
    parser.add_argument('--students', default='data/students.txt', help='Path to students.txt')
    parser.add_argument('--out', default='data/sub-grades.txt', help='Output file path')
    parser.add_argument('--no-overwrite', dest='overwrite', action='store_false', help='Do not overwrite output if exists')
    args = parser.parse_args(argv)

    subjects_path = Path(args.subjects)
    students_path = Path(args.students)
    out_path = Path(args.out)

    if not subjects_path.exists():
        print(f"Subjects file not found: {subjects_path}", file=sys.stderr)
        sys.exit(2)
    if not students_path.exists():
        print(f"Students file not found: {students_path}", file=sys.stderr)
        sys.exit(2)
    if out_path.exists() and not args.overwrite:
        print(f"Output exists and overwrite disabled: {out_path}", file=sys.stderr)
        sys.exit(3)

    subjects = parse_subjects(subjects_path)
    students = parse_students(students_path)

    lines = generate_lines(subjects, students)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text('\n'.join(lines) + '\n', encoding='utf-8')

    print(f"Wrote {len(lines)} lines to {out_path}")


if __name__ == '__main__':
    main()
