# CGPA Calculator

This is a simple C program that calculates the SGPA (Semester Grade Point Average) for each semester and the overall CGPA (Cumulative Grade Point Average) for a student. The program allows the user to input course details such as credits and grades, and then computes the SGPA and CGPA accordingly.

## Features

- Allows the user to input their name and USN (University Serial Number).
- Supports up to 8 semesters of grades and course details.
- Converts letter grades (A+, A, A-, B+, B, etc.) into grade points.
- Calculates SGPA for each semester and CGPA based on user input.
- Outputs the result to a text file (`grades_summary.txt`), which includes the name, USN, SGPA for each semester, and overall CGPA.

## Requirements

- C Compiler (e.g., GCC)
- Basic knowledge of C programming

## Instructions

### Compilation
To compile the program, use a C compiler such as GCC. For example:

```bash
gcc -o cgpa_calculator cgpa_calculator.c
