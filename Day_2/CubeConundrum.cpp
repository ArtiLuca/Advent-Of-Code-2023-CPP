#include "CubeConundrum.h"

CubeConundrum::CubeConundrum(const std::string& input) {
    puzzleInput = input;
    readPuzzleInput();
}

void CubeConundrum::readPuzzleInput() {

    // open puzzle input
    std::ifstream f(puzzleInput);
    std::string s;

    // read in each line
    while (std::getline(f, s)) {

        // separate string
        size_t colonPos = s.find(':');
        std::string s1 = s.substr(0, colonPos);
        std::string s2 = s.substr(colonPos + 1);

        Game g;
        // extract game ID
        g.id = std::stoi(s1.substr(5));

        std::stringstream sets(s2);
        std::string setInfo;

        // read game sets
        while (std::getline(sets, setInfo, ';')) {

            CubeSet set;
            std::stringstream pairs(setInfo);
            std::string pairInfo;

            // read set pairs and set color counts
            while (std::getline(pairs, pairInfo, ',')) {

                std::stringstream ss(pairInfo);
                int count;
                std::string color;

                ss >> count >> color;

                if (color == "red") set.red = count;
                else if (color == "green") set.green = count;
                else if (color == "blue") set.blue = count;
            }

            // insert set into game
            g.cubeSets.push_back(set);
        }

        // inset game into list
        games.push_back(g);
    }

    std::cout << "Read Successful: " << games.size() << " total games read." << std::endl;
}

int CubeConundrum::getSolutionPart1(bool detail) {

    int solution1 = 0;
    bool valid = true;

    for (int i = 0; i < (int)games.size(); ++i) {
        valid = true;
        for (int j = 0; j < (int) games[i].cubeSets.size(); ++j) {

            if (games[i].cubeSets[j].blue > 14 || games[i].cubeSets[j].red > 12 || games[i].cubeSets[j].green > 13) {
                valid = false;
            }
        }

        if (valid) {
            if (detail) testPrintGame(i);
            solution1 += games[i].id;
        }
    }

    return solution1;
}

CubeSet CubeConundrum::minCubesNeeded(const Game& g) {

    CubeSet cs;
    for (int i = 0; i < (int)g.cubeSets.size(); ++i) {
        CubeSet curr = g.cubeSets[i];
        cs.blue = std::max(cs.blue, curr.blue);
        cs.red = std::max(cs.red, curr.red);
        cs.green = std::max(cs.green, curr.green);
    }

    std::cout << "Min: B=" << cs.blue << " R=" << cs.red << " G=" << cs.green << std::endl;
    return cs;
}

int CubeConundrum::getSolutionPart2() {

    int solution2 = 0;

    for (int i = 0; i < (int)games.size(); ++i) {
        CubeSet csMin = minCubesNeeded(games[i]);
        solution2 += (csMin.blue * csMin.red * csMin.green);
    }
    return solution2;
}

void CubeConundrum::testPrintGame(int pos) {

    Game g = games[pos];
    std::cout << "Valid Game. ID: " << g.id << "\n";

    for (int i = 0; i < (int)g.cubeSets.size(); ++i) {
        CubeSet cs = g.cubeSets[i];
        std::cout << "[Game " << i <<  " R=" << cs.red << " B=" << cs.blue << " G=" << cs.green << "]\n";
    }
}
