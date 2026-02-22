#include "Almanac.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>


void Rule::printRule() const {

    std::cout << "[srcStart, srcEnd, range] = " << "[" << srcStart << ", " << srcEnd << ", " << delta << "]\n";
    std::cout << "Source Interval: [" << srcStart << ", " << srcEnd << "]\n";
    std::cout << "Dest Interval: [" << (srcStart + delta) << ", " << (srcEnd + delta) << "]\n";

    // destStart = srcStart + delta
    // destEnd = srcEnd + delta
}

long long RuleMap::apply(long long x) const {

    for (const auto& r : rules) {
        if (x >= r.srcStart && x <= r.srcEnd)
            return x + r.delta;
    }
    return x;
}

void RuleMap::printRuleMap() const {
    std::cout << "Rule '" << name << "' (" << rules.size() << " rules)\n";
}



Almanac::Almanac(const std::string& input)
    : puzzleInput(input)
{}

void Almanac::readPuzzleInput() {

    bool detail = false;

    std::ifstream file(puzzleInput);
    std::string line;

    RuleMap current;     // temp map being built
    bool inMap = false;  // true if in map section

    // read puzzle input
    while (std::getline(file, line)) {

        // blank lines separate sections -> skip
        if (line.empty()) continue;

        // if line starts with "seeds:"
        if (line.rfind("seeds:", 0) == 0) {

            // extract numbers after colon
            std::stringstream ss(line.substr(6));
            long long x;
            // push into seeds vector
            while (ss >> x)
                seeds.push_back(x);
            continue;
        }

        // if line contains "map:"
        if (line.find("map:") != std::string::npos) {

            // if already in map section
            if (inMap) {
                ruleMaps.push_back(current);  // save it
                current = RuleMap{};          // start a new map
            }

            inMap = true;
            current.name = line;   // save name (optional)
            continue;
        }

        // if we are in map section, in numeric line
        if (inMap) {

            // read values
            std::stringstream ss(line);
            long long destStart, srcStart, length;
            ss >> destStart >> srcStart >> length;

            // build the rule and convert: destStart sourceStart delta
            // into:
            //  - source interval
            //  - delta offset

            Rule r;
            r.srcStart = srcStart;
            r.srcEnd = srcStart + length - 1; // inclusive
            r.delta = destStart - srcStart;

            if (detail) r.printRule();

            // save the rule
            current.rules.push_back(r);
        }
    }

    // after finishing line, we push back last map
    // since there is no blank line after the final block
    if (inMap) {
        ruleMaps.push_back(current);
        if (detail) current.printRuleMap();
    }

    if (detail) {
        std::cout << "Total seeds read from file: " << seeds.size() << std::endl;
        std::cout << "Total rule maps: " << ruleMaps.size() << std::endl;
    }

}

long long Almanac::applySingleSeed(long long seed) {

    long long value = seed;

    for (const auto& map : ruleMaps)
        value = map.apply(value);

    return value;
}

long long Almanac::getSolutionPart1() {

    long long minimumValue = std::numeric_limits<long long>::max();

    for (long long s : seeds) {
        long long location = applySingleSeed(s);
        if (location < minimumValue)
            minimumValue = location;
    }

    return minimumValue;
}


void Almanac::setSeedIntervals() {

    for (int i = 0; i < (int)seeds.size(); i += 2) {
        long long start = seeds[i];
        long long length = seeds[i+1];

        seedIntervals.push_back({start, start + length - 1});
    }
}

std::vector<Interval> Almanac::applyMapToIntervals(
    const RuleMap& map,
    const std::vector<Interval>& input) {

    std::vector<Interval> output;

    // for each interval coming into this map
    for (const Interval& interval : input) {

        // track pieces that still need to be processed
        std::vector<Interval> remaining;
        remaining.push_back(interval);

        // for each rule in current map
        for (const Rule& rule : map.rules) {

            std::vector<Interval> newRemaining;

            // we try to match each remaining piece against this rule
            for (const Interval& piece : remaining) {

                long long a = piece.start;
                long long b = piece.end;

                long long r1 = rule.srcStart;
                long long r2 = rule.srcEnd;

                // compute overlap
                long long overlapStart = std::max(a, r1);
                long long overlapEnd = std::min(b, r2);

                if (overlapStart <= overlapEnd) {

                    // there is an overlap

                    // (a) left remainder (not affected by rule)
                    if (a < overlapStart) {
                        newRemaining.push_back({a, overlapStart - 1});
                    }

                    // (b) overlapping part (we shift by delta)
                    output.push_back({overlapStart + rule.delta, overlapEnd + rule.delta});

                    // (c) right remainder (not affected by rule)
                    if (overlapEnd < b) {
                        newRemaining.push_back({overlapEnd + 1, b});
                    }
                }
                else {

                    // if no overlap, we keep piece unchanged for future rules
                    newRemaining.push_back(piece);
                }
            }

            // continue processing leftover pieces with next rule
            remaining = newRemaining;
        }

        // after processing all rules,
        // whatever is left was never mapped, so these simply map to themseleves
        // so we add them unchanged
        for (const Interval& piece : remaining) {
            output.push_back(piece);
        }
    }

    return output;
}

long long Almanac::getSolutionPart2() {

    std::vector<Interval> current;

    // build initial seed intervals
    setSeedIntervals();

    // push intervals through each map
    for (const RuleMap& map : ruleMaps) {
        seedIntervals = applyMapToIntervals(map, seedIntervals);
    }

    // find minimum start in final intervals
    long long minimum = std::numeric_limits<long long>::max();

    for (const Interval& interval : seedIntervals) {
        minimum = std::min(minimum, interval.start);
    }

    return minimum;
}








