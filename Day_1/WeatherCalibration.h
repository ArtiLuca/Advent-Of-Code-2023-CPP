#ifndef WEATHER_CALIBRATION_H
#define WEATHER_CALIBRATION_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;


/**
 * @class WeatherCalibration1
 * @brief Solves Advent of Code 2023 Day 1 (Trebuchet?!) calibration problem.
 *
 * This class encapsulates the logic for both Part 1 and Part 2 of the puzzle.
 *
 * Part 1:
 *  - Each line contains random characters and decimal digits.
 *  - The calibration value for a line is obtained by concatenating
 *    the first and last numeric digit appearing in the line.
 *
 * Part 2:
 *  - In addition to numeric characters, digits may also appear as
 *    spelled-out words ("one" to "nine").
 *  - Digit words may overlap and must be detected without skipping characters.
 *  - The earliest and latest digit occurrence (numeric or spelled) determines
 *    the calibration value.
 */

class WeatherCalibration1 {

public:

    // ================================================================
    //                     CLASS MEMEBERS
    // ================================================================

    /**
     * @brief Path to the input file containing the calibration document.
     */
    std::string puzzleInput;

    /**
     * @brief Stores all calibration lines read from the input file.
     *
     * Each entry corresponds to one line in the puzzle input.
     */
    std::vector<std::string> calibrationLines;

    /**
     * @brief Stores the first and last digit values found for each line (Part 1).
     *
     * For each line i:
     *  - digitValues[i].first  = first numeric digit
     *  - digitValues[i].second = last numeric digit
     */
    std::vector<std::pair<int,int>> digitValues;

    /**
     * @brief Stores the indexes of the first and last numeric digits for each line.
     *
     * These indexes are later reused in Part 2 to compare against
     * spelled-out digit occurrences.
     */
    std::vector<std::pair<int,int>> digitIndexes;


    // ================================================================
    //                     PART 1
    // ================================================================

    /**
     * @brief Constructs the WeatherCalibration1 object.
     *
     * @param input Path to the calibration input file.
     */
    WeatherCalibration1(const std::string& input);

    /**
     * @brief Computes the calibration value for a single line (Part 1).
     *
     * Scans the string to find the first and last numeric digit ('0'–'9'),
     * stores both their values and positions, and returns the corresponding
     * two-digit calibration value.
     *
     * @param str     The input line to analyze.
     * @param detail  If true, prints debugging information.
     * @return        The calibration value derived from the line.
     */
    int computeCalibrationValue1(std::string str, bool detail = false);

    /**
     * @brief Reads the entire puzzle input file and processes all lines (Part 1).
     *
     * Each line is stored in calibrationLines, and its numeric digit
     * values and indexes are recorded for later reuse in Part 2.
     */
    void readPuzzleInput1();

    /**
     * @brief Computes the total calibration value for Part 1.
     *
     * Uses the digit values already extracted from all lines.
     *
     * @return The sum of all calibration values (Part 1 solution).
     */
    int getSolutionPart1();


    // ================================================================
    //                     PART 2
    // ================================================================

    /**
     * @brief Mapping of spelled-out digit strings to their numeric values.
     *
     * Used to detect digit words such as "one", "two", ..., "nine"
     * when scanning calibration lines in Part 2.
     */
    std::vector<std::pair<std::string, int>> letterDigits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };


    /**
     * @brief Computes the updated calibration value for a line (Part 2).
     *
     * Starts from the numeric digit solution obtained in Part 1 and
     * scans the line for occurrences of spelled-out digits.
     *
     * If a digit word appears earlier or later than the numeric digits,
     * the calibration value is updated accordingly.
     *
     * Overlapping digit words are explicitly supported.
     *
     * @param pos     Index of the line in calibrationLines.
     * @param detail  If true, prints debugging information.
     * @return        The updated calibration value for Part 2.
     */
    int computeCalibrationValue2(int pos, bool detail = false);

    /**
     * @brief Computes the total calibration value for Part 2.
     *
     * Applies Part 2 logic to each stored line and sums the resulting
     * calibration values.
     *
     * @return The sum of all calibration values (Part 2 solution).
     */
    int getSolutionPart2();
};


#endif // WEATHER_CALIBRATION_H
