/*
 * File:    Farm_Runner.h
 * Author:  Sam Clark
 * Created: July 1, 2019 at 12:06 AM
 */

#ifndef BARREN_LAND_FARM_RUNNER_H
#define BARREN_LAND_FARM_RUNNER_H

#include <string>

//----------------------------------------------------------------------------//
// run_test_suite:                                                            //
//      Inputs:     NONE                                                      //
//      Outputs:    Test results to STDOUT                                    //
void run_test_suite();


//----------------------------------------------------------------------------//
// run_farm:                                                                  //
//      Inputs:     string - line (input read from STDIN)                     //
//                  int - width (width of Farm)                               //
//                  int - length (length of Farm)                             //
//      Outputs:    string - results from Farm                                //
std::string run_farm(std::string line, int width, int length);


//----------------------------------------------------------------------------//
// test_farm:                                                                 //
//      Inputs:     string - line (input read from STDIN)                     //
//                  int - width (width of Farm)                               //
//                  int - length (length of Farm)                             //
//                  string - out (expected output of farm)                    //
//      Outputs:    NONE - writes to STDOUT                                   //
void test_farm(std::string line, int width, int length, std::string out);

#endif //BARREN_LAND_FARM_RUNNER_H
