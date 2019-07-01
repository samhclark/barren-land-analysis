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
 *          Ex: $ barren_land_analysis --width 10 --length 10
 *              {"4 0 7 9"}
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
 *          Executed without command-line arguments, the default farm size is
 *          400 by 600. With command-line arguments (as shown in the example
 *          above), the program can simulate a farm of the desired length and
 *          width. If run with the --test argument, the program will run
 *          through a series of test farms and display each output.
 */


/*-Preprocessor Directives----------------------------------------------------*/
#include "Farm_Runner.h"
#include <cassert>  // assert()
#include <cstdlib>  // exit()
#include <cstring>  // strcmp()
#include <iostream> // cin, cout
/*----------------------------------------------------------------------------*/


//----------------------------------------------------------------------------//
// check_args:                                                                //
//      Inputs:     int - argc (argument count)                               //
//                  char** - argv (ragged char array of argument values)      //
//      Outputs:    bool - true if arguments are valid, false otherwise       //
bool check_args(int argc, char* argv[]);


//----------------------------------------------------------------------------//
// main:                                                                      //
//      Inputs:     argc, argv from command line                              //
//                  string - read from STDIN                                  //
//      Outputs:    string - areas sent to STDOUT                             //
int main(int argc, char* argv[]) {
    assert(check_args(argc, argv) && "Check usage.");

    if (argc == 2) {
        run_test_suite();
        exit(EXIT_SUCCESS);
    }

    // Set width and length based on command line args, if applicable.
    int width, length;

    if (argc == 1) { /* no args */
        width = 400;
        length = 600;
    }
    else { /* argc must be 5 */
        if ((std::strcmp(argv[1],"-w") == 0 || std::strcmp(argv[1],"--width") == 0)) {
            width = std::stoi(std::string(argv[2]));
            length = std::stoi(std::string(argv[4]));
        }
        else {
            length = std::stoi(std::string(argv[2]));
            width = std::stoi(std::string(argv[4]));
        }
    }

    std::string line;
    std::getline(std::cin, line);
    std::cout << run_farm(line, width, length) << std::endl;

    exit(EXIT_SUCCESS);
}


bool check_args(int argc, char* argv[]) {
    if (argc == 1) {
        return true;
    }

    if (argc == 2 && std::strcmp(argv[1],"--test") == 0) {
        return true;
    }

    if (argc != 5) { // argc == 5 is only valid option left
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
