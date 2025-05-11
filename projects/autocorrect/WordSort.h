//
// Created by Elijah Ghossein on 5/11/25.
//

#ifndef WORDSORT_H
#define WORDSORT_H
#include "FileReader.h"
#include "TextBox.h"
#include "../../ds/Heap.h"


class WordSort : public ml::Rectangle {

    TextBox* textBox;

    float tBXPos = 0.f;
    float tBYPos = 0.f;
    float tBYSize = 0.f;

    Heap<Word> wordHeap;

    FileReader reader;

    // calculate Levenshtein distance
    int levenshteinDist(const std::string &str1, const std::string &str2);

    // a heuristic function to determine a priority for each Word stored in reader.words
    void heuristicCheck(const std::string& query);

public:

    WordSort(const std::string &filename, TextBox *textBox);

    std::vector<ml::Text> suggestions;

    // reposition autocorrect to sit below text box
    void reposition();
    // call to update autocorrect suggestions on screen
    void autocorrect();

};



#endif //WORDSORT_H
