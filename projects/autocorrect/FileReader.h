//
// Created by Elijah Ghossein on 5/11/25.
//

#ifndef FILEREADER_H
#define FILEREADER_H
#include <vector>
#include <string>

#include "Word.h"


class FileReader {

    std::vector<Word> words;

public:

    FileReader(const std::string &filename);

    std::vector<Word> getWords();

};



#endif //FILEREADER_H
