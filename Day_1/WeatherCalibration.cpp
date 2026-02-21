#include "WeatherCalibration.h"

WeatherCalibration1::WeatherCalibration1(const std::string& input) {
    puzzleInput = input;
}

int WeatherCalibration1::computeCalibrationValue1(std::string str, bool detail) {

    int len = str.size();
    int first = -1;
    int last = -1;

    // store digit values/indexes founds
    std::pair<int,int> values = {-1,-1};
    std::pair<int,int> indexes = {-1,-1};

    // iterate string
    for (int i = 0; i < len; ++i) {

        // if first digit not yet found
        if (first < 0) {

            // found first digit
            if (isdigit(str[i])) {
                first = str[i] - '0';
                values.first = first;
                indexes.first = i;
            }
        }

        // if second digit not yet found
        if (last < 0) {

            // found last digit
            if (isdigit(str[len - 1 - i])) {
                last = str[len - 1 - i] - '0';
                values.second = last;
                indexes.second = len - 1 - i;
            }
        }
    }

    // store digit values and indexes found
    digitValues.push_back(values);
    digitIndexes.push_back(indexes);

    // compute calibration value
    int value = (values.first * 10) + values.second;

    if (detail) {
        std::cout << "Line: " << str << std::endl;
        std::cout << "first=" << values.first << " (ind. " << indexes.first << ")\n";
        std::cout << "last=" << values.second << " (ind. " << indexes.second << ")\n";
        std::cout << "Value = " << value << std::endl;
    }

    return value;
}

void WeatherCalibration1::readPuzzleInput1() {

    std::ifstream f(puzzleInput);
    std::string s;

    int solution = 0;
    int val;

    // read each line
    while (std::getline(f, s)) {

        // compute and update calibration value counter for line
        val = computeCalibrationValue1(s, false);
        solution += val;
        // store line
        calibrationLines.push_back(s);
    }

    f.close();
}

int WeatherCalibration1::getSolutionPart1() {

    int solution = 0;
    int val;

    for (int i = 0; i < (int)digitValues.size(); ++i) {
        val = (digitValues[i].first * 10) + digitValues[i].second;
        solution += val;
    }

    return solution;
}

int WeatherCalibration1::computeCalibrationValue2(int pos, bool detail) {

    // retrieve stored solution for Part 1
    std::string s = calibrationLines[pos];
    int first = digitIndexes[pos].first;
    int last = digitIndexes[pos].second;
    int firstDigit = digitValues[pos].first;
    int lastDigit = digitValues[pos].second;
    int origVal = (firstDigit * 10) + lastDigit;

    // check occurrences for each letter digit
    for (int i = 0; i < 9; ++i) {

        int pos = static_cast<int>(s.find(letterDigits[i].first));

        while (pos != std::string::npos) {

            // if smaller 'first' letter digit found
            if (pos < first) {
                first = pos;
                firstDigit = letterDigits[i].second;
                if (detail) std::cout << "Smaller 'first' found at index " << pos << " (" << letterDigits[i].first << ")\n";
            }

            // if larger 'last' letter digit
            if (pos > last) {
                last = pos;
                lastDigit = letterDigits[i].second;
                if (detail) std::cout << "Larger 'last' found at index " << pos << " (" << letterDigits[i].first << ")\n";
            }

            // updated pos, allowing overlaps
            pos = s.find(letterDigits[i].first, pos+1);
        }
    }

    // compute updated calibration value, or remains unchanged
    int newVal = (firstDigit * 10) + lastDigit;
    if (detail) std::cout << "Found new value: " << origVal << " -> " << newVal << std::endl;
    return newVal;
}

int WeatherCalibration1::getSolutionPart2() {

    int solution = 0;
    int val;

    for (int i = 0; i < (int)digitValues.size(); ++i) {
        val = computeCalibrationValue2(i, false);
        solution += val;
    }

    return solution;
}
