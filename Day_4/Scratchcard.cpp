#include "Scratchcard.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>

Scratchcard::Scratchcard(const std::string& input)
    : puzzleInput(input)
{}

void Scratchcard::readPuzzleInput() {

    std::ifstream file(puzzleInput);
    std::string line;

    while (getline(file, line)) {

        Card c;

        // find colon ':'
        size_t colonPos = line.find(':');

        // split into ID, numbers
        std::string left = line.substr(0, colonPos);
        std::string right = line.substr(colonPos + 1);

        // store card ID
        c.id = std::stoi(left.substr(5)); // safe?

        // split right into numbers/winning
        size_t splitPos = right.find('|');
        std::string played = right.substr(0, splitPos);
        std::string winning = right.substr(splitPos + 1);

        // read each set
        std::stringstream ssPlayed(played);
        int n;
        while (ssPlayed >> n)
            c.numbers.push_back(n);

        std::stringstream ssWinning(winning);
        while (ssWinning >> n)
            c.winningNumbers.push_back(n);

        // store card
        cards.push_back(c);
    }

    file.close();
}

int Scratchcard::getPoints(int cardPos) {

    const Card& c = cards[cardPos];

    std::unordered_set<int> wins(c.winningNumbers.begin(), c.winningNumbers.end());

    int matches = 0;
    for (int x : c.numbers)
        if (wins.count(x)) matches++;


    // return only if at least 1 match
    if (matches == 0 ) return 0;
    else return 1 << (matches - 1);
}

int Scratchcard::getSolutionPart1() {

    int points = 0;
    for (int i = 0; i < (int)cards.size(); ++i) {
        int test = getPoints(i);
        points += test;
    }

    return points;
}

int Scratchcard::getMatches(int cardPos) {

    const Card& c = cards[cardPos];

    std::unordered_set<int> wins(c.winningNumbers.begin(), c.winningNumbers.end());

    int matchCount = 0;
    for (int x : c.numbers)
        if (wins.count(x)) matchCount++;

    return matchCount;
}

void Scratchcard::initializeStructuresForPart2() {

    matches.resize(cards.size());
    copies.resize(cards.size());

    for (int i = 0; i < (int)cards.size(); ++i) {

        // store number of matches
        matches[i] = getMatches(i);

        // initial copies 1
        copies[i] = 1;
    }
}

void Scratchcard::processMatches() {

    for (int i = 0; i < (int)cards.size(); ++i) {

        // get matches for given card
        int k = matches[i];

        // propagate copies
        for (int j = 1; j <= k; ++j)
            if (i + j < (int)cards.size())
                copies[i+j] += copies[i];
    }
}

long long Scratchcard::getSolutionPart2() {

    initializeStructuresForPart2();
    processMatches();

    long long total = 0;

    for (long long c : copies)
        total += c;

    return total;
}

void Scratchcard::testPrintCard(int cardPos) {

    const Card& c = cards[cardPos];
    std::cout << "ID: " << c.id << "\n";
    std::cout << "Numbers: ";
    for (int i = 0; (int)i < c.numbers.size(); ++i) std::cout << c.numbers[i] << ", ";
    std::cout << "\nWinning numbers: ";
    for (int i = 0; (int)i < c.winningNumbers.size(); ++i) std::cout << c.winningNumbers[i] << ", ";

}

