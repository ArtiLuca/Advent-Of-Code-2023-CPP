#ifndef CUBE_CONUNDRUM_H
#define CUBE_CONUNDRUM_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>

/**
 * @struct CubeSet
 * @brief Represents a single revealed subset of cubes in a game.
 *
 * Each CubeSet corresponds to one semicolon-separated draw
 * (e.g. "3 red, 4 blue, 2 green").
 *
 * Missing colors are implicitly represented as 0.
 */

struct CubeSet {

    int red = 0;
    int green = 0;
    int blue = 0;
};

/**
 * @struct Game
 * @brief Represents a single game from the puzzle input.
 *
 * A game consists of:
 *  - a unique game ID
 *  - a sequence of CubeSets, each corresponding to one draw
 *
 * CubeSets are independent observations; cubes are returned
 * to the bag after each draw.
 */

struct Game {

    int id;
    std::vector<CubeSet> cubeSets;
};

/**
 * @class CubeConundrum
 * @brief Solves Advent of Code 2023 Day 2 (Cube Conundrum).
 *
 * This class handles:
 *  - parsing the puzzle input into structured data
 *  - solving Part 1 (game feasibility under fixed constraints)
 *  - solving Part 2 (minimum required cubes and power computation)
 *
 * Parsing and problem logic are intentionally separated to
 * keep the implementation clear and extensible.
 */

class CubeConundrum {
public:


    // ================================================================
    //                     CLASS MEMEBERS
    // ================================================================

    /**
     * @brief Path to the puzzle input file.
     */
    std::string puzzleInput;

    /**
     * @brief All games parsed from the puzzle input.
     *
     * Each entry corresponds to one "Game X: ..." line.
     */
    std::vector<Game> games;


    // ================================================================
    //                     PART 1
    // ================================================================

    /**
     * @brief Constructs the CubeConundrum solver and reads the input file.
     *
     * @param input Path to the puzzle input file.
     */
    CubeConundrum(const std::string& input);

    /**
     * @brief Reads and parses the puzzle input file.
     *
     * Converts each input line into a Game object with
     * its associated CubeSets.
     *
     * This method performs only parsing, not validation.
     */
    void readPuzzleInput();

    /**
     * @brief Solves Part 1 of the puzzle.
     *
     * Determines which games are possible if the bag
     * contained at most:
     *  - 12 red cubes
     *  - 13 green cubes
     *  - 14 blue cubes
     *
     * A game is valid if all its CubeSets satisfy these limits.
     *
     * @param detail If true, prints debug information for valid games.
     * @return The sum of the IDs of all valid games.
     */
    int getSolutionPart1(bool detail = false);



    // ================================================================
    //                     PART 2
    // ================================================================

    /**
     * @brief Computes the minimum number of cubes required for a game (Part 2).
     *
     * For each color, the minimum required count is the maximum
     * observed count across all CubeSets of the game.
     *
     * @param g The game to analyze.
     * @return A CubeSet representing the minimum required cubes.
     */
    CubeSet minCubesNeeded(const Game& g);

    /**
     * @brief Solves Part 2 of the puzzle.
     *
     * For each game:
     *  - computes the minimum required cubes
     *  - computes the power of that set
     *  - sums the powers across all games
     *
     * @return The sum of the powers of all minimum cube sets.
     */
    int getSolutionPart2();


    /**
     * @brief Prints a game and its cube sets for debugging.
     *
     * @param pos Index of the game in the games vector.
     */
    void testPrintGame(int pos);
};



#endif // CUBE_CONUNDRUM_H
