#pragma once

#include "person.h"
#include <vector>
#include <string>

class StudentProcessor {
public:
    static bool compareStudents(
        const Person& a,
        const Person& b
    );

    static bool readFromFile(
        std::vector<Person>& students,
        const std::string& filename
    );

    static void sortStudents(
        std::vector<Person>& students
    );

    static void splitStudents(
        const std::vector<Person>& students,
        std::vector<Person>& passing,
        std::vector<Person>& failing
    );

    static void writeResults(
        const std::vector<Person>& passing,
        const std::vector<Person>& failing,
        const std::string& passingFile,
        const std::string& failingFile
    );
};