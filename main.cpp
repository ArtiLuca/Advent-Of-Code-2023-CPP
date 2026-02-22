#include "Almanac.cpp"

using namespace std;

int main() {

    std::cout << "Aoc 2023 Day 5" << std::endl;

    // Part 1
    std::cout << "=== PART 1 ===" << std::endl;
    Almanac a("input.txt");
    a.readPuzzleInput();
    long long solution1 = a.getSolutionPart1();
    std::cout << "Solution Part 1 = " << solution1 << std::endl;

    std::cout << "=== PART 1 ===" << std::endl;
    long long solution2 = a.getSolutionPart2();
    std::cout << "Solution Part 2 = " << solution2 << std::endl;

    return 0;

}
