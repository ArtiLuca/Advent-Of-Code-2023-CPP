#include "CubeConundrum.cpp"

using namespace std;

int main() {

    std::cout << "AoC 2023 Day 2" << std::endl;

    CubeConundrum cubeGame("input.txt");

    int solution1 = cubeGame.getSolutionPart1();
    std::cout << "Part 1 Solution: " << solution1 << std::endl;

    std::cout << "\n--- Part 2 ---" << std::endl;
    int solution2 = cubeGame.getSolutionPart2();
    std::cout << "Part 2 Solution: " << solution2 << std::endl;

    return 0;
}

