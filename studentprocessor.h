#pragma once

#include "person.h"
#include <vector>
#include <string>

class StudentProcessor {
public:
    static bool compareStudents(const Person& a, const Person& b);

    static bool readFromFile(
        std::vector<Person>& students,
        const std::string& filename
    );

    static void sortStudents(std::vector<Person>& students);
};
