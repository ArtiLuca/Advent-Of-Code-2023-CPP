#include "GearRatios.h"

#include <fstream>

GearRatios::GearRatios(const std::string& input) {
    puzzleInput = input;
}

void GearRatios::readPuzzleInput() {

    std::ifstream f(puzzleInput);
    std::string str;

    while (std::getline(f, str)) {
        schematic.push_back(str);
    }

    std::cout << "Read " << schematic.size() << " lines" << std::endl;
    std::cout << "Puzzle input successfully read!" << std::endl;

    f.close();
}

void GearRatios::parseSchematicLine(int ind, bool detail) {

    std::string line = schematic[ind];
    int len = line.size();

    int pos = 0;

    while (pos < len) {

        if (std::isdigit(line[pos])) {
            int val = 0;
            int left = pos;

            while (pos < len && std::isdigit(line[pos])) {
                val = val * 10 + (line[pos] - '0');
                pos++;
            }

            int right = pos -1;

            Number num;
            num.value = val;
            num.row = ind;
            num.colStart = left;
            num.colEnd = right;
            numbers.push_back(num);

            if (detail) {
                std::cout << "Line: " << ind << ", ";
                num.printNumber();
            }
        }

        else {

            if (line[pos] != '.') {
                Symbol symb;
                symb.type = line[pos];
                symb.row = ind;
                symb.col = pos;
                symbols.push_back(symb);

                if (detail) {
                    std::cout << "Line: " << ind << ", ";
                    symb.printSymbol();
                }
            }

            pos++;
        }
    }
}

void GearRatios::parseFullSchematic(bool detail) {

    for (int i = 0; i < (int)schematic.size(); ++i) {
        parseSchematicLine(i, detail);
    }

    //if (detail)

    std::cout << "Total numbers parsed: " << numbers.size() << std::endl;
    std::cout << "Total symbols parsed: " << symbols.size() << std::endl;
}

bool GearRatios::isPartNumber(int n, bool detail) {

    Number num = numbers[n];
    if (detail) num.printNumber();

    int r0 = num.row - 1;
    int r1 = num.row + 1;
    int c0 = num.colStart - 1;
    int c1 = num.colEnd + 1;

    for (const Symbol& s : symbols) {
        if (s.row >= r0 && s.row <= r1 && s.col >= c0 && s.col <= c1) {
            if (detail) std::cout << "Symbol " << s.type << " touces number " << num.value << "\n";
            return true;
        }
    }
    return false;
}

int GearRatios::getSolutionPart1() {

    int sum = 0;
    for (int i = 0; i < (int)numbers.size(); ++i) {
        if (isPartNumber(i, false)) sum += numbers[i].value;
    }
    return sum;
}

int GearRatios::isTouchingTwoNumbers(int n, bool detail) {

    Symbol s = symbols[n];
    if (detail) s.printSymbol();

    int ratio = 1;
    int count = 0;

    int r0 = s.row - 1;
    int r1 = s.row + 1;
    int c0 = s.col - 1;
    int c1 = s.col + 1;

    for (const Number& num : numbers) {

        if (num.row >= r0 && num.row <= r1 &&
            num.colEnd >= c0 && num.colStart <= c1) {

            if (detail)
                std::cout << "Number " << num.value << " touches * symbls\n";

            count++;
            ratio *= num.value;
        }
    }
    if (count == 2) {
        if (detail)
            std::cout << "Found valid gear at ("
                      << s.row << ", " << s.col << ")\n";
        return ratio;
    }

    return -1;
}

int GearRatios::getSolutionPart2() {

    int sum = 0;

    for (int i = 0; i < (int)symbols.size(); ++i) {

        if (symbols[i].type == '*') {
            int ratio = isTouchingTwoNumbers(i, false);

            if (ratio > 0)
                sum += ratio;
        }
    }

    return sum;
}



