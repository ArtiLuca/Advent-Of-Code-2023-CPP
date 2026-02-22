#ifndef ALMANAC_H
#define ALMANAC_H

#include <string>
#include <vector>
#include <iostream>

// Day 5 - If You Give A Seed A Fertilizer

/*
    === PART 1 ===

We model the problem as a pipeline of piecewise-linear functions:

    location = f7 ∘ f6 ∘ f5 ∘ ... ∘ f1 (seed)

Each map defines a transformation:

    destStart sourceStart length

This defines:

    Source interval:      [sourceStart, sourceStart + length - 1]
    Destination interval: [destStart, destStart + length - 1]

For x inside the source interval:

    x -> x + (destStart - sourceStart)

For x outside all source intervals:

    x -> x (identity)

For each seed:
    Apply all maps in order.
    Take the minimum final location.
*/


/*
    === PART 2 ===

1. If dealing with intervals, the ranges of seeds becomes too large to process every single seed.
   So instead of doing: value -> value
                 we do: interval -> intervals(s)

We define a new struct 'Interval' to represent (start, end] for each pair of seeds.

2. We turn the seed pairs into Intervals of seeds.

3. We then apply one map to many intervals, using a function such as:

    vector<Interval> applyMapToIntervals
        (const RuleMap& map, const vector<Interval>& inputIntervals);

4. Meaning we build a new list:

     vector<Interval> output

   and then for every input interval [a,b] we process it against all rules.

5. That is, for one interval [a,b] we keep a working list:

    vector<Interval> remaining = { [a, b] }

   Then for each rule in map.rules we process overlaps.

6. We have to compute the intersections. For example, given:

    interval = [x1,x2]
    rule = [r1,r2]

   We compute:

    overlapStart = max(x1, r1)
    overlapEnd = min(x2, r2)

In the case that overlapStart <= overlapEnd ... we have an overlap.

7. When there is an overlap, we split the interval into up to 3 pieces:

    a) left remainder:
       [x1, overlapStart - 1] (only if x1 < overlapStart)

    b) overlapping mapped part (we shift by delta)
       [overlapStart + delta, overlapEnd + delta]
      We add this directly to output

    c) right remainder:
       [overlapEnd + 1, x2] (only if overlapEnd < x2)

8. We do not recompute the overlapping piece, but only the leftover ones.

9. The remaining intervals (the ones that never matched any rule) simply map to themselves.
   So we simply add them unchanged to output.

10. The answer is the minimum found.



*/


/**
 * @struct Rule
 * @brief Represents a single interval mapping rule.
 *
 * Each rule models a piecewise-linear transformation over a source interval.

 * A rule is derived from an input line of the form:
 *
 *      destStart sourceStart length
 *
 * This defines:
 *
 *      Source interval:      [srcStart, srcEnd]
 *      Destination interval: [srcStart + delta, srcEnd + delta]
 *
 * where:
 *
 *      srcEnd = srcStart + length - 1
 *      delta  = destStart - srcStart
 *
 * For any value x inside the source interval:
 *
 *      x → x + delta
 *
 * Values outside all source intervals are unaffected (identity mapping).
 */

struct Rule {
    long long srcStart;
    long long srcEnd;
    long long delta;


    /**
     * @brief Prints the rule for debugging purposes.
     *
     * Displays the source interval and corresponding destination interval.
     */
    void printRule() const;
};



/**
 * @struct RuleMap
 * @brief Represents a full category-to-category transformation.
 *
 * A RuleMap contains multiple Rule objects and models
 * a piecewise-defined function:
 *
 *      f : ℤ → ℤ
 *
 * For a given input value:
 *   - The first rule whose source interval contains the value applies.
 *   - If no rule applies, the value maps to itself (identity).
 *
 * Example:
 *   seed-to-soil
 *   soil-to-fertilizer
 *   fertilizer-to-water
 *   ...
 */

struct RuleMap {
    std::string name;
    std::vector<Rule> rules;


    /**
     * @brief Applies this rule map to a single value.
     *
     * If the value lies within a rule's source interval,
     * the corresponding delta offset is applied.
     * Otherwise, the value is returned unchanged.
     *
     * @param x Input value.
     * @return Transformed value after applying the rule map.
     */
    long long apply(long long x) const;

    /**
     * @brief Prints summary information about the rule map.
     */
    void printRuleMap() const;
};


