/*
 * File:    Farm.h
 * Author:  Sam Clark
 * Created: June 28, 2019 at 12:46 AM
 */

#ifndef FARM_H
#define FARM_H

#include <algorithm>
#include "Barren.h"
#include <cassert>
#include <iostream>
#include <vector>


/**
 * Class definition
 */
class Farm {
public:
    // Overload assignment operator
    Farm& operator=(const Farm& other_farm);

    // Default constructor
    // Creates 400 x 600 farm
    Farm();

    // Constructor from two ints
    Farm(int w, int l);

    // Copy constructor
    Farm(const Farm& other_farm);

    // Destructor
    ~Farm();

    // Function to add barren area to farm
    void add_barren(const Barren& b);

    // Function to reset farm to initial state
    void clear_farm();

    // Function that calculates and returns the total fertile area
    std::vector<int> get_fertile_area();

    // Prints out a visualization of the farm to STDOUT
    void display_farm() const;


private:
    int width;
    int length;

    std::vector<std::vector<int>> field;

    // Fills in the fertile area of the farm
    void fill_cell(int &marker, int i, int j);

    // Function to make a copy of other_farm
    void copy_farm(const Farm& other_farm);

    // Safe access method for field
    int get_cell(int x, int y) const;

    // Replace a marker with another marker
    // Used to reduce field down to minimum number of markers
    void replace_in_field(int search, int replace);

    int smallest_int_gt_zero(int a, int b, int c, int d) const;
};



/**
 * Member function implementations
 */
Farm& Farm::operator=(const Farm& other_farm){
    if (this != &other_farm) {  //avoid self-copy
        copy_farm(other_farm);
    }
    return *this;
}

Farm::Farm() {
    width = 400;
    length = 600;
    field.resize(width, std::vector<int>(length));
    clear_farm();
}

Farm::Farm(int w, int l) {
    assert(width >= 0 && "Width must be positive.");
    assert(length >= 0 && "Length must be positive.");

    width = w;
    length = l;
    field.resize(width, std::vector<int>(length));
    clear_farm();
}

Farm::Farm(const Farm& other_farm) {
    copy_farm(other_farm);
}

Farm::~Farm() {};

void Farm::add_barren(const Barren& b) {
    assert(b.is_valid() && "Barren object was invalid.");
    assert(b.get_top_right_x() < width && "Barren object was wider than farm width.");
    assert(b.get_top_right_y() < length && "Barren object was longer than farm length.");

    for (int i = b.get_bottom_left_x(); i <= b.get_top_right_x(); i++) {
        for (int j = b.get_bottom_left_y(); j <= b.get_top_right_y(); j++) {
            field[i][j] = -1;
        }
    }
}

void Farm::clear_farm() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            field[i][j] = 0;
        }
    }
}

std::vector<int> Farm::get_fertile_area() {
    int marker = 1;

    // Fill in the fertile area with marker ints
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            fill_cell(marker, i, j);
        }
    }

    // Now count them up
    // Not counting on write because it can change as they are filled
    // TODO: This could be calculated as written.
    std::vector<int> counts (marker, 0);  // could be std::array
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            if (field[i][j] < 1) {
                continue;
            }
            else {
                counts[field[i][j] - 1]++;
            }
        }
    }

    // Remove zeros from the vector, sort the vector.
    std::sort(counts.begin(),
              counts.erase(std::remove(counts.begin(), counts.end(), 0),
                           counts.end()));

    return counts;
}

void Farm::fill_cell(int &marker, int i, int j) {
    int above, right, left, below, min;
    int curr_val = field[i][j];

    if (curr_val >= 0) {
        above = get_cell(i, j+1);
        right = get_cell(i+1, j);
        below = get_cell(i, j-1);
        left = get_cell(i-1, j);
        min = smallest_int_gt_zero(above, right, below, left);

        // If the current location is already filled, and is smaller
        // then any one of the surrounding numbers, then that surrounding
        // number needs to be replaced by the current number.
        // TODO: I'm not 100% sure this ever gets hit
        if (above > 0 && curr_val < above && curr_val > 0) {
            replace_in_field(above, curr_val);
        }
        else if (right > 0 && curr_val < right && curr_val > 0) {
            replace_in_field(right, curr_val);
        }
        else if (below > 0 && curr_val < below && curr_val > 0) {
            replace_in_field(below, curr_val);
        }
        else if (left > 0 && curr_val < left && curr_val > 0) {
            replace_in_field(left, curr_val);
        }
        // If any of the surrounding cells are filled, then this cell is
        // filled by that number
        else if (min > 0) {
            field[i][j] = min;
            // Then, each of the surrounding cells are checked to make sure
            // they shouldn't be replaced
            if (above > min) {
                replace_in_field(above, min);
            }
            if (left > min) {
                replace_in_field(left, min);
            }
            if (right > min) {
                replace_in_field(right, min);
            }
            if (below > min) {
                replace_in_field(below, min);
            }
        }
        // If the current cell can't be filled by an adjacent cell, then it
        // is filled with the current marker and the marker is incremented.
        else if (curr_val == 0) {
            field[i][j] = marker;
            marker++;
        }
    }
}

void Farm::display_farm() const {
    for (int j = length-1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            std::cout << field[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void Farm::copy_farm(const Farm& other_farm) {
    assert(other_farm.width == width && other_farm.length == length
            && "Farm sizes must match.");
    field = other_farm.field;
}

int Farm::get_cell(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= length) {
        return -1;
    }
    else {
        return field[x][y];
    }
}

void Farm::replace_in_field(int search, int replace) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < length; j++) {
            if (field[i][j] == search) {
                field[i][j] = replace;
            }
        }
    }
}

int Farm::smallest_int_gt_zero(int a, int b, int c, int d) const {
    int min = -1;
    if (a > 0 && (min <= 0 || a < min)) {
        min = a;
    }
    if (b > 0 && (min <= 0 || b < min)) {
        min = b;
    }
    if (c > 0 && (min <= 0 || c < min)) {
        min = c;
    }
    if (d > 0 && (min <= 0 || d < min)) {
        min = d;
    }
    return min;
}

#endif //FARM_H
