//
// Created by Elijah Ghossein on 5/11/25.
//

#include "WordSort.h"

WordSort::WordSort(const std::string &filename, TextBox *textBox)
    : reader(filename), textBox(textBox)
{
    // 5 suggestions
    suggestions.reserve(5);
    for (int i = 0; i < 5; i++) {
        ml::Text t;
        t.setCharacterSize(24);
        t.setString("");
        suggestions.emplace_back(std::move(t));
    }

    onUpdate([this, textBox]() {
        // update positions of autocorrect suggestions
        const float typerSize = textBox->typer.getGlobalBounds().size.x;
        for (int i = 0; i < suggestions.size(); i++) {
            suggestions[i].setPosition({
                    tBXPos + typerSize,
                    tBYPos + tBYSize + (i * 25.f)
                    });
        }
    });
}

void WordSort::reposition() {
    tBXPos = textBox->getGlobalBounds().position.x;
    tBYPos = textBox->getGlobalBounds().position.y;
    tBYSize = textBox->getGlobalBounds().size.y;
}

void WordSort::autocorrect() {

    const std::string query = textBox->typer.getString();

    if (query.size() < 2) {
        for (int i = 0; i < suggestions.size(); i++) {
            suggestions[i].setString("");
        }
        return;
    }

    heuristicCheck(query);
    for (int i = 0; i < suggestions.size(); i++) {

        if (wordHeap.empty()) break;

        Word w = wordHeap.top();
        suggestions[i].setString(w.getString());
        wordHeap.pop();
    }
}

void WordSort::heuristicCheck(const std::string& query) {
    wordHeap.clear(); // fresh start

    if (query.size() > 0) {
        for (Word& w : reader.getWords()) {
            const std::string& word = w.getString();

            // Levenshtein distance score
            int score = levenshteinDist(query, word);

            // check if query appears at the beginning of a word
            if (word.rfind(query, 0) == 0) {
                score -= 3;
            }

            w.setPriority(-score);
            wordHeap.push(w);
        }
    }
}

// Returns the Levenshtein distance between word1 and word2.
int WordSort::levenshteinDist(const std::string& str1, const std::string& str2)
{
    const int m = str1.length();
    const int n = str2.length();

    std::vector<int> row(n + 1);
    for (int j = 0; j <= n; ++j) {
        row[j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        int prev = row[0];
        row[0] = i;

        for (int j = 1; j <= n; ++j) {
            int temp = row[j];
            if (str1[i - 1] == str2[j - 1]) {
                row[j] = prev;
            } else {
                row[j] = 1 + std::min({ row[j - 1], row[j], prev });
            }
            prev = temp;
        }
    }

    return row[n];
}
