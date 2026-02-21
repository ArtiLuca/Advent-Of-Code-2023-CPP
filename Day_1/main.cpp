#include "WeatherCalibration.cpp"

using namespace std;

int main() {

    std::cout << "AoC 2023 Day 1" << std::endl;

    WeatherCalibration1 w1("input.txt");
    w1.readPuzzleInput1();
    int solution1 = w1.getSolutionPart1();
    // SOLUTION = 55208
    std::cout << "Part 1 Solution: " << solution1 << std::endl;

    int solution2 = w1.getSolutionPart2();
    // SOLUTION = 54578
    std::cout << "\n\nPart 2 Solution: " << solution2 << std::endl;


    return 0;
}

