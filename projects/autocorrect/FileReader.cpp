//
// Created by Elijah Ghossein on 5/11/25.
//

#include "FileReader.h"


#include <fstream>
#include <iostream>

FileReader::FileReader(const std::string &filename) {

    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        words.emplace_back(Word(line));
    }

    file.close();
}

std::vector<Word> FileReader::getWords() {
    return words;
}