/**
 * @class Almanac
 * @brief Solves Advent of Code 2023 - Day 5: If You Give A Seed A Fertilizer.
 *
 * Problem Model:
 *
 * The input describes a pipeline of piecewise-linear transformations:
 *
 *      location = f_n ∘ f_{n-1} ∘ ... ∘ f_1 (seed)
 *
 * Each map converts numbers from one category to the next
 * using interval-based offset rules.
 *
 * Part 1:
 *   - Apply all maps sequentially to each seed.
 *   - Compute the final location value.
 *   - Return the minimum location over all seeds.
 *
 * Design Strategy:
 *   Phase 1: Parse file into:
 *       - Vector of seed values
 *       - Ordered vector of RuleMap objects
 *
 *   Phase 2:
 *       - For each seed, apply maps in order
 *       - Track the minimum resulting location
 */



/**
 * @struct Interval
 * @brief Represents a closed integer interval [start, end].
 *
 * Used in Part 2 to efficiently model large contiguous ranges
 * of seed values without enumerating individual seeds.
 *
 * Both endpoints are inclusive:
 *
 *      start ≤ x ≤ end
 */

struct Interval {
    long long start;
    long long end;
};



class Almanac {

public:

    // ================================================================
    //                     CLASS MEMEBERS
    // ================================================================

    /** @brief Path to the puzzle input file. */
    std::string puzzleInput;

    /** @brief Initial seed values read from the input. */
    std::vector<long long> seeds;

    /** @brief Ordered collection of all transformation maps. */
    std::vector<RuleMap> ruleMaps;

    std::vector<Interval> seedIntervals;




    // ================================================================
    //                     PART 1
    // ================================================================

    /**
     * @brief Constructs the Almanac solver using the given input file.
     *
     * @param input Path to the puzzle input file.
     */
    Almanac(const std::string& input);

    /**
     * @brief Reads and parses the puzzle input file.
     *
     * Parsing behavior:
     *   - Extract seed values from the "seeds:" line.
     *   - Parse each map section.
     *   - Convert each numeric rule line into a Rule object.
     *
     * The rule maps are stored in file order to preserve
     * correct functional composition.
     */
    void readPuzzleInput();

    /**
     * @brief Applies the full chain of rule maps to a single seed.
     *
     * Starting from the given seed value, this method applies each
     * RuleMap in sequence, transforming the value step by step
     * until the final location number is obtained.
     *
     * This models functional composition:
     *
     *     location = f_n ∘ f_{n-1} ∘ ... ∘ f_1 (seed)
     *
     * @param seed The initial seed number.
     * @return The final location number corresponding to the seed.
     */
    long long applySingleSeed(long long seed);

    /**
     * @brief Computes the solution to Part 1.
     *
     * For each seed listed in the input:
     *   - Apply all rule maps in order.
     *   - Compute the final location value.
     *
     * The answer is the minimum location value among all seeds.
     *
     * @return The lowest location number corresponding to any initial seed.
     */
    long long getSolutionPart1();



    // ================================================================
    //                     PART 2
    // ================================================================


    /**
     * @brief Converts the raw seed list into seed intervals.
     *
     * In Part 2, the input "seeds:" line encodes ranges:
     *
     *      seeds: start1 length1 start2 length2 ...
     *
     * Each pair (start, length) defines a closed interval:
     *
     *      [start, start + length - 1]
     *
     * These intervals are stored in seedIntervals.
     */
    void setSeedIntervals();

    /**
     * @brief Applies a RuleMap to a collection of intervals.
     *
     * Instead of mapping single values (as in Part 1),
     * this function maps entire intervals.
     *
     * For each input interval:
     *   - It computes overlaps with each rule.
     *   - Splits intervals into:
     *         • left remainder (unmapped)
     *         • overlapping mapped part (shifted by delta)
     *         • right remainder (unmapped)
     *
     * Intervals that never overlap any rule
     * map to themselves (identity).
     *
     * @param map The RuleMap to apply.
     * @param input The current set of intervals.
     * @return The transformed set of intervals after applying the map.
     */
    std::vector<Interval> applyMapToIntervals(
        const RuleMap& map,
        const std::vector<Interval>& input);

    /**
     * @brief Computes the solution to Part 2.
     *
     * Strategy:
     *   1. Convert seed pairs into intervals.
     *   2. Push intervals through each RuleMap in order.
     *   3. Track resulting transformed intervals.
     *   4. Return the minimum start value among final intervals.
     *
     * This avoids enumerating billions of seeds and instead
     * performs interval splitting and transformation.
     *
     * @return The lowest location number reachable from any seed range.
     */
    long long getSolutionPart2();

};


#endif // ALMANAC_H
