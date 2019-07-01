# Barren Land Analysis
Target Case Study 2: Barren Land Analysis

**Purpose:**  
The purpose of the case study is to (1) provide a gauge of technical ability and (2) show how I think. The excercise needs to meet the following requirements:
1. *The excercise should be completed in the tech stack of choice.* In this case, that is C++.  
2. *Evidence of the results must be provided.* In this case, there are tests of each class and the code is runnable itself.  
3. *The end result should be a functional implementation of the problem, along with associated tests.* The code is provided here, in a publicly accessible repo and the README.md is available as well (this file). 

**Problem Statement:**  
Suppose there is a rectangular farm of a given size (e.g. 400 units by 600 units). A portion of this farm is barren and the rest is fertile. All barren land is given as a set of rectangles. These rectangles are defined by the position of their bottom left corner and their top right corner. This program takes the set of barren land and calculates the area(s) of the remaining fertile land. Input is from STDIN and output is to STDOUT.

Ex: 
```
$ barren_land_analysis --width 10 --length 10
{"4 0 7 9"}
20 40
```

The illustration below is only for description, this is not printed on each run of the code, however the Farm class does have a display_farm() member function that can output an illustration of the farm to STDOUT, for testing. 
```
9 | .  .  .  .  X  X  X  X  .  .
8 | .  .  .  .  X  X  X  X  .  .     X -- barren land
7 | .  .  .  .  X  X  X  X  .  .     . -- fertile land
6 | .  .  .  .  X  X  X  X  .  .
5 | .  .  .  .  X  X  X  X  .  .
4 | .  .  .  .  X  X  X  X  .  .
3 | .  .  .  .  X  X  X  X  .  .
2 | .  .  .  .  X  X  X  X  .  .
1 | .  .  .  .  X  X  X  X  .  .
0 | .  .  .  .  X  X  X  X  .  .
  +------------------------------
    0  1  2  3  4  5  6  7  8  9
```

On the 10 by 10 farm above, the barren land is described by the coordinate set **{"4 0 7 9"}**. This leaves two distinct areas of fertile land. This program calculates those areas and displays them on STDOUT from least to greatest. The result being **20 40**.

**Usage:**  
Executed without command-line arguments, the default farm size is 400 by 600. With command-line arguments (as shown in the example above), the program can simulate a farm of the desired length and width. If run with the **--test** argument, the program will run through a series of test farms and display each output. 

**Build Instruction:**
1. Clone this repository.  
2. Run **make** which will build the executable from source.  
3. Run the executable (**barren_land_analysis**) which is in the same directory as the source files.  
