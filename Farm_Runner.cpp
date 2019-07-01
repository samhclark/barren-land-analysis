/*
 * File:    Farm_Runner.cpp
 * Author:  Sam Clark
 * Created: July 1, 2019 at 12:06 AM
 */

#include "Barren.h"
#include "Farm_Runner.h"
#include "Farm.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>


void run_test_suite() {
    std::cout << "Barren Land Analysis Test Suite" << std::endl;

    // Given in problem statement
    std::cout << "Test 01:";
    test_farm(R"({"0 292 399 307"})", /*raw input string*/
              400, /*width*/
              600, /*length*/
              "116800 116800"); /*expected output*/

    // Given in problem statement
    std::cout << "Test 02:";
    test_farm(R"({"48 192 351 207", "48 392 351 407", "120 52 135 547", "260 52 275 547"})",
              400, 600, "22816 192608");

    // Small test from the README.md
    std::cout << "Test 03:";
    test_farm(R"({"4 0 7 9"})", 10, 10, "20 40");

    // Farm with lots of corners and backtracking
    std::cout << "Test 04:";
    test_farm(R"({"2 4 3 4", "1 3 5 3", "8 3 8 4", "9 4 12 4", "12 0 12 3", "11 0 11 0", "10 2 11 2"})",
            13, 5, "45");

    // Bad formatting
    std::cout << "Test 05:";
    test_farm(R"(48 192 351 207 48 392 351 407 120 52 135 547 260 52 275 547)",
              400, 600, "22816 192608");

    // Small test from the README.md
    std::cout << "Test 06:";
    test_farm(R"({"4 0 7"})", 10, 10, "Invalid number of arguments. Read 3 args.");
}

std::string run_farm(std::string line, int width, int length) {
    // First, parse the line.
    // This is a raw string read from STDIN. In order to be robust,
    //several characters ({ } , ") are replaced with white space. Then
    // the remaining integers are pushed into an int vector. If a multiple
    // of 4 integers were read, then they are parsed as valid coordinates.
    // These are then used to create the desired Barren objects.
    // TODO: Fix the parsing to more closely align with the formatting spec
    std::stringstream stream(std::regex_replace(line,
            std::regex{R"(\{|\}|,|\")"}, " "));
            /* replaces { } , and " with white space */

    // Parse remaining string to int vector
    std::vector<int> coords;
    int coord;
    while(stream >> coord) {
        coords.push_back(coord);
    }

    // If there are the wrong number of coords, print an error
    // and exit the program
    if (coords.size() % 4 != 0) {
        std::stringstream ss;
        ss << "Invalid number of arguments. Read " << coords.size() << " args.";
        return ss.str();
    }

    Farm f(width, length);

    // Add each Barren object to the Farm
    for (int i = 0; i < coords.size(); i += 4) {
        f.add_barren(Barren(coords[i],
                            coords[i+1],
                            coords[i+2],
                            coords[i+3]));
    }

    std::vector<int> f_areas = f.get_fertile_area();

    // Create a string from the int vector of areas
    std::stringstream ss;

    ss << f_areas[0];
    for(int i = 1; i < f_areas.size(); i++) {
        ss << " " << f_areas[i];
    }
    return ss.str();
}

void test_farm(std::string line, int width, int length, std::string out) {
    std::string str = run_farm(line, width, length);

    std::cout << (str == out ? " Passed\n" : " Failed\n");
    std::cout << "Input string: " << line << "\n";
    std::cout << "Desired output: " << out << "\n";
    std::cout << " Actual output: " << str << "\n";
    std::cout << std::endl;
}
