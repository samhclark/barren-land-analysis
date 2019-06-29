/*
 * File:    main.cpp
 * Author:  Sam Clark
 * Created: June 27, 2019 at 2:54 PM
 *
 * Purpose: Target Interview Case Study 2
 *          Barren Land Analysis
 *          Suppose there is a rectangular farm of a given size (e.g. 400 units
 *          by 600 units). A portion of this farm is barren and the rest is
 *          fertile. All barren land is given as a set of rectangles. These
 *          rectangles are defined by the position of their bottom left corner
 *          and their top right corner.
 *          This program takes the set of barren land and calculates the area(s)
 *          of the remaining fertile land. Input is from STDIN and output is to
 *          STDOUT.
 *
 *          Ex: $ barren_land_analysis.exe {"4 0 7 9"}
 *              20 40
 *
 *          9 | .  .  .  .  X  X  X  X  .  .
 *          8 | .  .  .  .  X  X  X  X  .  .     X -- barren land
 *          7 | .  .  .  .  X  X  X  X  .  .     . -- fertile land
 *          6 | .  .  .  .  X  X  X  X  .  .
 *          5 | .  .  .  .  X  X  X  X  .  .
 *          4 | .  .  .  .  X  X  X  X  .  .
 *          3 | .  .  .  .  X  X  X  X  .  .
 *          2 | .  .  .  .  X  X  X  X  .  .
 *          1 | .  .  .  .  X  X  X  X  .  .
 *          0 | .  .  .  .  X  X  X  X  .  .
 *            +------------------------------
 *              0  1  2  3  4  5  6  7  8  9
 *
 *          On this 10 by 10 farm, the barren land is described by the
 *          coordinate set {"4 0 7 9"}. This leaves two distinct areas of
 *          fertile land. This program calculates those areas and displays
 *          them on STDOUT from least to greatest. The result being "20 40".
 *
 *          The default farm area is 400 by 600. The program accepts command
 *          line arguments for easier use from the shell. If executed without
 *          arguments, the program will take input from STDIN.
 */


/*-Preprocessor Directives----------------------------------------------------*/
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "Barren.h"
#include "Farm.h"
/*----------------------------------------------------------------------------*/


bool check_args(int argc, char* argv[]);

//----------------------------------------------------------------------------//
// main:                                                                      //
//      Inputs:     string from STDIN                                         //
//      Outputs:    string of areas to STDOUT                                 //
int main(int argc, char* argv[]) {
    assert(check_args(argc, argv) && "Check usage.");

    int width, length;
    if (argc == 1) {
        width = 400;
        length = 600;
    }
    else if (argc == 5) {
        if ((std::strcmp(argv[1],"-w") == 0 || std::strcmp(argv[1],"--width") == 0)) {
            width = std::stoi(argv[1]);
            length = std::stoi(argv[3]);
        }
        else if ((std::strcmp(argv[1],"-l") == 0 || std::strcmp(argv[1],"--length") == 0)) {
                length = std::stoi(argv[1]);
                width = std::stoi(argv[3]);
        }
        else {
            std::cerr << "Usage error." << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        std::cerr << "Usage error." << std::endl;
        exit(EXIT_FAILURE);
    }


    std::string line;
    std::getline(std::cin, line);
    std::istringstream stream(std::regex_replace(line,
            std::regex{R"(\{|\}|,|\")"}, " "));
    std::vector<int> coords;
    int coord;
    while(stream >> coord) {
        coords.push_back(coord);
    }

    std::vector<Barren> barren_v;

    if (coords.size() % 4 != 0) {
        std::cerr << "Invalid number of arguments. Read " << coords.size()
                    << " args." << std::endl;
        exit(EXIT_FAILURE);
    }
    else {
        for (int i = 0; i < coords.size(); i += 4) {
            barren_v.emplace_back(Barren(coords[i],
                                         coords[i+1],
                                         coords[i+2],
                                         coords[i+3]));
        }
    }

    Farm f(width, length);

    for (auto b: barren_v) {
        f.add_barren(b);
    }

    std::vector<int> f_areas = f.get_fertile_area();
    std::cout << f_areas[0];
    for(int i = 1; i < f_areas.size(); i++) {
        std::cout << " " << f_areas[i];
    }
    std::cout << std::endl;

    exit(EXIT_SUCCESS);
}

bool check_args(int argc, char* argv[]) {
    if (argc == 1) {
        return true;
    }

    if (argc != 5) {
        return false;
    }

    if ( (std::strcmp(argv[1],"-w") == 0 || std::strcmp(argv[1],"--width") == 0) &&
         (std::strcmp(argv[3],"-l") == 0 || std::strcmp(argv[3],"--length") == 0) ) {
        return true;
    }

    if ( (std::strcmp(argv[1],"-l") == 0 || std::strcmp(argv[1],"--length") == 0) &&
         (std::strcmp(argv[3],"-w") == 0 || std::strcmp(argv[3],"--width") == 0) ) {
        return true;
    }

    return false;
}