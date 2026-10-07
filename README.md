Student Final Grade Calculator

Introduction

This project is a C++ application for calculating students’ final grades based on their homework and examination results.

The program supports:

* Manual student data input.
* A variable number of homework assignments.
* std::vector for storing homework results.
* Final grade calculation using the average.
* Final grade calculation using the median.
* Random generation of homework and exam results.
* Reading student data from Students.txt.
* Sorting students by surname.
* Formatted output with two decimal places.

Final Grade Calculation

The final grade consists of 40% homework results and 60% of the examination result.

Average

Final grade:

0.4 × Homework Average + 0.6 × Exam

Median

Final grade:

0.4 × Homework Median + 0.6 × Exam

Person Class

The Person class stores:

* Student’s first name.
* Student’s surname.
* Homework results.
* Examination result.
* Final grade.

The class implements the Rule of Three:

1. Copy constructor.
2. Assignment operator.
3. Destructor.

The following operators are also overloaded:

* operator>> for input.
* operator<< for output.

Technologies

* C++
* Object-Oriented Programming
* STL
* std::vector
* File input/output
* Random number generation
* Sorting algorithms

Version

v0.1
