#ifndef GEAR_RATIOS_H
#define GEAR_RATIOS_H

#include <iostream>
#include <string>
#include <vector>


/**
 * @struct Symbol
 * @brief Represents a non-digit, non-period character in the engine schematic.
 *
 * A symbol is any character that is not:
 *   - a digit ('0'–'9')
 *   - a period ('.')
 *
 * Symbols are stored with their coordinates and are used to determine
 * adjacency relationships with numbers.
 */

struct Symbol {
    char type;
    int row;
    int col;

    void printSymbol() { std::cout << type << " (" << row << ", " << col << ")\n"; }
};

/**
 * @struct Number
 * @brief Represents a horizontally contiguous number in the schematic.
 *
 * Each Number stores:
 *   - its parsed integer value
 *   - the row in which it appears
 *   - the starting and ending column indices (inclusive)
 *
 * These intervals are used to test adjacency against symbols.
 */

struct Number {
    int value;
    int row;
    int colStart;
    int colEnd;

    void printNumber() { std::cout << value << ", row " << row << "(" << colStart << "-" << colEnd << ")\n"; }
};


/**
 * @class GearRatios
 * @brief Solves Advent of Code 2023 Day 3 (Gear Ratios).
 *
 * This class performs:
 *   - Parsing of the engine schematic grid
 *   - Extraction of Number and Symbol entities
 *   - Part 1: Summing all part numbers
 *   - (Part 2 will build on the same adjacency logic)
 *
 * The implementation follows a two-phase architecture:
 *   Phase 1: Parse entities (numbers + symbols)
 *   Phase 2: Compute relationships (adjacency checks)
 */

class GearRatios {
public:


    // ================================================================
    //                     CLASS MEMEBERS
    // ================================================================

    /** @brief Path to the puzzle input file */
    std::string puzzleInput;
    /** @brief Stores the full schematic grid as read from input. */
    std::vector<std::string> schematic;
    /** @brief All non-digit, non-period symbols found in the schematic. */
    std::vector<Symbol> symbols;
    /** @brief All parsed numbers found in the schematic. */
    std::vector<Number> numbers;

    // ================================================================
    //                              PART 1
    // ================================================================

    /**
     * @brief Constructs the solver using the given input file.
     * @param input Path to puzzle input.
     */
    GearRatios(const std::string& input);

    /**
     * @brief Reads the puzzle input file into the schematic grid.
     */
    void readPuzzleInput();

    /**
     * @brief Parses a single schematic line to extract numbers and symbols.
     *
     * @param ind Index of the row to parse.
     * @param detail If true, prints parsed entities.
     */
    void parseSchematicLine(int ind, bool detail = false);

    /**
     * @brief Parses the entire schematic grid.
     *
     * Extracts all numbers and symbols into their respective vectors.
     *
     * @param detail If true, prints parsed entities.
     */
    void parseFullSchematic(bool detail = false);


    /**
     * @brief Determines whether a number is a valid part number (Part 1).
     *
     * A number is a part number if at least one symbol lies in its
     * 3×(width+2) adjacency rectangle (including diagonals).
     *
     * @param n Index of the number in the numbers vector.
     * @param detail If true, prints adjacency debug info.
     * @return True if the number touches a symbol.
     */
    bool isPartNumber(int n, bool detail = false);

    /**
     * @brief Computes the solution to Part 1.
     *
     * Sums all numbers that qualify as part numbers.
     *
     * @return Sum of all valid part numbers.
     */
    int getSolutionPart1();


    // ================================================================
    //                              PART 2
    // ================================================================


    /**
     * @brief Determines whether a '*' symbol forms a valid gear.
     *
     * A symbol qualifies as a gear if:
     *   - Its type is '*'
     *   - Exactly two distinct numbers lie in its 3×3 adjacency region
     *     (including diagonals).
     *
     * If exactly two numbers touch the symbol, the gear ratio is defined as
     * the product of their values.
     *
     * The adjacency test checks interval overlap between:
     *   - The 3×3 neighborhood centered on the symbol
     *   - The horizontal span of each number (colStart → colEnd)
     *
     * @param n Index of the symbol in the symbols vector.
     * @param detail If true, prints adjacency and gear detection debug info.
     * @return The gear ratio if exactly two numbers touch the symbol;
     *         otherwise returns -1.
     */
    int isTouchingTwoNumbers(int n, bool detail = false);


    /**
     * @brief Computes the solution to Part 2 (sum of all gear ratios).
     *
     * Iterates over all '*' symbols and:
     *   - Identifies valid gears (exactly two adjacent numbers)
     *   - Computes their gear ratios
     *   - Sums all valid gear ratios
     *
     * @return The total sum of all valid gear ratios.
     */
    int getSolutionPart2();

};


#endif // GEAR_RATIOS_H
