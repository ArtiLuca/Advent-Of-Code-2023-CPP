#ifndef SCRATCHCARD_H
#define SCRATCHCARD_H

#include <string>
#include <vector>

/**
 * @struct Card
 * @brief Represents a single scratchcard.
 *
 * Each card contains:
 *   - A unique identifier (id)
 *   - A list of numbers revealed on the card
 *   - A list of winning numbers for that card
 *
 * The goal is to count how many revealed numbers
 * appear in the winning set.
 */

struct Card {
    int id;
    std::vector<int> numbers;
    std::vector<int> winningNumbers;
};


/**
 * @class Scratchcard
 * @brief Solves Advent of Code 2023 - Day 4: Scratchcards.
 *
 * Responsibilities:
 *   - Parse scratchcard input data
 *   - Store structured card representations
 *   - Compute total points for Part 1
 *
 * Problem Summary (Part 1):
 *   For each card:
 *     - Count how many revealed numbers match winning numbers.
 *     - If there are k matches:
 *           points = 2^(k - 1)
 *       If k = 0:
 *           points = 0
 *
 *   The final answer is the sum of all card points.
 *
 * Design Strategy:
 *   - Phase 1: Parse file into structured Card objects
 *   - Phase 2: For each card:
 *         Convert winning numbers into a hash set
 *         Count membership matches
 *         Compute score
 */

class Scratchcard {

public:


    // ================================================================
    //                     CLASS MEMEBERS
    // ================================================================

    /** @brief Path to the puzzle input file. */
    std::string puzzleInput;

    /** @brief All parsed scratchcards. */
    std::vector<Card> cards;

    std::vector<int> matches;
    std::vector<long long> copies;


    // ================================================================
    //                     PART 1
    // ================================================================


    /**
     * @brief Constructs the solver using the given input file.
     * @param input Path to puzzle input.
     */
    Scratchcard(const std::string& input);

    /**
     * @brief Reads and parses the puzzle input file.
     *
     * For each line:
     *   - Extract card ID
     *   - Extract revealed numbers
     *   - Extract winning numbers
     *   - Store as Card struct
     */
    void readPuzzleInput();

    /**
     * @brief Computes the point value of a single card.
     *
     * A card's points are:
     *   - 0 if no matches
     *   - 2^(matches - 1) otherwise
     *
     * Membership is checked using a hash set
     * for O(n) complexity per card.
     *
     * @param cardPos Index of the card.
     * @return Point value of that card.
     */
    int getPoints(int cardPos);

    /**
     * @brief Computes the total score for Part 1.
     *
     * Iterates through all cards and sums their points.
     *
     * @return Total scratchcard points.
     */
    int getSolutionPart1();


    /**
     * @brief Prints a card for debugging purposes.
     * @param cardPos Index of the card.
     */
    void testPrintCard(int cardPos);



    // ================================================================
    //                     PART 2
    // ================================================================

    /**
     * @brief Computes the number of matching numbers for a given card.
     *
     * Counts how many numbers revealed on the card appear
     * in its set of winning numbers.
     *
     * Internally uses a hash set for O(n) membership checks.
     *
     * @param cardPos Index of the card.
     * @return Number of matches.
     */
    int getMatches(int cardPos);

    /**
     * @brief Initializes data structures required for Part 2.
     *
     * Prepares:
     *   - matches[i] = number of matches for card i
     *   - copies[i]  = number of copies of card i (initially 1)
     *
     * Must be called before processing propagation.
     */
    void initializeStructuresForPart2();


    /**
     * @brief Propagates scratchcard copies according to match rules.
     *
     * For each card i:
     *   - Let k = matches[i]
     *   - Each of the copies[i] copies generates one copy
     *     of each of the next k cards.
     *
     * This is implemented as a forward dynamic programming pass.
     *
     * Complexity: O(n * m), where m is the maximum matches.
     */
    void processMatches();


    /**
     * @brief Computes the final total number of scratchcards.
     *
     * After propagation, sums all entries in the copies vector.
     *
     * @return Total number of original and generated scratchcards.
    */
    long long getSolutionPart2();

};


#endif // SCRATCHCARD_H

