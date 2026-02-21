#include "GearRatios.cpp"

using namespace std;

int main() {

    std::cout << "AoC 2023 Day 3" << std::endl;

    GearRatios engine("input.txt");
    engine.readPuzzleInput();
    engine.parseFullSchematic(false);
    int solution1 = engine.getSolutionPart1();
    std::cout << "Part 1 Solution: " << solution1 << std::endl;

    int solution2 = engine.getSolutionPart2();
    std::cout << "Part 2 Solution: " << solution2 << std::endl;

    return 0;
}
