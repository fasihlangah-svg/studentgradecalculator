#include "datasetgenerator.h"

#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

void DatasetGenerator::generateFile(
    const std::string& filename,
    std::size_t numberOfStudents
) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not create dataset file: " + filename
        );
    }

    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> gradeDistribution(0, 10);

    for (std::size_t i = 1; i <= numberOfStudents; ++i) {
        file << "Name" << i
             << " Surname" << i
             << " 3";

        for (int j = 0; j < 3; ++j) {
            file << ' ' << gradeDistribution(generator);
        }

        file << ' ' << gradeDistribution(generator) << '\n';

        if (!file) {
            throw std::runtime_error(
                "Error writing dataset file: " + filename
            );
        }
    }
}