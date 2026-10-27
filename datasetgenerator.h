#pragma once

#include <string>
#include <cstddef>

class DatasetGenerator {
public:
    static void generateFile(
        const std::string& filename,
        std::size_t numberOfStudents
    );
};