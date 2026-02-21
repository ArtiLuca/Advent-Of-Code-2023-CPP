#include "Scratchcard.cpp"

using namespace std;

int main() {

    std::cout << "--- Aoc 2023 Day 3 - Part 1 ---"  << std::endl;

    Scratchcard game("input.txt");
    game.readPuzzleInput();
    int sol1 = game.getSolutionPart1();

    std::cout << "Part 1 Solution: " << sol1 << std::endl;

    std::cout << "\n--- Aoc 2023 Day 3 - Part 2 ---"  << std::endl;
    long long sol2 = game.getSolutionPart2();

    std::cout << "Part 2 Solution: " << sol2 << std::endl;


    return 0;
}
